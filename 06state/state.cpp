/*
 * FSM应用场景：
 * 1 你有个实体，它的行为基于一些内在状态；
 * 2 状态可以被严格的分割为相对较少的不相干项目；
 * 3 实体响应一系列输入或事件。
 **/

// 未使用状态模式之前，增加功能会让代码变得混乱

// version 01 按B键跳跃
void Heroine::handleInput(Input input) {
	if (input == PRESS_B) {
		yVelocity_ = JUMP_VELOCITY;
		setGraph(IMAGE_JUMP);
	}
}

// version 02 防止空气跳
void Heroine::handleInput(Input input) {
	if (input == PRESS_B) {
		if (!isJumping_) {
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_JUMP);
		}
	}
}


// version 03 按下键时，在地上时卧倒，松开下键的时候站起来
void Heroine::handleInput(Input input) {
	if (input == PRESS_B and !isJumping_) {
		if (!isJumping_) {
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_JUMP);
		}
	} 
	else if (input == PRESS_DOWN) {
		if (!isJumping_) {
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_DUCK);
		}
	}
	else if (input == RELEASE_DOWN) {
		setGraph(IMAGE_STAND);
	}
}

// version 04 防止卧倒时直接跳起
void Heroine::handleInput(Input input)
{
	if (input == PRESS_B) {
		if (!isJumping_ && !isDucking_)
		{
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_JUMP);
		}
	}
	else if (input == PRESS_DOWN) {
		if (!isJumping_)
		{
			isDucking_ = true;
			setGraphics(IMAGE_DUCK);
		}
	}
	else if (input == RELEASE_DOWN) {
		if (isDucking_)
		{
			isDucking_ = false;
			setGraphics(IMAGE_STAND);
		}
	}
}

// version 05  按下下键，英雄能够做速降攻击
void Heroine::handleInput(Input input)
{
	if (input == PRESS_B) {
		if (!isJumping_ && !isDucking_) {
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_JUMP);
		}
	}
	else if (input == PRESS_DOWN) {
		if (!isJumping_) {
			isDucking_ = true;
			setGraphics(IMAGE_DUCK);
		}
		else {
			isJumping_ = false;
			setGraphics(IMAGE_DIVE);
		}
	}
	else if (input == RELEASE_DOWN) {
		if (isDucking_)
		{
			isDucking_ = false;
			setGraphics(IMAGE_STAND);
		}
	}
}


// 状态模式
// version 01

enum State {
	STATE_STANDING,
	STATE_JUMPING,
	STATE_DUCKING,
	STATE_DIVING
};

void Heroine : handleInput(Input input) {
	switch (state_) {
	case STATE_STANDING:
		if (input == PRESS_B) {
			state_ = STATE_JUMPING;
			yVelocity_ = JUMP_VELOCITY;
			setGraph(IMAGE_JUMP);
		}
		else if (input == PRESS_DOWN) {
			state_ = STATE_DUCKING;
			chargeTime_ = 0;
			setGraphics(IMAGE_DUCK);
		}
		break;
	case STATE_JUMPING:
		if (input == PRESS_DOWN) {
			state_ = STATE_DIVING;
			setGraphics(IMAGE_DIVE);
		}
		break;
	case STATE_DUCKING:
		if (input == RELEASE_DOWN) {
			state_ = STATE_STANDING;
			setGraphics(IMAGE_STAND);
		}
		break;
	}
}

void Heroine::update() {
	if (state_ == STATE_DUCKING) {
		chargeTime_++;
		if (chargeTime_ > MAX_CHARGE) {
			superBomb();
		}
	}
}

// version 02

class HeroineState 
{
public:
	virtual ~HeroineSate() {}
	virtual void handleInput(Heroine& heroine, Input input) {}
	virtual void update(Heroine& heroine) {}

	static StandingState standing;
	static DuckingState ducking;
	static JumpingState jumping;
	static DivingState diving;
};

class DuckingState : public HeroineState 
{
public:
	DuckingState() : chargeTiime_(0) {}

	virtual void handleInput(Heroine& heroine, Input input) {
		if (input == RELEASE_DOWN) {
			heroine.state_ = &HeroineState::standing;
			heroine.setGraphics(IMAGE_STAND);
		}
	}

	virtual void update(Heroine& heroine) {
		chargeTime++;
		if (chargeTime_ > IMAGE_CHARGE) {
			heroine.superBomb();
		}
	}

private:
	int chargeTime_;
};

class Heroine
{
public:
	virtual void handleInput(Input input) {
		state_->handleInput(*this, input);
	}

	void update() {
		state_->update(*this);
	}

private:
	HeroineState* state_;
};


// version 03 每次返回新的状态对象，防止多个英雄拥有相同状态时数据相互覆盖
HeroineState* StandingState::handleInput(Heroine& heroine, Input input) {
	if (input == PRESS_DOWN) {
		heroine.setGraphics(IMAGE_DUCKING);
		return new DuckineState();
	}
	return NULL;
}

void Heroine::handleInput(Input input) {
	HeroineState* state = state->handleInput(*this, input);
	if (state != NULL) {
		delete state_;
		state_ = state;
	}
}

// version 04 添加enter和exit方法
class StandingStandingState::public HeroineState
{
public:
	virtual void enter(Heroine& heroine) {
		heroine.setGraphics(IMAGE_STAND);
	}
	virtual void exit(Heroine& heroine) {
		//...
	}
};

HeroineState* DuckingState::handleInput(Heroine& heroine, Input input)
{
	if (input == RELEASE_DOWN) {
		return new StandingState();
	}
}

void Heroine::handleInput(Input input) {
	HeroineState* state = state->handleInput(*this, input);
	if (state != NULL) {
		state_->exit(*this);
		delete state_;
		state_ = state;
		state_->enter(*this);
	}
}

// version 05  并发状态机
class Heroine
{
private:
	HeroineState* state_;
	HeroineState* equipment_;
};

void Heroine::handleInput(Input input) {
	state_->handleInput(*this, input);
	equipment_->handleInput(*this, input);
}

// version 06 分层状态机
class OnGroundState : public HeroineState
{
public:
	virtual void handleInput(Heroine& heroine, Input input) {
		if (input == PRESS_B) {
			// Jump
		}
		else if (input == PRESS_DOWN) {
			// Duck
		}
	}
};

class DuckingState : public OnGroundState
{
public:
	virtual void handleInput(Heroine& heroine, Input input) {
		if (input == RELEASE_DOWN) {
			// Stand up...
		}
		else {
			// Didn't handle input, so walk up hierarchy.
			OnGroundState::handleInput(heroine, input);
		}
	}
};

// version 07  存储之前的状态
/* 
有限自动机有一个指针指向状态，下推自动机有一栈指针。 
在FSM中，转换到新状态代替了之前的那个。 下推状态机不仅能完成那个，还能给你两个额外操作：
1 你可以将新状态推入栈中。“当前的”状态总是在栈顶，所以这会转到新状态。但它让之前的状态待在栈中而不是销毁它。
2 你可以弹出最上面的状态。这个状态会被销毁，它下面状态成为新状态。
*/

