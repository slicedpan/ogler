#ifndef BASICENGINE_H
#define BASICENGINE_H

#include "MiscUtils.h"
#include "GLGUI\GUIBase.h"

class ITimerProvider
{
public:
	virtual double GetTimeElapsed() = 0;
	virtual void Sleep(double time) = 0;
};

struct TimeInfo
{
	float fTimeElapsed;
	float fTimeSinceLastFrame;
	double dTimeElapsed;
	double dTimeSinceLastFrame;
};

class BasicEngine
{
public:
	BasicEngine(ITimerProvider* timerProvider);
	virtual ~BasicEngine(void);
	virtual void Setup() {}
	virtual void Update(TimeInfo& timeInfo) {}
	virtual void Display() {}
	virtual void EndFrame() {}
	void Run();
	bool LimitFPS;
	int MaxFPS;
	void Exit();
	const int& CurrentFPS;
protected:
	GUIBase GUI;
private:
	bool running;
	int currentFPS;
	int frameCounter;
	double frameBegin;
	double timeElapsed;
	double timeCount;
	double lastTime;
	TimeInfo t;
	ITimerProvider* timerProvider;
};

#endif
