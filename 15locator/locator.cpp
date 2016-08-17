

// version 01

class Audio
{
public:
	virtual ~Audio() {}
	virtual void playSound(int soundID) = 0;
	virtual void stopSound(int soundID) = 0;
	virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio
{
public:
	virtual void playSound(int soundID)
	{
	// Play sound using console audio api...
	}

	virtual void stopSound(int soundID)
	{
	// Stop sound using console audio api...
	}

	virtual void stopAllSounds()
	{
	// Stop all sounds using console audio api...
	}
};


class Locator
{
public:
	static Audio* getAudio() {
		return service_;
	}

	static void provide(Audio* service) {
		service_ = service;
	}

private:
	static Audio* service_;
};

ConsoleAudio *audio = new ConsoleAudio();
Locator::provide(audio);

Audio *audio = Locator::getAudio();
audio->playSound(VERY_LOUD_BANG);

// version 02

class NullAudio: public Audio 
{
public:
	virtual void playSound(int soundId) {}
	virtual void stopSound(int soundId) {}
	virtual void stopAllSounds() {}
};

class Locator
{
public:
	static void init() {
		service_ = &nullService_;
	}

	static Audio& getAudio() {
		return service_;
	}

	static void provide(Audio* service) {
		if (service == NULL) {
			service_ = &nullService_;
		} else {
			service_ = service;
		}
	}

private:
	static Audio* service_;
	static NullAudio nullService_;
};

// version 03

class LoggeAduio : public Audio
{
public:
	LoggeAduio(Audio &wrapperd) : wrapperd_(wrapperd) {}

	virtual void playSound(int soundID) {
		log("play sound");
		wrapped_.playSound(soundID);
	}

	virtual void stopSound(int soundID) {
		log("stop sound");
		wrapped_.stopSound(soundID);
	}

	virtual void stopAllSounds() {
		log("stop all sounds");
		wrapped_.stopAllSounds();
	}

private:
	void log(const char* message) {
	// Code to log message...
	}

	Audio &wrapped_;
};

void enableAudioLogging()
{
  // Decorate the existing service.
  Audio *service = new LoggedAudio(Locator::getAudio());

  // Swap it in.
  Locator::provide(service);
}