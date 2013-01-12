#include "GLFWMouseListener.h"
#include <vector>
#include <GL\glfw.h>

static bool initialised = false;
static std::vector<GLFWMouseListener*> listeners;

void MouseMoveCallback(int x, int y)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		listeners[i]->MouseMove(x, y);
	}
}

void MouseButtonCallback(int button, int action)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		listeners[i]->MouseButton(button, action);
	}
}

void MouseWheelCallback(int pos)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		listeners[i]->MouseWheel(pos);
	}
}

GLFWMouseListener::GLFWMouseListener(void)
{
}

GLFWMouseListener::~GLFWMouseListener(void)
{
	for (int i = 0; i < listeners.size(); ++i)
	{
		if (listeners[i] = this)
		{
			listeners.erase(listeners.begin() + i);
			break;
		}
	}
}

void GLFWMouseListener::MouseInit()
{
	if (!initialised)
	{
		glfwSetMouseButtonCallback(MouseButtonCallback);
		glfwSetMousePosCallback(MouseMoveCallback);
		glfwSetMouseWheelCallback(MouseWheelCallback);
		listeners.push_back(this);
	}
	initialised = true;
}

void GLFWMouseListener::MouseButton(int button, int action) {}
void GLFWMouseListener::MouseMove(int x, int y) {}
void GLFWMouseListener::MouseWheel(int pos) {}
