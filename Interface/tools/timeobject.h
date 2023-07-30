#pragma once

#include <chrono>
#include <time.h>

class TExecutionTimeObject {
public:

	void Begin() {
		Time[0] = std::chrono::high_resolution_clock::now();
	}

	double GetInterval() {
		std::chrono::duration<double, std::milli> FunctionInterval = Time[1] - Time[0];
		return FunctionInterval.count();
	}

	void End() {
		Time[1] = std::chrono::high_resolution_clock::now();
	}

private:
	std::chrono::steady_clock::time_point Time[2];
};
