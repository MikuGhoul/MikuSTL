#ifndef TESTSTRING_H__
#define TESTSTRING_H__

#include "../Include/TinyString.h"
#include <string>

void stringTestCase1() {
	TinyString Tstr("TinyString testing");
	std::cout << Tstr.front() << std::endl;
}

#endif // !TESTSTRING_H__