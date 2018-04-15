#ifndef TEST_PERFORMANCE_H__
#define TEST_PERFORMANCE_H__

#include <ctime>
#include <random>
#include <cstdlib>

namespace TestPer {
	std::clock_t _Start_time;
	std::clock_t _Finish_time;
	void start() {
		_Start_time = std::clock();
	}

	void finish() {
		_Finish_time = std::clock();
	}

	std::clock_t spend() {
		return _Finish_time - _Start_time;
	}
}


#endif // !TEST_PERFORMANCE_H__
