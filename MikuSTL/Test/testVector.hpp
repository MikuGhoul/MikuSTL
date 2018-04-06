#ifndef TEST_VECTOR_H__
#define TEST_VECTOR_H__

#include "../Include/MikuVector.h"

void vectorTestCase1() {
	Miku::vector<int> _vec_1;
	Miku::vector<int> _vec_2(3, 111);
	Miku::vector<int> _vec_3(_vec_2.begin(), _vec_2.end());
	Miku::vector<int> _vec_4(_vec_3);
	Miku::vector<int> _vec_5(_vec_4);
	Miku::vector<int> _vec_6(std::move(_vec_5));
	Miku::vector<int> _vec_7{ 1,2,3,4 };

	assert(_vec_1.size() == 0);
	assert(_vec_2.size() == 3);	
	assert(_vec_3.size() == 3);
	assert(_vec_4.size() == 3);
	assert(_vec_6.size() == 3);
	assert(_vec_7.size() == 4);
}

void vectorTestCase2() {
	Miku::vector<int> _vec_1{ 1,2,3,4 };
	Miku::vector<int>::iterator _iter_1 = _vec_1.begin();
	Miku::vector<int>::iterator _iter_2 = _vec_1.end();
	auto _iter_3 = _vec_1.begin() + 3;

	assert(*_iter_1 == 1);
	assert(*(--_iter_2) == 4);
	assert(_iter_1 != _iter_2);
	assert(_iter_2 == _iter_3);
}
void vectorTestCase3() {
	const Miku::vector<int> _vec_1{ 1,2,3 };
	Miku::vector<int>::const_iterator _iter_1 = _vec_1.begin();
	_iter_1++;			// ok
	// *_iter_1 = -1;	// error

	Miku::vector<int> _vec_2{ 1,2,3 };
	const Miku::vector<int>::iterator _iter_2 = _vec_2.begin();
	// _iter_2++;		// error
	*_iter_2 = -1;		// ok

	Miku::vector<int> _vec_3{ 1,2,3 };
	Miku::vector<int>::const_iterator _iter_3 = _vec_3.cbegin();
	_iter_3 += 2;			// ok
	// *_iter_3 = -1;	// error
}

void vectorTestCase4() {
	Miku::vector<int> _vec_1{ 1,2,3 };
	assert(_vec_1[2] == 3);
	assert(_vec_1.at(1) == 2);
	assert(_vec_1.front() == 1);
	assert(_vec_1.back() == 3);
	_vec_1.front() = -1;
	assert(*_vec_1.begin() == -1);
	assert(_vec_1.begin() == _vec_1.data());
}

void vectorTestCase5() {
	Miku::vector<int> _vec_1{ 1,2,3 };
	assert(_vec_1.size() == 3);
	assert(_vec_1.capacity() == 3);
	_vec_1.insert(_vec_1.begin(), 1, 6);
	assert(_vec_1.size() == 4);
	assert(_vec_1.capacity() == 6);
	_vec_1.insert(_vec_1.begin(), 100, 2);
	assert(_vec_1.size() == 104);
	assert(_vec_1.capacity() == 104);
	_vec_1.insert(_vec_1.begin(), 3);
	assert(_vec_1.size() == 105);
	assert(_vec_1.capacity() > 105);

	Miku::vector<int> _vec_2{ 1,2,3 };
	auto _iter_1 = _vec_2.insert(_vec_2.begin(), 100);
	assert(*_iter_1 == 100);

}

void vectorTestCase6() {
	Miku::vector<int> _vec_1{ 1 };
	_vec_1.insert(_vec_1.begin(), 2);
	_vec_1.insert(_vec_1.begin(), 2, 3);
	Miku::vector<int> _vec_2{ 6,6,6 };
	_vec_1.insert(_vec_1.begin(), _vec_2.begin(), _vec_2.end());
	_vec_1.insert(_vec_1.begin(), { 7,8,9 });
	assert(_vec_1.size() == 10);

	_vec_1.push_back(100);
	assert(_vec_1.size() == 11);
}

void vectorTestCase7() {
	Miku::vector<int> _vec_1{ 1,2,3 };
	Miku::vector<int> _vec_2;
	assert(_vec_1.size() == 3);
	assert(_vec_2.size() == 0);
	_vec_2 = _vec_1;
	assert(_vec_1.size() == 3);
	assert(_vec_2.size() == 3);
	Miku::vector<int> _vec_3;
	_vec_3 = std::move(_vec_1);
	assert(_vec_1.size() == 0);
	assert(_vec_3.size() == 3);
}

void vectorTestCase8() {
	Miku::vector<int> _vec_1{ 1,2,3 };
	assert(_vec_1.size() == 3);
	assert(_vec_1.capacity() == 3);
	_vec_1.reserve(100);
	assert(_vec_1.size() == 3);
	assert(_vec_1.capacity() == 100);
}

void vectorTestCase9() {
	Miku::vector<int> _vec_1;
	assert(_vec_1.size() == 0);
	assert(_vec_1.capacity() == 0);

	_vec_1.resize(100);
	assert(_vec_1.size() == 100);
	assert(_vec_1.capacity() == 100);

	_vec_1.clear();
	assert(_vec_1.size() == 0);
	assert(_vec_1.capacity() == 100);
	
	_vec_1.shrink_to_fit();
	assert(_vec_1.size() == 0);
	assert(_vec_1.capacity() == 0);
}

void vectorTestCase10() {
	Miku::vector<int> _vec_1{ 1,2,3,4,5 };
	auto _iter_1 = _vec_1.erase(_vec_1.begin());
	assert(*(_vec_1.begin()) == 2);
	assert(*_iter_1 == 2);
	assert(_vec_1.size() == 4);

	auto _iter_2 = _vec_1.erase(_vec_1.begin(), _vec_1.begin() + 2);
	assert(_vec_1.size() == 2);
	assert(*_iter_2 == 4);
}

void vectorTestCase11() {
	Miku::vector<int> _vec_1{ 1,2 };
	Miku::vector<int> _vec_2{ 1,2,3 };
	assert(_vec_1 != _vec_2);
	_vec_1.push_back(3);
	assert(_vec_1 == _vec_2);
}

void vectorTestCase12() {
	Miku::vector<int> _vec_1{ 1 };
	Miku::vector<int> _vec_2{ 7,8,9 };
	assert(_vec_1.size() == 1);
	assert(_vec_2.size() == 3);
	_vec_1.swap(_vec_2);
	assert(_vec_1.size() == 3);
	assert(_vec_2.size() == 1);
}

#endif // !TEST_VECTOR_H__
