#ifndef TESTSTRING_H__
#define TESTSTRING_H__

#include "../Include/TinyString.h"
#include "Test/testHeader.hpp"
#include <string>
#include <cassert>

void stringTestCase1() {
	TinyString Tstr("TinyString testing 1");
	std::string _Tstr("TinyString testing 1");
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase2() {
	TinyString Tstr("TinyString testing 2");
	assert(expect_char(Tstr.front(), 'T'));
	assert(expect_char(Tstr.back(), '2'));
}

void stringTestCase3() {
	TinyString Tstr("TinyString testing 3");
	assert(expect_char(Tstr[1], 'i'));
	assert(expect_char(Tstr[3], 'y'));
}

void stringTestCase4() {
	TinyString Tstr("TinyString testing 4");
	TinyString _Tstr("");
	assert(!Tstr.empty());
	assert(_Tstr.empty());
}

void stringTestCase5() {
	TinyString Tstr("Tiny");
	TinyString _Tstr("");
	assert(Tstr.size() == 4);
	assert(Tstr.length() == 4);
	assert(_Tstr.size() == 0);
	assert(_Tstr.length() == 0);
}

#endif // !TESTSTRING_H__