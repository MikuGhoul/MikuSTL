#include "../Include/MikuVector.h"
#include <ctime>
#include <vector>
#include <random>

void vector_test() {

	std::srand(std::time(nullptr));

	// Miku
	Miku::vector<int> miku_vec_1;
	std::clock_t miku_start_time_1 = std::clock();
	for (int i = 0; i != 100000; ++i)
		miku_vec_1.push_back(rand());
	std::clock_t miku_end_time_1 = std::clock();
	std::cout << "push_back: " << miku_end_time_1 - miku_start_time_1 << std::endl;

	Miku::vector<int> miku_vec_2;
	std::clock_t miku_start_time_2 = std::clock();
	for (int i = 0; i != 1000000; ++i)
		miku_vec_2.push_back(rand());
	std::clock_t miku_end_time_2 = std::clock();
	std::cout << "push_back: " << miku_end_time_2 - miku_start_time_2 << std::endl;

	Miku::vector<int> miku_vec_3;
	std::clock_t miku_start_time_3 = std::clock();
	for (int i = 0; i != 10000000; ++i)
		miku_vec_3.push_back(rand());
	std::clock_t miku_end_time_3 = std::clock();
	std::cout << "push_back: " << miku_end_time_3 - miku_start_time_3 << std::endl;


	// std
	std::vector<int> std_vec_1;
	std::clock_t std_start_time_1 = std::clock();
	for (int i = 0; i != 100000; ++i)
		std_vec_1.push_back(rand());
	std::clock_t std_end_time_1 = std::clock();
	std::cout << "push_back: " << std_end_time_1 - std_start_time_1 << std::endl;

	std::vector<int> std_vec_2;
	std::clock_t std_start_time_2 = std::clock();
	for (int i = 0; i != 1000000; ++i)
		std_vec_2.push_back(rand());
	std::clock_t std_end_time_2 = std::clock();
	std::cout << "push_back: " << std_end_time_2 - std_start_time_2 << std::endl;

	std::vector<int> std_vec_3;
	std::clock_t std_start_time_3 = std::clock();
	for (int i = 0; i != 10000000; ++i)
		std_vec_3.push_back(rand());
	std::clock_t std_end_time_3 = std::clock();
	std::cout << "push_back: " << std_end_time_3 - std_start_time_3 << std::endl;

}