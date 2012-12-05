#pragma once

#include "../svl/svl.h"
#include "GUITray.h"

class GUIBase;

class GUIElement
{
public:
	GUIElement();
	~GUIElement(void);
	virtual void Draw(Vec2& position) = 0;
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetColour(Vec4& colour) { this->colour = colour; }
	void SetTextColour(Vec4& colour) { this->textColour = colour; }
	virtual bool MouseClick (int x, int y, int button);
protected:
	int width;
	int height;
	Vec4 colour;
	Vec4 textColour;
	GUIBase* owner;
public:
	const int& Width;
	const int& Height;
private:	
	friend void GUITray::AddElement(GUIElement* element);
};

