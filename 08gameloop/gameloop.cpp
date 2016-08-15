

// version 01 文本命令
whlile(true) {
	char* command = readCommand();
	handleCommand(command);
}

// version 02 输入事件(鼠标键盘)
while (true) {
	Event* event = waitForEvent();
	dispatchEvent(event);
}

// version 03 不阻塞等待用户输入事件
while (true) {
	processInput();
	update();
	render();
}

// version 04 设置休眠时间
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