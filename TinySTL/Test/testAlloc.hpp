#ifndef TESTALLOC_H__
#define TESTALLOC_H__

// #include <iostream>
#include "../Include/MikuAllocator.h"
#include "../Include/MikuAllocTraits.h"


void allocTestCase1() {
	 Miku::allocator<int> a;
	 auto p = a.allocate(1);
	 a.construct(p, 100);
	 // std::cout << *p << std::endl;
	 assert(*p == 100);
	 a.deallocate(p, 1);

	 Miku::allocator<int> b = a;
	 assert(a == b);

	/*Miku::allocator<Type> a;
	auto p = a.allocate(1);

	a.construct(p, 1);
	a.destroy(p);

	a.deallocate(p, 1);*/

}

void allocTestCase2() {
	Miku::allocator<int> a;
	auto p = Miku::allocator_traits<Miku::allocator<int>>::allocate(a, 2);

	Miku::allocator_traits<Miku::allocator<int>>::construct(a, p, 100);
	assert(*(p + 0) == 100);
	// does not support C++ 11, just like this...
	// Miku::allocator_traits<Miku::allocator<int>>::construct(a, p, 100, 200, 300);
	// assert(*(p + 1) == 200);
	
}

void allocTestCase3() {
	auto p = Miku::allocator<int>::allocate(1);
	Miku::allocator<int>::construct(p, 100);
	assert(*p == 100);
	Miku::allocator<int>::deallocate(p, 1);
}

#endif // !TESTALLOC_H__

