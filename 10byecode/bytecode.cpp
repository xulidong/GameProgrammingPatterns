/*
 * 实现算术运算
 * */

// version 01

class Experession
{
public:
	virtual ~Expression() {}
	virtual double evaluate() = 0;
};

class NumberExpression : public Expression
{
public:
	NumberExpression(double value): value_(value) {}

	virtual double evaluate() {
		return value_;
	}

private:
	double value_;
};

class AdditionExpression : public Expression
{
public:
	AdditionExpression(Expression* left, Expression* right): left_(left), right_(right) {}

	virtual double evaluate() {
		double left = left_->evaluate();
		double right = right_->evaluate();
		return left + right;
	}

private:
	Expression* left_;
	Expression* right_;
};

// version 02
// wizard：0代表玩家而1代表对手
void setHealth(int wizard, int amount);
void setWisdom(int wizard, int amount);
void setAgility(int wizard, int amount);

void playSound(int soundId);
void spawnParticles(int particleType);

enum Instruction
{
	INST_SET_HEALTH = 0x00, // 设置健康值
	INST_SET_WISDOM = 0x01, // 设置智力
	INST_SET_AGILITY = 0x02, // 设置敏捷
	INST_PLAY_SOUND = 0x03, // 播放音效
	INST_SPAWN_PARTICLES = 0x04 // 播放粒子特效
};

class VM
{
public:
	void interpret(char bytecode[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			char instruction = bytecode[i];
			switch (instruction)
			{
			case INST_SET_HEALTH:
				setHealth(0, 100);
				break;

			case INST_SET_WISDOM:
				setWisdom(0, 100);
				break;

			case INST_SET_AGILITY:
				setAgility(0, 100);
				break;

			case INST_PLAY_SOUND:
				playSound(SOUND_BANG);
				break;

			case INST_SPAWN_PARTICLES:
				spawnParticles(PARTICLE_FLAME);
				break;
			}
		}
	}
};

// version 03
class VM
{
public:
	VM():stackSize_(0) {}

	void push(int value) {
		assert(stackSize_ < MAX_STACK);
		stack_[stackSize_++] = value;
	}

	int pop() {
		assert(stackSize_ > 0);
		return stack_[--stackSize_];
	}

	void interpret(char bytecode[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			char instruction = bytecode[i];
			switch (instruction)
			{
			case INST_SET_HEALTH:
			{
				int amount = pop();
				int wizard = pop();
				setHealth(wizard, amount);
				break;
			}

			case INST_SET_WISDOM:
			case INST_SET_AGILITY:
			case INST_PLAY_SOUND:
				playSound(pop());
				break;

			case INST_SPAWN_PARTICLES:
				spawnParticles(pop());
				break;
			}
	}
private:
	static const int MAX_STACK = 128;
	int stackSize_;
	int stack_[MAX_STACK];
};
