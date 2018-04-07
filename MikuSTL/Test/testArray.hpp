#ifndef TEST_ARRAY_H__
#define TEST_ARRAY_H__

#include "../Include/MikuArray.h"

void arrayTestCase1() {
	Miku::array<int, 3> _arr_1;
	Miku::array<int, 3> _arr_2 = { 100,2,3 };
	Miku::array<int, 3> _arr_3{ -1, -1, -1 };

	assert(_arr_1.size() == 3);
	assert(*_arr_2.begin() == 100);
	assert(_arr_2.size() == 3);
	assert(*_arr_3.begin() == -1);
	assert(_arr_2.size() == 3);
}

void arrayTestCase2() {
	Miku::array<int, 3> _arr_1{ 1,2,3 };
	Miku::array<int, 0> _arr_2;
	assert(!_arr_1.empty());
	assert(_arr_2.empty());

	Miku::array<int, 3>::iterator _iter_1 = _arr_1.begin();
	Miku::array<int, 3>::iterator _iter_2 = _arr_1.end();
	assert(_iter_1 == _arr_1.begin());
	assert(_iter_2 != _iter_1);
}

void arrayTestCase3() {
	const Miku::array<int, 3> _arr_1{ 1,2,3 };
	Miku::array<int, 3>::const_iterator _iter_1 = _arr_1.begin();
	_iter_1++;			// ok
	// *_iter_1 = 1;	// error

	Miku::array<int, 3> _arr_2{ 1,2,3 };
	const Miku::array<int, 3>::iterator _iter_2 = _arr_2.begin();
	// _iter_2++;		// ok
	*_iter_2 = -1;		// error
	
	Miku::array<int, 3> _arr_3{ 1,2,3 };
	Miku::array<int, 3>::const_iterator _iter_3 = _arr_3.begin();
	_iter_3 += 2;		// ok
	// *_iter_3 = 1;	// error
}

void arrayTestCase4() {
	Miku::array<int, 3> _arr_1{ 1,2,3 };

	assert(_arr_1.front() == 1);
	_arr_1.front() = -1;
	assert(_arr_1.front() == -1);

	assert(_arr_1.back() == 3);
	_arr_1.back() = 0;
	assert(_arr_1.back() == 0);

	assert(_arr_1.data() == _arr_1.begin());

}

void arrayTestCase5() {
	Miku::array<int, 3> _arr_1{ 1,1,1 };
	for (auto i : _arr_1)
		assert(i == 1);
	_arr_1.fill(2);
	for (auto i : _arr_1)
		assert(i == 2);

	Miku::array<int, 3> _arr_2{ 1,1,1 };
	Miku::array<int, 3> _arr_3{ 2,2,2 };
	auto _iter_1 = _arr_2.begin();
	auto _iter_2 = _arr_3.begin();
	assert(*_iter_1 == 1);
	assert(*_iter_2 == 2);
	
	_arr_2.swap(_arr_3);
	assert(*_iter_1 == 2);
	assert(*_iter_2 == 1);
	
	assert(_arr_1 == _arr_2);
	assert(_arr_1 != _arr_3);
}

#endif // !TEST_ARRAY_H__
