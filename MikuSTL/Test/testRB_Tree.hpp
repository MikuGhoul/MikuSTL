#ifndef TEST_TB_TREE__
#define TEST_TB_TREE__

#include "../Include/MikuRB_Tree.h"

template<class T>
struct _Identity {
	const T& operator()(const T& _x) const {
		return _x;
	}
};

void rbtreeTestCase1() {
	Miku::RB_Tree<int, int, _Identity<int>, std::less<int>> _rb1;
	_rb1.begin();
	_rb1.end();
	_rb1.empty();
	_rb1.size();
}

void rbtreeTestCase2() {

}

void rbtreeTestCase3() {

}

void rbtreeTestCase4() {

}

void rbtreeTestCase5() {

}

void rbtreeTestCase6() {

}

#endif // !TEST_TB_TREE__
