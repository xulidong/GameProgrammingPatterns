

// version 01

class Monster
{
public:
	virtual ~Monster() {}
	virtual const char* getAttack() = 0;

protected:
	Monster(int startingHealth) : health_(startingHealth) {}

private:
	int health_; // Current health.
};

class Dragon : public Monster
{
public:
	Dragon() : Monster(230) {}

	virtual const char* getAttack() {
		return "The dragon breathes fire!";
	}
};

class Troll : public Monster
{
public:
	Troll() : Monster(48) {}

	virtual const char* getAttack() {
		return "The troll clubs you!";
	}
};

// version 02
class Breed
{
public:
	Breed(int health, const char* attack) : health_(health), attack_(attack) {}

	int getHealth() { 
		return health_; 
	}

	const char* getAttack() { 
		return attack_; 
	}

private:
	int health_; // Starting health.
	const char* attack_;
};

class Monster
{
public:
	Monster(Breed& breed) : health_(breed.getHealth()), breed_(breed) {}

	const char* getAttack() {
		return breed_.getAttack();
	}

private:
	int health_; // Current health.
	Breed& breed_;
};

Monster* monster = new Monster(someBreed);

// version 03

class Breed 
{
public:
	Monster* newMonster() {
		return new Monster(*this);
	}

	int getHealth() { 
		return health_; 
	}

	const char* getAttack() { 
		return attack_; 
	}

private:
	int health_; // Starting health.
	const char* attack_;
};

class Monster
{
	friend class Breed;

public:
	const char* getAttack() {
		return breed_.getAttack();
	}

private:
	Monster(Breed& breed) : health_(breed.getHealth()), breed_(breed) {}

	int health_;// Current health.
	Breed& breed_;
};

Monster* monster = someBreed.newMonster();

// version 03

class Breed
{
public:
	Breed(Breed* parent, int health, const char* attack) : parent_(parent), health_(health), attack_(attack_) {}

	int getHealth() { 
		if (health_ != 0 || parent_ == NULL) 
			return health_;
		return parent_->getHealth(); 
	}

	const char* getAttack() { 
		if (attack_ != NULL || parent_ == NULL) 
			return attack_;
		return parent_->getAttack(); 
	}

private:
	Breed* parent_;
	int health_;
	const char* attack_;
};

// version 04

class Breed 
{
public:
	Breed(Breed* parent, int health, const char* attack) : parent_(parent), health_(health), attack_(attack_) {
		if (parent != NULL) {
			if (health == 0) 
				health_ = parent->getHealth();
			
    		if (attack == NULL) 
    			attack_ = parent->getAttack();
		}

	}

	int getHealth() { 
		return health_; 
	}

	const char* getAttack() { 
		return attack_; 
	}

private:
	int health_; // Starting health.
	const char* attack_;
};