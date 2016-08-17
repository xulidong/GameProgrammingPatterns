

class Superpower
{
public:
	virtual ~Superpower() {}

protected:
	virtual void activate() = 0;

	void move(double x, double y, double z)
	{
		// Code here...
	}

	void playSound(SoundId sound, double volume)
	{
		// Code here...
	}

	void spawnParticles(ParticleType type, int count)
	{
		// Code here...
	}
};


class SkyLaunch : public Superpower
{
protected:
	virtual void activate()
	{
		// Spring into the air.
		playSound(SOUND_SPROING, 1.0f);
		spawnParticles(PARTICLE_DUST, 10);
		move(0, 0, 20);
	}
};


class Superpower
{
protected:
	double getHeroX()
	{
		// Code here...
	}

	double getHeroY()
	{
		// Code here...
	}

	double getHeroZ()
	{
		// Code here...
	}

	// Existing stuff...
};

class SkyLaunch : public Superpower
{
protected:
	virtual void activate()
	{
		if (getHeroZ() == 0)
		{
			// On the ground, so spring into the air.
			playSound(SOUND_SPROING, 1.0f);
			spawnParticles(PARTICLE_DUST, 10);
			move(0, 0, 20);
		}
		else if (getHeroZ() < 10.0f)
		{
			// Near the ground, so do a double jump.
			playSound(SOUND_SWOOP, 1.0f);
			move(0, 0, getHeroZ() + 20);
		}
		else
		{
			// Way up in the air, so do a dive attack.
			playSound(SOUND_DIVE, 0.7f);
			spawnParticles(PARTICLE_SPARKLES, 1);
			move(0, 0, -getHeroZ());
		}
	}
};