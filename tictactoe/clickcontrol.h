#ifndef _CLICKCONTROL__H
#define _CLICKCONTROL__H

struct Clickcontrol {
	//2players 3*3
	void create();
	bool handleClick(int mouseX, int mouseY, int& count);
	void resetClicks(int& count);
	void draw();
	void checkwin(int count);
	void AIClick(int& count);
	void AIsmartclick(int& count);
	//2players 10*10
	void createmore();
	void drawmore();
	void checkwinmore(int count);
	void handleClickmore(int mouseX, int mouseY, int& count);
	void resetClicksmore(int& count);
};
#endif // !_CLICKCONTROL__H


