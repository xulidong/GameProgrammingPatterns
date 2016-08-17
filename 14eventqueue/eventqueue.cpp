
// version 01

class Audio 
{
public:
	static void playSound(SoundId id, int volume) {
		ResourceId  resource = loadSound(id);
		int channel = findOpenChannel();
		if (channel == -1) 
			return
		startSound(resource, channel, volume);
	}
};

class Menu
{
public:
	void onSelect(int index) {
		Audio::playSound(SOUND_BLOOP, VOL_MAX);
	}
};

// version 02

struct PlayMessage
{
	SoundId id;
	int volume;
};

class Audio
{
public:
	static void init() {
		numPending_ = 0;
	}

	static void playSound(SoundId id, int volume) {
		assert(numPending_ < MAX_PENDING);

		pending_[numPending_].id = id;
  		pending_[numPending_].volume = volume;
		numPending_++;
	}

	static void update() {
		for (int i = 0; i < numPending_; i++) {
			ResourceId  resource = loadSound(pending_[i].id);
			int channel = findOpenChannel();
			if (channel == -1) 
				return
			startSound(resource, channel, volume);
		}
		numPending_ = 0;
	}
private:
	static const int MAX_PENDING = 16;
	static PlayMessage pending_[MAX_PENDING];
	static int numPending_;
}

// version 03

class Audio
{
public:
	static init() {
		head_ = 0;
		tail_ = 0;
	}

	void playSound() {
		assert(tail_ < MAX_PENDING);
		pending_[tail_].id = id;
  		pending_[tail_].volume = volume;
		tail_++;
	}

	void update() {
		if (head_ == tail_)
			return

		ResourceId resource = loadSound(pending_[head_].id);
		int channel = findOpenChannel();
		if (channel == -1)
			return;
		startSound(resource, channel, pending_[head_].volume);
		head_++;
	}

private:
	static int head_;
	static int tail_;
};


// version 04

void Audio::playSound() {
	assert((tail_ + 1) % MAX_PENDING != head_);
	pending_[tail_].id = id;
	pending_[tail_].volume = volume;
	tail_ = (tail_ + 1) % MAX_PENDING;
}

void Audio::update() {
	if (head_ == tail_)
		return

	ResourceId resource = loadSound(pending_[head_].id);
	int channel = findOpenChannel();
	if (channel == -1)
		return;
	startSound(resource, channel, pending_[head_].volume);
	head_++;
}

// version 04
void  Audio::playSound(SoundId id, int volume){
	for (int i = head_; i != tail_; i = (i + 1) % MAX_PENDING) {
		if (pending_[i].id == id) {
			pending_[i].volume = max(volume, pending_[i].volume);
			return
		}
	}
}