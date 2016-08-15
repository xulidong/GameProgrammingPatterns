/*
 * 双缓冲解决的核心问题:
 * 1 状态被修改的同时被请求;
 * 2 当负责修改的代码请求正在修改的同样的状态;
 * */

// version 01

class Framebuffer
{
public:
	FremaBuffer() {
		clear();
	}

	void clear() {
		for (int i = 0; i < WIDTH * HEIGHT; i++) {
			pixels_[i] = WHITE;
		}
	}

	void draw(int x, int y) {
		pixels_[(WIDTH * y) + x] = BLACK;
	}

	const char* getPixels() {
		return pixels_;
	}

private:
	static const int WIDTH = 160;
	static const int HEIGHT = 120;
	
	char pixels_[WIDTH * HEIGHT];
};


class Scene
{
public:
	void draw() {
		buffer_.clear();
		 
		buffer_.draw(1, 1);
		buffer_.draw(4, 1);
		buffer_.draw(1, 3);
		buffer_.draw(2, 4);
		buffer_.draw(3, 4);
		buffer_.draw(4, 3);
	}

	Framebuffer& getBuffer() { 
		return buffer_; 
	}

private:
	Framebuffer buffer_;
};

// version 02


class Scene
{
public:
	Scene() : current_(&buffers_[0]), next_(&buffers_[1]){}

	void draw() {
		buffer_.clear();

		buffer_.draw(1, 1);
		buffer_.draw(4, 1);
		buffer_.draw(1, 3);
		buffer_.draw(2, 4);
		buffer_.draw(3, 4);
		buffer_.draw(4, 3);

		swap();
	}

	Framebuffer& getBuffer() {
		return *current_;
	}

private:
	void swap() {
		FrameBuffer* temp = current_;
		current_ = next_;
		next_ = temp;
	}

	FrameBuffer* buffers_[2];
	FrameBuffer* current_;
	FrameBuffer* next_;
};


// version 03 
class Stage
{
public:
	void add(Actor* actor, int index) {
		actors_[index] = actor;
	}

	void update() {
		for (int i = 0; i < NUM_ACTORS; i++) {
			actors_[i]->update();
			actors_[i]->reset();
		}
	}

private:
	static const int NUM_ACTORS = 3;

	Actor* actors_[NUM_ACTORS];
};


class Actor
{
public:
	Actor() : slapped_(false) {}

	virtual ~Actor() {}
	virtual void update() = 0;

	void reset() { 
		slapped_ = false; 
	}

	void slap(){ 
		slapped_ = true; 
	}

	bool wasSlapped() { 
		return slapped_; 
	}

private:
	bool slapped_;
};

class Comedian : public Actor
{
public:
	void face(Actor* actor) { 
		facing_ = actor; 
	}

	virtual void update() {
		if (wasSlapped()) 
			facing_->slap();
	}

private:
	Actor* facing_;
};

Stage stage;

Comedian* harry = new Comedian();
Comedian* baldy = new Comedian();
Comedian* chump = new Comedian();

harry->face(baldy);
baldy->face(chump);
chump->face(harry);

stage.add(harry, 0);
stage.add(baldy, 1);
stage.add(chump, 2);

/*
stage.add(harry, 2);
stage.add(baldy, 1);
stage.add(chump, 0);
*/

harry->slap();

stage.update();

/*
Stage updates actor 0 (Harry)
Harry was slapped, so he slaps Baldy
Stage updates actor 1 (Baldy)
Baldy was slapped, so he slaps Chump
Stage updates actor 2 (Chump)
Chump was slapped, so he slaps Harry
Stage update ends

Stage updates actor 0 (Chump)
Chump was not slapped, so he does nothing
Stage updates actor 1 (Baldy)
Baldy was not slapped, so he does nothing
Stage updates actor 2 (Harry)
Harry was slapped, so he slaps Baldy
Stage update ends
*/

class Actor
{
public:
	Actor() : currentSlapped_(false) {}

	virtual ~Actor() {}
	virtual void update() = 0;

	void swap() {
		currentSlapped_ = nextSlapped_;
		nextSlapped_ = false;
	}

	void slap() { 
		nextSlapped_ = true; 
	}

	bool wasSlapped() { 
		return currentSlapped_; 
	}

private:
	bool currentSlapped_;
	bool nextSlapped_;
};

void Stage::update()
{
	for (int i = 0; i < NUM_ACTORS; i++) {
		actors_[i]->update();
	}

	for (int i = 0; i < NUM_ACTORS; i++) {
		actors_[i]->swap();
	}
}