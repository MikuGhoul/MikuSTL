#include <iostream>
#include <cassert>

#include "Test/testString.hpp"
#include "Test/testVector.hpp"
#include "Test/testHeader.hpp"

void testString() {
	stringTestCase1();
	stringTestCase2();
	stringTestCase3();
	stringTestCase4();
}


int main(int argc, char* argv[]) {

	testString();
	
	return 0;
}