#ifndef TESTALLOC_H__
#define TESTALLOC_H__

#include "../Include/TinyAllocator.h"
#include <iostream>

//class Type{
//public:
//	Type() { std::cout << "constructor" << std::endl; }
//	Type(int _t) : t(_t) { std::cout << "constructor" << t << std::endl; }
//	~Type() { std::cout << "destroctor" << std::endl; }
//private:
//	int t;
//};

void allocTestCase1() {
	 Miku::allocator<int> a;
	 auto p = a.allocate(1);
	 a.construct(p, 100);
	 // std::cout << *p << std::endl;
	 assert(*p == 100);
	 a.deallocate(p, 1);

	/*Miku::allocator<Type> a;
	auto p = a.allocate(1);

	a.construct(p, 1);
	a.destroy(p);

	a.deallocate(p, 1);*/

}


#endif // !TESTALLOC_H__

