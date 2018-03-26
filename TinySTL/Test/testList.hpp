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
	// std::cout << *iA << std::endl;
	// std::cout << "size:\t" << alist.size() << std::endl;
	assert(alist.size() == 1);

	// unsigned int a = 100;
	size_t a = 100;
	int b = 20;
	// Miku::list<int> blist(-1, 100);
	Miku::list<int> clist(1, 100);

	/*Miku::list<int>::iterator i;
	
	Miku::list<Test>::iterator iA;

	(*iA).a;
	iA.operator*().a;

	iA->a;
	iA.operator->()->a;
	
	iA++;
	++iA;*/
}


#endif // !TESTLIST_H__