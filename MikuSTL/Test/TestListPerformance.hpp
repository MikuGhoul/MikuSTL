#include "../Include/MikuList.h"
#include <ctime>
#include <cstdlib>
#include <list>
#include <random>

void list_test() {

	std::srand(std::time(nullptr));
	
	// Miku
	Miku::list<int> miku_list_1;
	std::clock_t miku_start_time_1 = std::clock();
	for (int i = 0; i != 100000; ++i) {
		miku_list_1.push_back(rand());
	}
	std::clock_t miku_end_time_1 = std::clock();
	std::cout << "puck_back: " << miku_end_time_1 - miku_start_time_1 << std::endl;

	Miku::list<int> miku_list_2;
	std::clock_t miku_start_time_2 = std::clock();
	for (int i = 0; i != 1000000; ++i) {
		miku_list_2.push_back(rand());
	}
	std::clock_t miku_end_time_2 = std::clock();
	std::cout << "puck_back: " << miku_end_time_2 - miku_start_time_2 << std::endl;

	Miku::list<int> miku_list_3;
	std::clock_t miku_start_time_3 = std::clock();
	for (int i = 0; i != 10000000; ++i) {
		miku_list_3.push_back(rand());
	}
	std::clock_t miku_end_time_3 = std::clock();
	std::cout << "puck_back: " << miku_end_time_3 - miku_start_time_3 << std::endl;


	// std
	std::list<int> std_list_1;
	std::clock_t std_start_time_1 = std::clock();
	for (int i = 0; i != 100000; ++i) {
		std_list_1.push_back(rand());
	}
	std::clock_t std_end_time_1 = std::clock();
	std::cout << "puck_back: " << std_end_time_1 - std_start_time_1 << std::endl;

	std::list<int> std_list_2;
	std::clock_t std_start_time_2 = std::clock();
	for (int i = 0; i != 1000000; ++i) {
		std_list_2.push_back(rand());
	}
	std::clock_t std_end_time_2 = std::clock();
	std::cout << "puck_back: " << std_end_time_2 - std_start_time_2 << std::endl;

	std::list<int> std_list_3;
	std::clock_t std_start_time_3 = std::clock();
	for (int i = 0; i != 10000000; ++i) {
		std_list_3.push_back(rand());
	}
	std::clock_t std_end_time_3 = std::clock();
	std::cout << "puck_back: " << std_end_time_3 - std_start_time_3 << std::endl;


}
