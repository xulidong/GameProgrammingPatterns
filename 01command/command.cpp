/*
A command is a reified method call  that��s a method call wrapped in an object.
*/

// version 01
// ��Ӧ��Ұ�������
void InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) {
		jump();
	}
	else if (isPressed(BUTTON_Y)) {
		fireGun();
	}
	else if (isPressed(BUTTON_A)) {
		swapWeapon();
	}
	else if (isPressed(BUTTON_B)) {
		lurchIneffectively();
	}
	else {
		// ...
	}
}

// version 02
// ֧����Ҹļ�
class Command 
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
};

class JumpCommand : public Command
{
	virtual void execute() { 
		jump();
	}
};

class FireCommand : public Command
{
public:
	virtual void execute() { 
		fireGun(); 
	}
};

class InputHandler
{
public:
	void handleInput();

private:
	Command* buttonX_;
	Command* buttonY_;
	Command* buttonA_;
	Command* buttonB_;
};

void InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) {
		buttonX_->execute();
	}
	else if (isPressed(BUTTON_Y)) {
		buttonY_->execute();
	}
	else if (isPressed(BUTTON_A)) {
		buttonA_->execute();
	}
	else if (isPressed(BUTTON_B)) {
		buttonB_->execute();
	}
	else {
		// ...
	}
}

// version 03
// ֧�����ѡ��Ҫ�����Ľ�ɫ
class Command{
public:
	virtual ~Command(){}
	virtual excute(GameActor& actor) = 0;
};

class JumpCommand : public Command
{
	virtual void execute(GameActor& actor) {
		actor.jump();
	}
};

Command* InputHandler::handleInput()
{
	if (isPressed(BUTTON_X)) {
		return buttonX_;
	} if (isPressed(BUTTON_Y)) {
		return buttonY_;
	}
	if (isPressed(BUTTON_A)) {
		return buttonA_;
	}
	if (isPressed(BUTTON_B)) {
		return buttonB_;
	} else {
		return NULL;
	}
}

InputHandler inputHandler;
Command* command = inputHandler.handleInput();
if (command) {
	command->execute(actor);
}

// version 04
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
	virtual void undo() = 0;
};

// ֧�ֳ���������(�ƶ���Ϸ�е�ĳ����Ԫ��)
class MoveUnitCommand : public Command 
{
public:
	MoveUnitCommand(Unit* unit, int x, int y) : unit_(unit), xBefore_(0), yBefore_(0), x_(x), y_(y) {}
	virtual void execute() 
	{
		xBefore_ = unit_->x();
		yBefore_ = unit_->y();
		unit->moveTo(x_, y_);
	}
private:
	Unit* unit_;
	int xBefore_, yBefore_;
	int x_, y_;
};

Command* handleInput()
{
	Unit* unit = getSelectedUnit();

	if (isPressed(BUTTON_UP)) {
		// Move the unit up one.
		int destY = unit->y() - 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	if (isPressed(BUTTON_DOWN)) {
		// Move the unit down one.
		int destY = unit->y() + 1;
		return new MoveUnitCommand(unit, unit->x(), destY);
	}

	// Other moves...

	return NULL;
}

