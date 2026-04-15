#pragma once
#include <chrono>

class TimeCalculate
{
private:
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;

public:

	void SetPoint1()
	{
		t1 = std::chrono::high_resolution_clock::now();
	}

	void SetPoint2()
	{
		t2 = std::chrono::high_resolution_clock::now();
	}

	double GetDurationMs() const
	{
		return std::chrono::duration<double, std::milli>(t2 - t1).count();
	}

	double GetDurationSec() const
	{
		return std::chrono::duration<double>(t2 - t1).count();
	}
};