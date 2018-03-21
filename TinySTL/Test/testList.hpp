#ifndef TESTLIST_H__
#define TESTLIST_H__

#include "../Include/TinyList.h"

struct Test {
	int a;
	char b;
};

void listTestCase1() {
	Miku::list<int> a;
	Miku::list<int>::iterator i;
	
	Miku::list<Test>::iterator iA;

	(*iA).a;
	iA.operator*().a;

	iA->a;
	iA.operator->()->a;
	
	iA++;
	++iA;
}


#endif // !TESTLIST_H__
