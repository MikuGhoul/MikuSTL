#ifndef TESTLIST_H__
#define TESTLIST_H__

#include <cstddef>
#include "../Include/MikuList.h"

struct Stru {
	int a;
	char b;
};

void listTestCase1() {
	Miku::list<int> _list_1;
	Miku::list<int> _list_2(2, 100);
	Miku::list<int> _list_3(_list_2.begin(), _list_2.end());
	Miku::list<int> _list_4(_list_3);
	Miku::list<int> _list_5{ 1, 2, 3 };

	assert(_list_1.size() == 0);
	assert(_list_2.size() == 2);
	assert(_list_3.size() == 2);
	assert(_list_4.size() == 2);
	assert(_list_5.size() == 3);

	Miku::list<int> _list_6(std::move(_list_5));
	assert(_list_6.size() == 3);
}

void listTestCase2() {
	Miku::list<int> _list_1{ 1, 2, 3, 4 };
	Miku::list<int>::iterator _iter_1 = _list_1.begin();
	Miku::list<int>::iterator _iter_2 = _list_1.end();
	auto _iter_3 = ++_list_1.begin();

	assert(*_iter_1 == 1);
	assert(*(++_iter_1) == 2);
	assert(*(--_iter_2) == 4);
	assert(_iter_1 == _iter_3);
	assert(_iter_2 != _iter_3);

	Miku::list<int> _list_2(4, 100);
	for (auto i : _list_2)
		assert(i == 100);
	for (auto i = _list_2.begin(); i != _list_2.end(); ++i)
		assert(*i == 100);	
}

void listTestCase3() {
	// const_iterator && const iterator²âÊÔ
	const Miku::list<int> _list_3{ 1, 2, 3 };
	Miku::list<int>::const_iterator _iter_4 = _list_3.begin();
	assert(*(_list_3.begin()) == 1);
	_iter_4++;			// OK
	// *_iter_4 = 1;	// error

	Miku::list<int> _list_4{ 2, 3 };
	const Miku::list<int>::iterator _iter_5 = _list_4.begin();
	// _iter_5++;		// error
	*_iter_5 = 1;		// ok

	Miku::list<int> _list_5{ 1, 2 };
	Miku::list<int>::const_iterator _iter_6 = _list_5.cbegin();
	_iter_6++;			// ok
	// *_iter_6 = 1;	// error
}

void listTestCase4() {
	Miku::list<int> _list_1{ 1, 2 };
	assert(_list_1.size() == 2);
	assert(*_list_1.begin() == 1);
	assert(*(--_list_1.end()) == 2);
	_list_1.push_back(3);
	assert(_list_1.size() == 3);
	assert(*(--_list_1.end()) == 3);
	_list_1.push_front(-1);
	assert(_list_1.size() == 4);
	assert(*_list_1.begin() == -1);

	Miku::list<Stru> _list_2;
	assert(_list_2.size() == 0);
	Stru s{100, 'c'};
	_list_2.push_back(s);
	Miku::list<Stru>::iterator _iter_1 = _list_2.begin();
	assert(_list_2.size() == 1);
	assert(_iter_1->a == 100);
	assert(_iter_1->b == 'c');

	int r = 42;
	Miku::list<int> _list_3{ 1, 2 };
	_list_3.push_back(std::move(r));
	assert(_list_3.size() == 3);
}

void listTestCase5() {
	Miku::list<int> _list_1{ 1, 2 };
	assert(_list_1.size() == 2);
	_list_1.insert(_list_1.begin(), -1);
	assert(_list_1.size() == 3);
	assert(*_list_1.begin() == -1);
	assert(*(--_list_1.end()) == 2);
	_list_1.insert(_list_1.end(), 2, -3);
	assert(_list_1.size() == 5);
	assert(*(--_list_1.end()) == -3);

	Miku::list<int> _list_2{ 7, 8, 9 };
	_list_2.insert(_list_2.end(), _list_1.begin(), _list_1.end());
	assert(_list_2.size() == 8);
	assert(*(--_list_2.end()) == -3);
}

void listTestCase6() {
	Miku::list<int> _list_1;
	assert(_list_1.empty());
	_list_1.push_back(1);
	assert(!_list_1.empty());
	
	Miku::list<int> _list_2{ 1,2,3 };
	assert(_list_2.size() == 3);
	_list_2.clear();
	assert(_list_2.size() == 0);	
}

