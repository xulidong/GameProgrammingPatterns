/*
 *
 * */

// version 01
while (true) {
	// Patrol right.
	for (double x = 0; x < 100; x++) {
		skeleton.setX(x);
	}
	// Patrol left.
	for (double x = 100; x > 0; x--) {
		skeleton.setX(x);
	}
}	

// version 02
Entity skeleton;
bool patrollingLeft = false;
double x = 0;

while (true) {
	if (patrollingLeft) {
		x--;
		if (x == 0)
			patrollingLeft = false;
	}
	else {
		x++;
		if (x == 100) {
			patrollingLeft = true;
		}
	}
	skeleton.setX(x);
}

// version 03
Entity leftStatue;
Entity rightStatue;
int leftStatueFrames = 0;
int rightStatueFrames = 0;

while (true) {
	if (++leftStatueFrames == 90) {
		leftStatueFrames = 0;
		leftStatue.shootLightning();
	}

	if (++rightStatueFrames == 80) {
		rightStatueFrames = 0;
		rightStatue.shootLightning();
	}
}

// version 04
class Entity
{
public:
	Entity() : x_(0), y_(0) {}

	virtual ~Entity() {}
	virtual void update() = 0;

	double x() const {
		return x_;
	}

	double y() const {
		return y_;
	}

	void setX(double x) {
		x_ = x;
	}

	void setY(double y) {
		y_ = y;
	}

private:
	double x_;
	double y_;
};

class World
{
public:
	World() : numEntities_(0) {}

	void gameLoop() {
		while (true) {
			for (int i = 0; i < numEntities_; i++) {
				entities_[i]->update();
			}
		}
	}

private:
	Entity* entities_[MAX_ENTITIES];
	int numEntitities;
};

class Skeleton : public Entity 
{
public:
	Skeleton() : patrollingLeft_(false) {}

	virtual void udpate() {
		if (patrollingLeft_) {
			setX(x() - 1);
			if (x() == 0) patrollingLeft_ = false;
		} 
		else {
			setX(x() + 1);
			if (x() == 100) patrollingLeft_ = true;
		}
	}

private:
	bool patrollingLeft_;
};

class Statue : public Entity
{
public:
	Statue(int delay) : frames_(0), delay_(delay) {}

	virtual void update() {
		if (++frames_ == delay_) {
			shootLightning();
			frames_ = 0;
		}
	}

private:
	int frames_;
	int delay_;

	void shootLightning(){
		// Shoot the lightning...
	}
};

// version 04
void Skeleton::update(double elapsed)
{
	if (patrollingLeft_) {
		x -= elapsed;
		if (x <= 0) {
			patrollingLeft_ = false;
			x = -x;
		}
	}
	else {
		x += elapsed;
		if (x >= 100) {
			patrollingLeft_ = true;
			x = 100 - (x - 100);
		}
	}
}