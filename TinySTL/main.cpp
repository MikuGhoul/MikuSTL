#include <iostream>

#include "Test/testMacro.h"
#include "Test/testString.hpp"
#include "Test/testVector.hpp"


void testString() {
	stringTestCase1();
	stringTestCase2();
	stringTestCase3();
	stringTestCase4();
}


int main(int argc, char* argv[]) {

	testString();
	std::cout << test_pass << "/" << test_count << std::endl 
		<< test_pass * 100.0 / test_count << "% Passed" << std::endl;

	return main_ret;
}