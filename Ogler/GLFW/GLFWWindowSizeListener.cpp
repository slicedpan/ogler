#include "GLFWWindowSizeListener.h"
#include <GL\glfw.h>

static std::vector<GLFWWindowSizeListener*> _listeners;
static bool initialised = false;

class _resizer
{
public:
	void _resize(int width, int height, GLFWWindowSizeListener* listener)
	{
		listener->_resize(width, height);
	}
};

void ResizeCallback(int newWidth, int newHeight)
{
	_resizer r;
	for (int i = 0; i < _listeners.size(); ++i)
	{
		r._resize(newWidth, newHeight, _listeners[i]);
	}
}

void GLFWWindowSizeListener::InitListen()
{
	if (!initialised)
	{
		glfwSetWindowSizeCallback(ResizeCallback);
		initialised = true;
	}
}

GLFWWindowSizeListener::GLFWWindowSizeListener(void)
{
	_listeners.push_back(this);
}


GLFWWindowSizeListener::~GLFWWindowSizeListener(void)
{
	for (int i = 0; i < _listeners.size(); ++i)
	{
		if (_listeners[i] == this)
		{
			_listeners.erase(_listeners.begin() + i);
			break;
		}
	}
}

