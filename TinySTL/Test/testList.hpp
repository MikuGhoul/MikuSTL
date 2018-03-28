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
	// std::cout << *iA << std::endl;

	*iA = 100;
	assert(*iA == 100);
	assert(alist.size() == 1);

	Miku::list<int> blist(3, 100);
	Miku::list<int>::iterator iBb = blist.begin();
	assert(blist.size() == 3);
	assert(*iBb == 100);
	assert(*(++iBb) == 100);
	assert(*(iBb++) == 100);

	Miku::list<int>::iterator iBe = blist.end();
	assert(*(--iBe) == 100);
	assert(*(iBe--) == 100);
}


#endif // !TESTLIST_H__