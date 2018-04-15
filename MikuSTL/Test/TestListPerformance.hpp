#include "../Include/MikuList.h"
#include <list>

void list_test() {

	std::srand(std::time(nullptr));
	
	// Miku
	std::cout << "Miku::list<int>" << std::endl;

	Miku::list<int> miku_list_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		miku_list_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 100000 times: " << TestPer::spend() << std::endl;

	Miku::list<int> miku_list_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		miku_list_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 1000000 times: " << TestPer::spend() << std::endl;

	Miku::list<int> miku_list_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		miku_list_3.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 10000000 times: " << TestPer::spend() << std::endl;


	// std
	std::cout << "std::list<int>" << std::endl;

	std::list<int> std_list_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		std_list_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 100000 times: " << TestPer::spend() << std::endl;

	std::list<int> std_list_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		std_list_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpuck_back -> 1000000 times: " << TestPer::spend() << std::endl;

	std::list<int> std_list_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i) {
		std_list_3.push_back(rand());
	}
	TestPer::finish();
	std::cout << "\tpuck_back -> 10000000 times: " << TestPer::spend() << std::endl;


}
