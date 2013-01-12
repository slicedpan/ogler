#pragma once
class GLFWMouseListener
{
public:
	GLFWMouseListener(void);
	~GLFWMouseListener(void);
	virtual void MouseButton(int button, int action);
	virtual void MouseMove(int x, int y);
	virtual void MouseWheel(int pos);
protected:
	void MouseInit();
};

