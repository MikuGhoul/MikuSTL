#include "../Include/MikuVector.h"
#include <vector>

void vector_test() {

	std::srand(std::time(nullptr));

	// Miku
	std::cout << "Miku::vector<int>" << std::endl;
	
	Miku::vector<int> miku_vec_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		miku_vec_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 100000 times: " << TestPer::spend() << std::endl;

	Miku::vector<int> miku_vec_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		miku_vec_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 1000000 times: " << TestPer::spend() << std::endl;

	Miku::vector<int> miku_vec_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		miku_vec_3.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 10000000 times: " << TestPer::spend() << std::endl;


	// std
	std::cout << "std::vector<int>" << std::endl;

	std::vector<int> std_vec_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		std_vec_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 100000 times: " << TestPer::spend() << std::endl;

	std::vector<int> std_vec_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		std_vec_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 1000000 times: " << TestPer::spend() << std::endl;

	std::vector<int> std_vec_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		std_vec_3.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 10000000 times: " << TestPer::spend() << std::endl;

}