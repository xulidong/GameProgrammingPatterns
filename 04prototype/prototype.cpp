/*
 * It is used when the type of objects to create is determined by a prototypical instance,
 * which is cloned to produce new objects.
 * */

// 产生不同怪物的方式

// version 01

// 怪物
class Monster
{
public:
	virtual ~Monster() {}
};


class Ghost : public Monster
{

};

class Demon : public Monster
{

};

class Sorcerer : public Monster
{

};

// 怪物生产者
class Spawner
{
public:
	virtual ~Spawner() {}
	virtual Monster* spawnMonster() = 0;
};

class GhostSpawner : public Spawner
{
public:
	virtual Monster* spawnMonster() {
		return new Ghost();
	}
};

class DemonSpawner : public Spawner
{
public:
	virtual Monster* spawnMonster() {
		return new Demon();
	}
};

class SorcererSpawner : public Spawner
{
public:
	virtual Monster* spawnMonster() {
		return new Sorcerer();
	}
};


// version 02
// 将多个生产者类变为一个
class Monster
{
public:
	virtual ~Monster() {}
	virtual Monster* clone() = 0;
};


class Ghost : public Monster
{
public:
	Ghost(int health, int speed) : health_(health), speed_(speed) {}
	virtual Monster* clone() {
		return new Ghost(health_, speed_);
	}

private:
	int health_;
	int speed_;
};

class Spawner
{
public:
	Spawner(Monster* prototype) : prototype_(prototype) {}
	Monster* spawnMonster() {
		return prototype->clone();
	}

private:
	Monster* prototype_;
};

Monster* ghostPrototype = new Ghost(15, 3);
Spawner* ghostSpawner = new Spawner(ghostPrototype);


// version 03
// 将生产者持有的对象替换为函数

Monster* spawnGhost()
{
	return Ghost();
}

typedef Monster* (*SpawnCallback)();

class Spawner
{
public:
	Spawner(SpawnCallback spawn) : spawn_(spawn) {}
	Monster* spawnMonster() {
		return spawn_();
	}

private:
	SpawnCallback spawn_;
};

Spawner* ghostSpawner = new Spawner(spawnGhost);


// version 03
// 使用模板
class Spawner
{
public:
	virtual ~Spawner() {}
	virtual Monster* spawnMonster() = 0;
};

template <class T>
class SpawnerFor : public Spawner
{
public:
	virtual Monster* spawnMonster() {
		return new T();
	}
};

Spawner* ghostSpawner = new SpawnerFor<Ghost>();

