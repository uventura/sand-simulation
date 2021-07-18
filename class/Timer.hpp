#pragma once
#include <iostream>
#include <chrono>

/*
    How to Use:
        Timer cronom; // ou cronom("Name")
        cronom.start();
             seu código
        cronom.end();

        cronom.show();
*/

struct Timer
{
	std::chrono::high_resolution_clock::time_point startTime, endTime;
	std::chrono::duration<float> duration;

	std::string TimerName;

	Timer(std::string name = "none"):TimerName(name){}

	inline void start()
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	inline void end()
	{
		endTime = std::chrono::high_resolution_clock::now();
	}

	void show()
	{
		duration = endTime - startTime;
		float timeMilliSeconds = duration.count() * 1000.0f;
		std::cout << ">> Timer(" << TimerName << ") execution: "<< timeMilliSeconds << "ms.\n";
	}
};
