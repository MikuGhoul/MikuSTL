#ifndef TESTLIST_H__
#define TESTLIST_H__

#include <cstddef>
#include "../Include/TinyList.h"

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
}

void listTestCase3() {
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

void listTestCase4() {
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

void listTestCase5() {

}

#endif // !TESTLIST_H__