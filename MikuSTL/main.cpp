#include <iostream>
#include <cassert>



#include "Test/testAlloc.hpp"
#include "Test/testList.hpp"
#include "Test/testVector.hpp"
#include "Test/testArray.hpp"
#include "Test/testDeque.hpp"
#include "Test/testRB_Tree.hpp"
//#include "Test/testString.hpp"
//#include "Test/testVector.hpp"
//#include "Test/testHeader.hpp"

#include "Test/TestPerformance.hpp"

#include "Test/TestListPerformance.hpp"
#include "Test/TestVectorPerformance.hpp"
#include "Test/TestDequePerformance.hpp"

void testAlloc() {
	allocTestCase1();
	allocTestCase2();
	allocTestCase3();
	allocTestCase4();
	allocTestCase5();
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
	listTestCase10();
	listTestCase11();
	listTestCase12();
	listTestCase13();
	listTestCase14();
}

void testVector() {
	vectorTestCase1();
	vectorTestCase2();
	vectorTestCase3();
	vectorTestCase4();
	vectorTestCase5();
	vectorTestCase6();
	vectorTestCase7();
	vectorTestCase8();
	vectorTestCase9();
	vectorTestCase10();
	vectorTestCase11();
	vectorTestCase12();
}

void testArray() {
	arrayTestCase1();
	arrayTestCase2();
	arrayTestCase3();
	arrayTestCase4();
	arrayTestCase5();
}

void testDeque() {
	dequeTestCase1();
	dequeTestCase2();
	dequeTestCase3();
	dequeTestCase4();
	dequeTestCase5();
	dequeTestCase6();
	dequeTestCase7();
	dequeTestCase8();
	dequeTestCase9();
	dequeTestCase10();
	dequeTestCase11();
	dequeTestCase12();
	dequeTestCase13();
	dequeTestCase14();
	dequeTestCase15();
	dequeTestCase16();
	dequeTestCase17();
}

void testRbTree() {
	rbtreeTestCase1();
	rbtreeTestCase2();
	rbtreeTestCase3();
	rbtreeTestCase4();
	rbtreeTestCase5();
	rbtreeTestCase6();
}

void basic_test() {
	testAlloc();
	testList();
	testVector();
	testArray();
	testDeque();
	testRbTree();
}

void performance_test() {
	// list_test();
	// vector_test();
	// deque_test();
}

int main(int argc, char* argv[]) {

	basic_test();
	// performance_test();
	return 0;
}