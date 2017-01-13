#pragma once
#include <chrono>

class Timer {

	const double NANOSECONDS_TO_MILLISECONDS = 1.0 / 1000000.0;
	const double NANOSECONDS_TO_SECONDS = NANOSECONDS_TO_MILLISECONDS / 1000.0;

public:

	void reset();
	void start();
	int pause();
	bool isrunning();
	
	double milliseconds();
	double seconds();
	double minutes();
	double hours();
	
	void updateStart();
	void stop();
	bool running();
protected:
	bool m_running;
	std::chrono::high_resolution_clock m_clock;
	std::chrono::high_resolution_clock::time_point m_startTimePoint;
	std::chrono::high_resolution_clock::time_point m_endTimePoint;
private:
};