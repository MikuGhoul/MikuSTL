#ifndef TESTLIST_H__
#define TESTLIST_H__

#include <cstddef>
#include "../Include/TinyList.h"

struct Test {
	int a;
	char b;
};

void listTestCase1() {
	Miku::list<int> alist;
	Miku::list<int>::iterator iA = alist.begin();
	alist.insert(iA, 2);
	assert(*(alist.begin()) == 2);

	*iA = 100;
	assert(*iA == 100);

}

void listTestCase2() {
	Miku::list<int> alist(3, 100);
	for (auto i : alist)
		assert(i == 100);
}

void listTestCase3() {
	Miku::list<int> alist(3, 100);
	assert(alist.size() == 3);
	alist.push_back(17);
	assert(alist.size() == 4);
	assert(*(--alist.end()) == 17);
}

void listTestCase4() {
	Miku::list<int> alist(3, 100);
	Miku::list<int> blist(alist.begin(), alist.end());
	for (auto i : blist)
		assert(i == 100);
	assert(blist.size() == 3);

	Miku::list<int> clist(alist);
	for (auto i : clist)
		assert(i == 100);

	Miku::list<int> dlist{ 1, 2, 3 };
	assert(*(dlist.begin()) == 1);
	assert(*(++dlist.begin()) == 2);
}

void listTestCase5() {

}

#endif // !TESTLIST_H__