
// version 01

class Bjorn
{
public:
	Bjorn():velocity_(0), x_(0), y_(0) {}

	void udpate(World& world, Graphic& graphics){
		switch (Controller::getJoystickDirection()) {
		case DIR_LEFT:
			velocity_ -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			velocity_ += WALK_ACCELERATION;
			break;
		}

		x_ += velocity_;
  		world.resolveCollision(volume_, x_, y_, velocity_);

  		Sprite* sprite = &spriteStand_;
		if (velocity_ < 0) {
			sprite = &spriteWalkLeft_;
		}
		else if (velocity_ > 0) {
			sprite = &spriteWalkRight_;
		}

		graphics.draw(*sprite, x_, y_);
	}

private:
	static const int WALK_ACCELERATION = 1;

	int velocity_;
	int x_, y_;

	Volume volume_;

	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};

// version 02

class InputComponent
{
public:
	void udpate(Bjorn& bjorn) {
		switch (Controller::getJoystickDirection()) {
		case DIR_LEFT:
			velocity_ -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			velocity_ += WALK_ACCELERATION;
			break;
		}
	}

private:
	static const int WALK_ACCELERATION = 1;
};


class Bjorn
{
public:
	Bjorn():velocity_(0), x_(0), y_(0) {}

	void udpate(World& world, Graphic& graphics){
		input_.update(*this);

		x_ += velocity_;
  		world.resolveCollision(volume_, x_, y_, velocity_);

  		Sprite* sprite = &spriteStand_;
		if (velocity_ < 0) {
			sprite = &spriteWalkLeft_;
		}
		else if (velocity_ > 0) {
			sprite = &spriteWalkRight_;
		}

		graphics.draw(*sprite, x_, y_);
	}

private:
	InputComponent input_;

	int velocity_;
	int x_, y_;

	Volume volume_;

	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};

// version 03

class PhysicsComponent
{
public:
	void udpate(Bjorn& bjorn) {
		bjorn.x += bjorn.velocity;
		world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
	}

private:
	Volume volume_;
};

class GraphicsComponent
{
public:
	void update(Bjorn& bjorn, Graphics& graphics) {
		Sprite* sprite = &spriteStand_;
		if (bjorn.velocity < 0) {
			sprite = &spriteWalkLeft_;
		}
		else if (bjorn.velocity > 0) {
			sprite = &spriteWalkRight_;
		}
		graphics.draw(*sprite, bjorn.x, bjorn.y);
	}

private:
	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};

class Bjorn
{
public:
	Bjorn():velocity_(0), x_(0), y_(0) {}

	void udpate(World& world, Graphic& graphics){
		input_.update(*this);
		physics_.update(*this, world);
		graphics_.update(*this, graphics);
	}

private:
	InputComponent input_;
	PhysicsComponent physics_;
	GraphicsComponent graphics_;

	int velocity_;
	int x_, y_;
};

// version 04
class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(Bjorn& bjorn) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
	virtual void update(Bjorn& bjorn)
	{
		switch (Controller::getJoystickDirection())
		{
		case DIR_LEFT:
			bjorn.velocity -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			bjorn.velocity += WALK_ACCELERATION;
			break;
		}
	}

private:
	static const int WALK_ACCELERATION = 1;
};

class Bjorn
{
public:
	Bjorn(InputComponent* input):input_(input), velocity_(0), x_(0), y_(0) {}

	void udpate(World& world, Graphic& graphics){
		input_->update(*this);
		physics_.update(*this, world);
		graphics_.update(*this, graphics);
	}

private:
	InputComponent* input_;
	PhysicsComponent physics_;
	GraphicsComponent graphics_;

	int velocity_;
	int x_, y_;
};

Bjorn* bjorn = new Bjorn(new PlayerInputComponent());

// verion 05
class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(Bjorn& bjorn) = 0;
};

class PlayerInputComponent : public InputComponent
{
public:
	virtual void update(Bjorn& bjorn)
	{
		switch (Controller::getJoystickDirection())
		{
		case DIR_LEFT:
			bjorn.velocity -= WALK_ACCELERATION;
			break;

		case DIR_RIGHT:
			bjorn.velocity += WALK_ACCELERATION;
			break;
		}
	}

private:
	static const int WALK_ACCELERATION = 1;
};

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void update(GameObject& obj, World& world) = 0;
};

class BjornPhysicsComponent : public PhysicsComponent
{
public:
	virtual void update(GameObject& obj, World& world)
	{
		bjorn.x += bjorn.velocity;
		world.resolveCollision(volume_, bjorn.x, bjorn.y, bjorn.velocity);
	}

private:
	Volume volume_;
};

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {}
	virtual void update(GameObject& obj, Graphics& graphics) = 0;
};

class BjornGraphicsComponent : public GraphicsComponent
{
public:
	virtual void update(Bjorn& bjorn, Graphics& graphics) {
		Sprite* sprite = &spriteStand_;
		if (bjorn.velocity < 0) {
			sprite = &spriteWalkLeft_;
		}
		else if (bjorn.velocity > 0) {
			sprite = &spriteWalkRight_;
		}
		graphics.draw(*sprite, bjorn.x, bjorn.y);
	}

private:
	Sprite spriteStand_;
	Sprite spriteWalkLeft_;
	Sprite spriteWalkRight_;
};

class GameObject
{
public:
	GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) 
	: input_(input),
	physics_(physics),
	graphics_(graphics),
	velocity_(0), 
	x_(0), 
	y_(0)
	{}


	void udpate(World& world, Graphic& graphics){
		input_->update(*this);
		physics_->update(*this, world);
		graphics_->update(*this, graphics);
	}

private:
	InputComponent* input_;
	PhysicsComponent* physics_;
	GraphicsComponent* graphics_;

	int velocity_;
	int x_, y_;
};

GameObject* createBjorn()
{	
	return new GameObject(new PlayerInputComponent(),
		new BjornPhysicsComponent(),
		new BjornGraphicsComponent());
}

/*
 * 组件之间通信
 * 1 通过修改容器对象的状态
 * 2 将其他组件作为参数传入
 * 3 通过容器调用其他组件
 * 4 消息
 */

 

