#include "GUIElement.h"

GUIElement::GUIElement()
	: colour(1, 1, 1, 1), 
	textColour(0, 0, 0, 1),
	Width(width),
	Height(height)
{
}

GUIElement::~GUIElement(void)
{
}

bool GUIElement::MouseClick(int x, int y, int button)
{
	return false;
}

