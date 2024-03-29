#ifndef TESTENGINE_H
#define TESTENGINE_H

#include "GLFW/GLFWEngine.h"
#include "GLGUI\GUIBase.h"
#include <vector>

class Shader;
class BasicTexture;
class FrameBufferObject;
class FBOManager;
class ShaderManager;

class TestEngine :
	public GLFWEngine
{
public:
	TestEngine(WindowSettings& w);
	~TestEngine(void);
	void Update(TimeInfo& timeInfo);
	void Display();
	void Setup();
	void KeyPressed(int code);
	void KeyReleased(int code);
private:
	Shader* textDraw;
	FrameBufferObject* last;
	FrameBufferObject* current;
	FrameBufferObject* next;
	void LoadTexture();
	bool simulate;
	float spaceStep, timeStep;
	void Step();
	void CreateFBOs();
	ShaderManager& shaders;
	FBOManager& fbos;
	std::vector<BasicTexture*> baseTextures;
	int currentTexture;
	std::vector<Shader*> equationShaders;
	int currentEq;
	int iterations;
	GUIBase* guiBase;
};

#endif

