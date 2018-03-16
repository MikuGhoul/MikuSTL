#include <iostream>
#include <cassert>



#include "Test/testString.hpp"
#include "Test/testVector.hpp"
#include "Test/testHeader.hpp"
#include "Test/testAlloc.hpp"

void testString() {
	stringTestCase1();
	stringTestCase2();
	stringTestCase3();
	stringTestCase4();
	stringTestCase5();
	stringTestCase6();
	stringTestCase7();
	stringTestCase8();
	stringTestCase9();
	stringTestCase10();
	stringTestCase11();
	stringTestCase12();
	stringTestCase13();
}

void testAlloc() {
	allocTestCase1();
}


int main(int argc, char* argv[]) {

	// testString();
	testAlloc();
	return 0;
}