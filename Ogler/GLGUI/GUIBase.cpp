#include "GUIBase.h"
#include "GUITray.h"
#include <GL\glew.h>
#include <tuple>

GUIBase::GUIBase(void)
	: Trays(trays)
{
}

GUIBase::~GUIBase(void)
{
}

void GUIBase::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto iter = trays.begin(); iter != trays.end(); ++iter)
	{
		iter->second->Draw();
	}	
}

void GUIBase::MouseClick(int x, int y, int button)
{
	for (auto iter = trays.begin(); iter != trays.end(); ++iter)
	{
		if (iter->second->MouseClick(x, y, button))
		{
			focusTray = iter->second;
			break;
		}
	}
}

void GUIBase::MouseRelease(int x, int y, int button)
{
	if (focusTray)
		focusTray->MouseRelease(x, y, button);
	focusTray = 0;
}

void GUIBase::MouseMove(int x, int y)
{
	if (focusTray)
		focusTray->MouseMove(x, y);
}

void GUIBase::Update()
{
	for (auto iter = trays.begin(); iter != trays.end(); ++iter)
	{
		iter->second->Update();
	}	
}

Vec2& GUIBase::GetScreenSize()
{
	return screenSize;
}

GUITray& GUIBase::CreateTray(int xPos, int yPos, unsigned int growDirection, std::string name)
{
	trays.emplace(std::pair<std::string, GUITray*>(name, new GUITray(xPos, yPos, growDirection)));	
	trays[name]->owner = this;
	return *(trays[name]);
}

void GUIBase::SetWindowSize(int width, int height)
{
	currentWidth = width;
	currentHeight = height;
	screenSize[0] = width;
	screenSize[1] = height;
}



