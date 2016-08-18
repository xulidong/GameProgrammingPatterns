/*
 *放弃独立地分配和释放对象，从固定的池子中重用对象，以提高性能和内存使用率
 * */

// version 01

class Particle
{
public:
	Particle() : framesLeft_(0)
	{}

	void init(double x, double y, double xVel, double yVel, int lifetime) {
		x_ = x; y_ = y;
		xVel_ = xVel; yVel_ = yVel;
		framesLeft_ = lifetime;
	}

	void animate() {
		if (!inUse()) return;

		framesLeft_--;
		x_ += xVel_;
		y_ += yVel_;
	}

	bool inUse() const { 
		return framesLeft_ > 0; 
	}

private:
	int framesLeft_;
	double x_, y_;
	double xVel_, yVel_;
};

class ParticlePool
{
public:
	void create(double x, double y, double xVel, double yVel, int lifetime) {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (!particles_[i].inUse()) {
				particles_[i].init(x, y, xVel, yVel, lifetime);
				return;
			}
		}
	}

	void animate() {
		for (int i = 0; i < POOL_SIZE; i++) {
			particles_[i].animate();
		}
	}

private:
	static const int POOL_SIZE = 100;
	Particle particles_[POOL_SIZE];
};

// version 02

class Particle
{
public:
	Particle* getNext() const { 
		return state_.next; 
	}

	void setNext(Particle* next) { 
		state_.next = next; 
	}

	bool animate() {
		if (!inUse()) 
			return false;

		framesLeft_--;
		x_ += xVel_;
		y_ += yVel_;

		return framesLeft_ == 0;
	}

private:
	int framesLeft_;

	union {
		// State when it's in use.
		struct {
			double x, y;
			double xVel, yVel;
		} live;

		// State when it's available.
		Particle* next;
	} state_;
};

class ParticlePool
{
public:
	ParticlePool() {
		// The first one is available.
		firstAvailable_ = &particles_[0];

		// Each particle points to the next.
		for (int i = 0; i < POOL_SIZE - 1; i++) {
			particles_[i].setNext(&particles_[i + 1]);
		}

		// The last one terminates the list.
		particles_[POOL_SIZE - 1].setNext(NULL);
	}

	void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
		// Make sure the pool isn't full.
		assert(firstAvailable_ != NULL);

		// Remove it from the available list.
		Particle* newParticle = firstAvailable_;
		firstAvailable_ = newParticle->getNext();

		newParticle->init(x, y, xVel, yVel, lifetime);
	}

	void animate() {
		for (int i = 0; i < POOL_SIZE; i++) {
			if (particles_[i].animate()) {
				// Add this particle to the front of the list.
				particles_[i].setNext(firstAvailable_);
				firstAvailable_ = &particles_[i];
			}
		}
	}

private:
	Particle* firstAvailable_;
};