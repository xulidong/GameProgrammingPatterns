/*
 * 1 singleton: Ensure a class has one instance, and provide a global point of access to it.
 * 2 how to avoid using it
 * */

/* singleton */

// version 01
class FileSystem
{
public:
	static FileSystem& instance() {
		if (instance_ == NULL) {
			instance_ = new FileSystem();
		}
		return instance_;
	}

private:
	FileSystem() {}
	static FileSystem* instance_;
};

// version 02
// 线程安全
class FileSystem
{
public:
	static FileSystem& instance() {
		static FileSystem* instance_ = new FileSystem();
		return instance_;
	}
private:
	FileSystem() {}
};

// version 03
class PS3FileSystem;
class WiiFileSystem;
class FileSystem
{
public:
	static FileSystem& instance() {
	#if PLATFORM == PLAYSTATION3
    	static FileSystem *instance = new PS3FileSystem();
	#elif PLATFORM == WII
    	static FileSystem *instance = new WiiFileSystem();
  	#endif
		return *instance;
	}

	virtual ~FileSystem() {}
	virtual char* readFile(char* path) = 0;
	virtual void  writeFile(char* path, char* contents) = 0;

protected:
  FileSystem() {}
};

class PS3FileSystem : public FileSystem
{
public:
	virtual char* readFile(char* path) {}
	virtual void  writeFile(char* path, char* contents) {}
};

class WiiFileSystem : public FileSystem
{
public:
	virtual char* readFile(char* path) {}
	virtual void  writeFile(char* path, char* contents) {}
};

/*  
 * how to avoid using it 
 * 1 理解代码更加困难
 * 2 激励耦合
 * 3 非并行友好
 * 总之一句话，他是一个全局变量
 * */


// version 01

class Bullet
{
public:
	int getX() const {return x_;}
	int getY() const {return y_;}

	void setX(int x) {x_ = x;}
	void setY(int y) {y_ = y;}

private:
	int x_;
	int y_;
};


class BulletManager : public singleton
{
public:
	Bullet* create(int x, int y) {
		Bullet* bullet = new Bullet();
		bullet->setX(x);
		bullet->setY(y);
		return bullet;
	}

	bool isOnScreen(Bullet& bullet) {
		return bullet.getX() >=0 &&
			bullet.getX() <= SCREEN_WIDTH &&
			bullet.getY() >= 0 &&
			bullet.getY() <= SCREEN_HEIGHT;
	}

	void move(Bullet& bullet) {
		bullet.setX(bullet.getX() + 5);
	}
}；

// version 02
class Bullet
{
public:
	int getX() const {return x_;}
	int getY() const {return y_;}

	void setX(int x) {x_ = x;}
	void setY(int y) {y_ = y;}

	bool isOnScreen(Bullet& bullet) {
		return _x >=0 && _x <= SCREEN_WIDTH &&
			_y >= 0 && _y <= SCREEN_HEIGHT;
	}

private:
	int x_;
	int y_;
};


/*
替代单例的方法：
1 参数传入
2 从基类中获取
3 从现有的全局变量获取
4 从服务定位器中获得
*/

class GameObject
{
protected:
	Log& getLog() { return log_; }

private:
	static Log& log_;
};

class Enemy : public GameObject
{
	void doSomething() {
    	getLog().write("I can log!");
	}
};

class Game
{
public:
	static Game& instance() { 
		return instance_; 
	}
	Log& getLog() { 
		return *log_; 
	}
	FileSystem& getFileSystem() { 
		return *fileSystem_; 
	}
	AudioPlayer& getAudioPlayer() { 
		return *audioPlayer_; 
	}

private:
	static Game instance_;

	Log* log_;
	FileSystem* fileSystem_;
	AudioPlayer* audioPlayer_;
};

