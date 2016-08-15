

// version 01 �ı�����
whlile(true) {
	char* command = readCommand();
	handleCommand(command);
}

// version 02 �����¼�(������)
while (true) {
	Event* event = waitForEvent();
	dispatchEvent(event);
}

// version 03 �������ȴ��û������¼�
while (true) {
	processInput();
	update();
	render();
}

// version 04 ��������ʱ��
while (true) {
	double start = getCurrentTime();
	processInput();
	update();
	render();
	sleep(start + MS_PER_FRAME - getCurrentTime());
}

// version 05
double lastTime = getCurrentTime();
while (true) {
	double current = getCurrentTime();
	double elapsed = current - lastTime;
	processInput();
	update(elapsed);
	render();
	lastTime = current;
}

// version 06
double previous = getCurrentTime();
double lag = 0.0;
while (true) {
	double current = getCurrentTime();
	double elapsed = current - previous;
	previous = current;
	lag += elapsed;

	processInput();

	while (lag >= MS_PER_UPDATE)
	{
		update();
		lag -= MS_PER_UPDATE;
	}

	render(lage / MS_PER_UPDATE);
}