void listTestCase7() {
	Miku::list<int> _list_3{ 1,2,3 };
	auto _iter_1 = _list_3.begin();
	auto _iter_2 = _list_3.erase(_iter_1);
	assert(_list_3.size() == 2);
	assert(*(_list_3.begin()) == 2);
	assert(_iter_2 == _list_3.begin());

	Miku::list<int> _list_4{ 1,2,3 };
	auto _iter_3 = _list_4.begin();
	auto _iter_4 = ++_list_4.begin();
	auto _iter_5 = _list_4.erase(_iter_3, _iter_4);
	assert(_list_4.size() == 2);
	assert(*_iter_5 == 2);

	Miku::list<int> _list_5{ 1,2,3 };
	auto _iter_6 = _list_5.cbegin();
	auto _iter_7 = ++_list_5.cbegin();
	auto _iter_8 = _list_5.erase(_iter_6, _iter_7);
	assert(_list_5.size() == 2);
	assert(*_iter_8 == 2);

	Miku::list<int> _list_6{ 1,2,3 };
	auto _iter_9 = _list_6.erase(_list_6.cbegin());
	assert(_list_6.size() == 2);
	assert(*_iter_9 == 2);
}

void listTestCase8() {
	Miku::list<int> _list_1{ 1,2,3 };
	_list_1.pop_back();
	assert(_list_1.size() == 2);
	assert(*(--_list_1.end()) == 2);

	_list_1.pop_front();
	assert(_list_1.size() == 1);
	assert(*_list_1.begin() == 2);

	Miku::list<int> _list_2{ 1,1,1 };
	_list_2.resize(5, 1);
	assert(_list_2.size() == 5);
	for (auto i : _list_2)
		assert(i == 1);
	_list_2.resize(1);
	assert(_list_2.size() == 1);
	for (auto i : _list_2)
		assert(i == 1);
}

void listTestCase9() {
	Miku::list<int> _list_1{ 1 };
	Miku::list<int> _list_2{ 7,8,9 };
	_list_1.swap(_list_2);
	assert(_list_1.size() == 3);
	assert(_list_2.size() == 1);
	_list_2.swap(_list_1);
	assert(_list_1.size() == 1);
	assert(_list_2.size() == 3);
}

void listTestCase10() {
	Miku::list<int> _list_1{ 4,2,1,3 };
	Miku::list<int> _list_2{ 1,2,3,4 };
	Miku::list<int> _list_3{ 1,2,3 };
	_list_3.push_back(4);
	assert(_list_1 != _list_2);
	assert(_list_2 == _list_3);

	_list_1.sort();
	assert(_list_1 == _list_2);

	Miku::list<int> _list_4{ 1, 3, 6 };
	Miku::list<int> _list_5{ 2,4,7 };
	_list_4.merge(_list_5);
	Miku::list<int> _list_6{ 1,2,3,4,6,7 };
	assert(_list_4 == _list_6);
	assert(_list_5.size() == 0);
}

void listTestCase11() {
	Miku::list<int> _list_1{ 1,2,3,4 };
	Miku::list<int> _list_2{ 100, 200 };
	auto _iter_1 = _list_1.begin();
	auto _iter_2 = ++(++_list_1.begin());
	assert(*_iter_1 == 1);
	assert(*_iter_2 == 3);
	auto _iter3 = _list_2.begin();
	_list_2.splice(_iter3, _list_1, _iter_1, _iter_2);
	Miku::list<int> _list_3{ 1, 2, 100, 200 };
	assert(_list_2 == _list_3);
	Miku::list<int> _list_4{ 3, 4 };
	assert(_list_1 == _list_4);

	Miku::list<int> _list_5{ 1, 2, 3 };
	Miku::list<int> _list_6{ 100, 200 };
	_list_5.splice(_list_5.begin(), _list_6);
	Miku::list<int> _list_7{ 100,200, 1,2,3 };
	assert(_list_5 == _list_7);
	assert(_list_6.size() == 0);
}

void listTestCase12() {
	Miku::list<int> _list_1{ 1,2,3,1,4,5 };
	_list_1.remove(1);
	Miku::list<int> _list_2{ 2,3,4,5 };
	assert(_list_1 == _list_2);

	_list_1.remove_if([](int n) {return n > 3; });
	Miku::list<int> _list_3{ 2,3 };
	assert(_list_1 == _list_3);
}

void listTestCase13() {
	Miku::list<int> _list_1{ 1,2,3 };
	assert(_list_1.front() == 1);
	assert(_list_1.back() == 3);

	_list_1.reverse();
	Miku::list<int> _list_2{ 3,2,1 };
	assert(_list_1 == _list_2);
}

void listTestCase14() {
	Miku::list<int> _list_1{ 1,2,2,3,3,2,1,1,2 };
	_list_1.unique();
	Miku::list<int> _list_2{ 1,2,3,2,1,2 };
	assert(_list_1 == _list_2);
}

#endif // !TESTLIST_H__