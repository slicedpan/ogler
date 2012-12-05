#pragma once

#include <vector>

class _resizer;

class GLFWWindowSizeListener
{
public:
	GLFWWindowSizeListener(void);
	~GLFWWindowSizeListener(void);
	friend class _resizer;
	void InitListen();
protected:
	virtual void _resize(int width, int height) {}
};

