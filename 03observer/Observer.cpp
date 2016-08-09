/*
 *
 **/

// 成就系统实现方式



// version01

class Observer
{
public:
	virtual ~Observer(){}
	virtual void onNotify(const Entity& entity, Event event) = 0;
};

class Achievements : public Observer
{
public:
	virtual void onNotify(const Entity& entity, Event event){
		switch(event) {
			case EVENT_ENTITY_FELL:
			if (entity.isHero() && heroIsOnBridge_) {
				unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
			}
			break;
		}
	}

private:
	void unlock(Achievement achievement) {
		// unlock
	}
	bool heroIsOnBridge_;
};


class Subject
{
public:
	void addObserver(Observer* observer) {
		// add
	}

	void removeObserver(Observer* observer) {
		// remove
	}

	void notify(const Entity& entity, Event event) {
		for (int i = 0; i < numObservers_; i++) {
			observers_[i]->onNotify(entity, event);
		}
	}
private:
	Observer* observers_[MAX_OBSERVERS];
	int numObservers_;
};


class Physics : public Subject
{
public:
	void updateEntity(Entity& entity) {
		bool wasOnSurface = entity.isOnSurface();
		entity.accelerate(GRAVITY);
		entity.update();
		if (wasOnSurface && !entity.isOnSurface()) {
			notify(entity, EVENT_START_FALL);
		}
	}
};


// version02

class Subject
{
public:
	Subject() : head_(NULL) {}
	void addObserver(Observer* observer) {
		observer->next = head_;
		head_ = observer;
	}

	void Subject::removeObserver(Observer* observer) {
		if (head_ == observer) {
			head_ = observer->next_;
			observer->next_ = NULL;
		} else {
			Observer* current = head_;
			while(current != NULL) {
				current->next_ = observer->next_;
				observer->next_ = NULL;
			}
			current = current->next_;
		}
	}

	void Subject::notify(const Entity& entity, Event event) {
		Observer* observer = head_;
		while (observer != NULL) {
			observer->onNotify(entity, event);
			observer = observer->next_;
		}
	}
private:
	Observer* head_;
};


class Observer
{
	friend class Subject;
public:
	Observer: next_(NULL) {}
private:
	Observer* next_;
};

/*
观察者模式解耦各系统之间的关联，防止代码分散在代码中，模块化一个功能
*/