#include <GL\glew.h>
#include <GL\glfw.h>
#include "Colour.h"
#include "ShaderManager.h"
#include "WindowSettings.h"
#include "TestEngine.h"

int windowWidth = 1280;
int windowHeight = 720;

BasicEngine* engine;

class blah
{
public:
	const int& X;
	const int& Y;
	blah()
		: X(xPos),
		Y(yPos)
	{
		xPos = 2;
		yPos = 5;
	}
private:
	int xPos;
	int yPos;
	static int myInt;
	std::vector<void*> textures;
	std::vector<GLuint> renderBuffers;
};

int blah::myInt = 0;


class BlahContainer
{
public:
	void AddBlah(blah* theBlah)
	{
		blahMap.insert(std::pair<std::string, blah*>("blah", theBlah));		
	}
private:
	std::map<std::string, blah*> blahMap;
};

int main(int argc, char** argv)
{	

	BlahContainer bc;

	bc.AddBlah(new blah());
	WindowSettings w;
	w.OpenGLVersionMajor = 4;
	w.OpenGLVersionMinor = 2;
	w.Width = 1280;
	w.Height = 720;
	engine = new TestEngine(w);
	engine->Run();

	glfwTerminate();

	return 0;
}