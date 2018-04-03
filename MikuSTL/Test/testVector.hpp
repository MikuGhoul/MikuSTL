#ifndef TEST_VECTOR_H__
#define TEST_VECTOR_H__

#include "../Include/MikuVector.h"

void vectorTestCase1() {
	Miku::vector<int> _vec_1;
	Miku::vector<int> _vec_2(3, 111);
	Miku::vector<int> _vec_3(_vec_2.begin(), _vec_2.end());
	Miku::vector<int> _vec_4(_vec_3);

	assert(_vec_1.size() == 0);
	assert(_vec_2.size() == 3);	
	assert(_vec_3.size() == 3);
	assert(_vec_4.size() == 3);
}

void vectorTestCase2() {

}
void vectorTestCase3() {

}

void vectorTestCase4() {

}

void vectorTestCase5() {

}

void vectorTestCase6() {

}



#endif // !TEST_VECTOR_H__
