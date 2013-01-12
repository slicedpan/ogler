#include "GLFWEngine.h"
#include "../WindowSettings.h"
#include <GL\glew.h>
#include <GL\glfw.h>
#include <boost\format.hpp>

GLFWEngine::GLFWEngine(void) : BasicEngine(new GLFWTimerProvider()),
	currentSettings(new WindowSettings()),
	Window(*currentSettings)
{
	WindowSettings w;

	if (!InitWindow(w))
		printf("Could not open window!");

	KeyInit();
	MouseInit();
	InitListen();
}

GLFWEngine::GLFWEngine(WindowSettings& w) : BasicEngine(new GLFWTimerProvider()),
	currentSettings(new WindowSettings()),
	Window(*currentSettings)
{
	if (!InitWindow(w))
		printf("Could not open window");

	KeyInit();
	MouseInit();
	InitListen();
}



int GLFWEngine::InitWindow(WindowSettings& w)
{

	if (!glfwInit())
		throw;

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, w.OpenGLVersionMajor);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, w.OpenGLVersionMinor);

	glfwOpenWindowHint(GLFW_OPENGL_CORE_PROFILE, 0);
	glfwOpenWindowHint(GLFW_OPENGL_COMPAT_PROFILE, 1);

	if (w.CoreProfile)
	{
		glfwOpenWindowHint(GLFW_OPENGL_CORE_PROFILE, 1);
		glfwOpenWindowHint(GLFW_OPENGL_COMPAT_PROFILE, 0);
	}

	int windowType = w.Fullscreen ? GLFW_FULLSCREEN: GLFW_WINDOW;

	int err = glfwOpenWindow(w.Width, w.Height, w.RedBits, w.GreenBits, w.BlueBits, w.AlphaBits, w.DepthBits, w.StencilBits, windowType);

	if (w.Title == "")
	{
		boost::format fmter("OpenGL %1%.%2% Context, %3% mode");
		int glMinor, glMajor;
		char modeString[] = "Compatibility";
		glMinor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR);
		glMajor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR);		
		if (glfwGetWindowParam(GLFW_OPENGL_CORE_PROFILE))
			sprintf(modeString, "Core");
		fmter % glMajor % glMinor % modeString;
		w.Title = fmter.str();
	}
	glfwSetWindowTitle(w.Title.c_str());

	*currentSettings = w;
	glewExperimental = true;
	GLenum glewErr = glewInit();
	if (glewErr != GLEW_OK)
	{
		printf("Glew Error: %s\n", glewGetErrorString(glewErr));
		return 1;
	}

	static int val = (int)__glewBindBuffer;
	static int* loc = (int*)&__glewBindBuffer;
	return err;
}

GLFWEngine::~GLFWEngine(void)
{
	//glfwTerminate();
}

void GLFWEngine::EndFrame()
{
	glfwSwapBuffers();
	if (!glfwGetWindowParam(GLFW_OPENED))
		Exit();
}

double GLFWTimerProvider::GetTimeElapsed()
{
	return glfwGetTime();
}

void GLFWTimerProvider::Sleep(double amount)
{
	glfwSleep(amount);
}

void GLFWEngine::_resize(int width, int height)
{
	GUI.SetWindowSize(width, height);
	Window.Width = width;
	Window.Height = height;
	ResizeWindow(width, height);
}




