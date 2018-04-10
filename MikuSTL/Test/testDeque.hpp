#ifndef TEST_DEQUE_H__
#define TEST_DEQUE_H__

#include "../Include/MikuDeque.h"

void dequeTestCase1() {
	Miku::deque<int> _deq_1;
	Miku::deque<int> _deq_2(3, 100);
	// 这个测试是因为type为int时，每个buffer大小为512 / 4 = 128
	Miku::deque<int> _deq_3(130, 100);
	Miku::deque<int> _deq_4(_deq_3.begin(), _deq_3.end());

	assert(_deq_1.size() == 0);
	assert(_deq_2.size() == 3);
	assert(_deq_3.size() == 130);
	assert(_deq_4.size() == 130);
}

void dequeTestCase2() {

}

void dequeTestCase3() {

}

void dequeTestCase4() {

}

void dequeTestCase5() {

}

void dequeTestCase6() {

}

void dequeTestCase7() {

}


#endif // !TEST_DEQUE_H__
