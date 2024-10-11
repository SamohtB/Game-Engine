#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
	static double getFixedDeltaTime();
	static void setFrameTime(int rate);

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* sharedInstance;
	
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;
	double targetFrameRate = 0.0;
	double fixedDeltaTime = 0.0;
	double accumulator = 0.0f;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;

};

