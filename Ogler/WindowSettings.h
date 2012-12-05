#ifndef WINDOWSETTINGS_H
#define WINDOWSETTINGS_H

#include <string>

struct WindowSettings
{
	WindowSettings()
	{
		RedBits = 8;
		GreenBits = 8;
		BlueBits = 8;
		AlphaBits = 8;
		DepthBits = 24;
		StencilBits = 0;
		Height = 600;
		Width = 800;
		OpenGLVersionMajor = 3;
		OpenGLVersionMinor = 3;
		Title = "";
		Fullscreen = false;
		CoreProfile = false;
	}
	int RedBits;
	int GreenBits;
	int BlueBits;
	int AlphaBits;
	int DepthBits;
	int StencilBits;
	int Height;
	int Width;
	int OpenGLVersionMinor;
	int OpenGLVersionMajor;
	std::string Title;
	bool Fullscreen;
	bool CoreProfile;
};

#endif