#ifndef TESTSTRING_H__
#define TESTSTRING_H__

#include "../Include/TinyString.h"
#include <string>

void stringTestCase1() {
	TinyString Tstr("TinyString testing 1");
	std::cout << Tstr.front() << std::endl
		<< Tstr.back() << std::endl
		<< Tstr << std::endl;
}

void stringTestCase2() {
	
	TinyString Tstr("TinyString testing 2");
	TinyString _Tstr("TinyString testing 3");
	Tstr = _Tstr;
	std::cout << Tstr << std::endl
		<< _Tstr << std::endl;
}

void stringTestCase3() {
	TinyString Tstr("TinyString testing 4");
	TinyString _Tstr("TinyString testing 5");
	Tstr[2] = 'a';
	std::cout << Tstr << std::endl
		<< _Tstr[2] << std::endl;
}
void stringTestCase4() {
	TinyString Tstr("TinyString testing 6");
	EXPECT_CHAR(Tstr.front(), 'T');
	EXPECT_CHAR(Tstr.back(), '5');
	EXPECT_CHAR(Tstr[2], 'q');
}
#endif // !TESTSTRING_H__