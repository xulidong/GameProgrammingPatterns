
// version 01

class GameEntity
{
public:
	GameEntity(AIComponent* ai, PhysicsComponent* physics, RenderComponent* render) 
		: ai_(ai), physics_(physics), render_(render)
	{}

	AIComponent* ai() { 
		return ai_; 
	}

	PhysicsComponent* physics() { 
		return physics_; 
	}

	RenderComponent* render() { 
		return render_; 
	}

private:
	AIComponent* ai_;
	PhysicsComponent* physics_;
	RenderComponent* render_;
};

class AIComponent
{
public:
	void update() { /* Work with and modify state... */ }

private:
	// Goals, mood, etc. ...
};

class PhysicsComponent
{
public:
	void update() { /* Work with and modify state... */ }

private:
	// Rigid body, velocity, mass, etc. ...
};

class RenderComponent
{
public:
	void render() { /* Work with and modify state... */ }

private:
	// Mesh, textures, shaders, etc. ...
};

while (!gameOver)
{
	// Process AI.
	for (int i = 0; i < numEntities; i++)
	{
		entities[i]->ai()->update();
	}

	// Update physics.
	for (int i = 0; i < numEntities; i++)
	{
		entities[i]->physics()->update();
	}

	// Draw to screen.
	for (int i = 0; i < numEntities; i++)
	{
		entities[i]->render()->render();
	}

	// Other game loop machinery for timing...
}

// version 02  提高缓存命中率

AIComponent* aiComponents = new AIComponent[MAX_ENTITIES];
PhysicsComponent* physicsComponents = new PhysicsComponent[MAX_ENTITIES];
RenderComponent* renderComponents = new RenderComponent[MAX_ENTITIES];

while (!gameOver)
{
	// Process AI.
	for (int i = 0; i < numEntities; i++)
	{
		aiComponents[i].update();
	}

	// Update physics.
	for (int i = 0; i < numEntities; i++)
	{
		physicsComponents[i].update();
	}

	// Draw to screen.
	for (int i = 0; i < numEntities; i++)
	{
		renderComponents[i].render();
	}

	// Other game loop machinery for timing...
}


// other example

class Particle
{
public:
	void update() { /* Gravity, etc. ... */ }
	// Position, velocity, etc. ...
};

class ParticleSystem
{
public:
	ParticleSystem() : numParticles_(0)
	{}

	void update() {
		for (int i = 0; i < numParticles_; i++)
		{
			particles_[i].update();
		}
	}

	void activateParticle(int index)
	{
		// Shouldn't already be active!
		assert(index >= numActive_);

		// Swap it with the first inactive particle
		// right after the active ones.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;

		// Now there's one more.
		numActive_++;
	}

	void deactivateParticle(int index)
	{
		// Shouldn't already be inactive!
		assert(index < numActive_);

		// There's one fewer.
		numActive_--;

		// Swap it with the last active particle
		// right before the inactive ones.
		Particle temp = particles_[numActive_];
		particles_[numActive_] = particles_[index];
		particles_[index] = temp;
	}

private:
	static const int MAX_PARTICLES = 100000;

	int numParticles_;
	Particle particles_[MAX_PARTICLES];
};

// other sample

// version 01
class AIComponent
{
public:
	void update() { /* ... */ }

private:
	Animation* animation_;
	double energy_;
	Vector goalPos_;

	LootType drop_;
	int minDrops_;
	int maxDrops_;
	double chanceOfDrop_;
};

// version 02
/* 
 * "冷/热分割"： 这个点子来源于将数据结构划分为两个分离的部分。 第一部分保存“热”数据，那些每帧都要调用的数据。 剩下的片段被称为“冷”数据，在那里的任何数据使用的更少。
 * */
class AIComponent
{
public:
	// Methods...
private:
	Animation* animation_;
	double energy_;
	Vector goalPos_;

	LootDrop* loot_;
};

class LootDrop
{
	friend class AIComponent;
	LootType drop_;
	int minDrops_;
	int maxDrops_;
	double chanceOfDrop_;
};