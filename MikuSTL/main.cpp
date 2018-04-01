#include <iostream>
#include <cassert>



#include "Test/testAlloc.hpp"
#include "Test/testList.hpp"

//#include "Test/testString.hpp"
//#include "Test/testVector.hpp"
//#include "Test/testHeader.hpp"

//void testString() {
//	stringTestCase1();
//	stringTestCase2();
//	stringTestCase3();
//	stringTestCase4();
//	stringTestCase5();
//	stringTestCase6();
//	stringTestCase7();
//	stringTestCase8();
//	stringTestCase9();
//	stringTestCase10();
//	stringTestCase11();
//	stringTestCase12();
//	stringTestCase13();
//}

void testAlloc() {
	allocTestCase1();
	allocTestCase2();
	allocTestCase3();
	allocTestCase4();
}

void testList() {
	listTestCase1();
	listTestCase2();
	listTestCase3();
	listTestCase4();
	listTestCase5();
	listTestCase6();
	listTestCase7();
	listTestCase8();
	listTestCase9();
}

int main(int argc, char* argv[]) {

	// testString();
	testAlloc();
	testList();
	return 0;
}