#include "../Include/MikuDeque.h"
#include <deque>

void deque_test() {

	// Miku
	std::cout << "Miku::deque<int>" << std::endl;

	Miku::deque<int> miku_deq_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		miku_deq_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_bak -> 100000 times: " << TestPer::spend() << std::endl;

	Miku::deque<int> miku_deq_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		miku_deq_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_bak -> 1000000 times: " << TestPer::spend() << std::endl;

	Miku::deque<int> miku_deq_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		miku_deq_3.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_bak -> 10000000 times: " << TestPer::spend() << std::endl;

	Miku::deque<int> miku_deq_4;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		miku_deq_4.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 100000 times: " << TestPer::spend() << std::endl;

	Miku::deque<int> miku_deq_5;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		miku_deq_5.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 1000000 times: " << TestPer::spend() << std::endl;

	Miku::deque<int> miku_deq_6;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		miku_deq_6.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 10000000 times: " << TestPer::spend() << std::endl;


	//std
	std::cout << "std::deque<int>" << std::endl;

	std::deque<int> std_deq_1;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		std_deq_1.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_back -> 100000 times: " << TestPer::spend() << std::endl;

	std::deque<int> std_deq_2;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		std_deq_2.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_back -> 1000000 times: " << TestPer::spend() << std::endl;

	std::deque<int> std_deq_3;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		std_deq_3.push_back(rand());
	TestPer::finish();
	std::cout << "\tpush_back -> 10000000 times: " << TestPer::spend() << std::endl;


	std::deque<int> std_deq_4;
	TestPer::start();
	for (int i = 0; i != 100000; ++i)
		std_deq_4.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 100000 times: " << TestPer::spend() << std::endl;

	std::deque<int> std_deq_5;
	TestPer::start();
	for (int i = 0; i != 1000000; ++i)
		std_deq_5.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 1000000 times: " << TestPer::spend() << std::endl;

	std::deque<int> std_deq_6;
	TestPer::start();
	for (int i = 0; i != 10000000; ++i)
		std_deq_6.push_front(rand());
	TestPer::finish();
	std::cout << "\tpush_front -> 10000000 times: " << TestPer::spend() << std::endl;

}