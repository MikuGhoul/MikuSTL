#ifndef TEST_DEQUE_H__
#define TEST_DEQUE_H__

#include "../Include/MikuDeque.h"

void dequeTestCase1() {
	Miku::deque<int> _deq_1;
	Miku::deque<int> _deq_2(3, 100);
	// 这个测试是因为type为int时，每个buffer大小为512 / 4 = 128
	Miku::deque<int> _deq_3(130, 100);
	Miku::deque<int> _deq_4(_deq_3.begin(), _deq_3.end());
	Miku::deque<int> _deq_5{ 1,2,3 };

	assert(_deq_1.size() == 0);
	assert(_deq_2.size() == 3);
	assert(_deq_3.size() == 130);
	assert(_deq_4.size() == 130);
	assert(_deq_5.size() == 3);

	Miku::deque<int> _deq_6(std::move(_deq_5));
	assert(_deq_6.size() == 3);
}

void dequeTestCase2() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	Miku::deque<int>::iterator _iter_1 = _deq_1.begin();
	Miku::deque<int>::iterator _iter_2 = _deq_1.end();

	assert(*_iter_1 == 1);
	assert(*(--_iter_2) == 3);
	assert(_iter_1 != _iter_2);
	assert(_iter_1 == _deq_1.begin());

	assert(_deq_1[1] == 2);
	assert(_deq_1.at(2) == 3);

	assert(_iter_2 - _iter_1 == 2);
	assert(_iter_1 + 2 == _iter_2);
	_iter_1 += 2;
	assert(_iter_1 == _iter_2);
}

void dequeTestCase3() {
	const Miku::deque<int> _deq_1{ 1,2,3 };
	Miku::deque<int>::const_iterator _iter_1 = _deq_1.begin();
	_iter_1++;			// ok
	// *_iter_1 = -1	// error

	Miku::deque<int> _deq_2{ 1,2,3 };
	const Miku::deque<int>::iterator _iter_2 = _deq_2.begin();
	// _iter_2++;		// error
	*_iter_2 = -1;		// ok

	Miku::deque<int> _deq_3{ 1,2,3 };
	Miku::deque<int>::const_iterator _iter_3 = _deq_3.cbegin();
	_iter_3 += 3;		// ok
	// *_iter_3 = -1;	// error

	assert(_deq_1[1] == 2);
}

void dequeTestCase4() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	assert(*(_deq_1.begin()) == 1);
	assert(*(_deq_1.end() - 1) == 3);
	assert(_deq_1.front() == 1);
	assert(_deq_1.back() == 3);

	const Miku::deque<int> _deq_2{ 3,2,1 };
	assert(_deq_2.front() == 3);
	assert(_deq_2.back() == 1);

}

void dequeTestCase5() {
	Miku::deque<int> _deq_1(300, 3);
	assert(_deq_1.size() == 300);
	_deq_1.clear();
	assert(_deq_1.size() == 0);
}

void dequeTestCase6() {

}

void dequeTestCase7() {

}


#endif // !TEST_DEQUE_H__
