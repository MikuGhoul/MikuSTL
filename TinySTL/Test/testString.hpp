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

void stringTestCase6() {
	TinyString Tstr("Tiny testing 5");
	std::string _Tstr("testing 5");
	Tstr.erase(0, 5);
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase7() {
	TinyString Tstr("Tiny testing 6");
	std::string _Tstr("Tiy testing 6");
	auto p = Tstr.begin() + 2;
	assert(*(Tstr.erase(p)) == 'y');
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase8() {
	TinyString Tstr("Tiny testing 7");
	std::string _Tstr("Titesting 7");
	auto p = Tstr.begin() + 2;
	auto q = p + 3;
	assert(*(Tstr.erase(p, q)) == 't');
	assert(expect_string(Tstr, _Tstr));	
}

void stringTestCase9() {
	TinyString Tstr("Tiny testing 8");
	Tstr.clear();
	assert(Tstr.empty());
}

void stringTestCase10() {
	TinyString Tstr("Tiny testing 9");
	std::string _Tstr("Tiny wwwtesting 9");
	Tstr.insert(5, 3, 'w');
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase11() {
	TinyString Tstr("Tiny testing 10");
	std::string _Tstr("whatTiny testing 10");
	Tstr.insert(0, "what");
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase12() {
	TinyString Tstr("Tiny testing 11");
	std::string _Tstr("whTiny testing 11");
	Tstr.insert(0, "what the hell", 2);
	assert(expect_string(Tstr, _Tstr));
}

void stringTestCase13() {
	TinyString Tstr("Tiny testing 12");
	TinyString _Tstr("what");
	std::string _Tstr_2("whatTiny testing 12");
	Tstr.insert(0, _Tstr);
	assert(expect_string(Tstr, _Tstr_2));
}

#endif // !TESTSTRING_H__