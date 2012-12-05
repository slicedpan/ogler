#pragma once

#include <vector>
#include <string>
#include <map>
#include "../MiscUtils.h"
#include "../svl/SVL.h"

class GUITray;

class GUIBase
{
public:
	GUIBase(void);
	~GUIBase(void);
	void Draw();
	void Update();
	void MouseMove(int x, int y);
	void MouseClick(int x, int y, int button);
	void MouseRelease(int x, int y, int button);
	GUITray& CreateTray(int xPos, int yPos, unsigned int growDirection, std::string name);	
	MapWrapper<std::string, GUITray*> Trays;
	Vec2& GetScreenSize();
private:
	std::map<std::string, GUITray*> trays;
	GUITray* focusTray;	
	void SetWindowSize(int width, int height);
	friend class GLFWEngine;
	friend class GUITray;
	friend class GUIElement;
	int currentWidth;
	int currentHeight;	
	Vec2 screenSize;
};



