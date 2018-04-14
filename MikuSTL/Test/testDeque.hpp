#ifndef TEST_DEQUE_H__
#define TEST_DEQUE_H__

#include "../Include/MikuDeque.h"

void dequeTestCase1() {
	Miku::deque<int> _deq_1;
	Miku::deque<int> _deq_2(3, 100);
	// �����������ΪtypeΪintʱ��ÿ��buffer��СΪ512 / 4 = 128
	Miku::deque<int> _deq_3(130, 100);
	Miku::deque<int> _deq_4(_deq_3.begin(), _deq_3.end());
	Miku::deque<int> _deq_5{ 1,2,3 };

	assert(_deq_1.size() == 0);
	assert(_deq_2.size() == 3);
	assert(_deq_3.size() == 130);
	assert(_deq_4.size() == 130);
	assert(_deq_5.size() == 3);

	Miku::deque<int> _deq_6(std::move(_deq_5));
	assert(_deq_6.size() == 3);
}

void dequeTestCase2() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	Miku::deque<int>::iterator _iter_1 = _deq_1.begin();
	Miku::deque<int>::iterator _iter_2 = _deq_1.end();

	assert(*_iter_1 == 1);
	assert(*(--_iter_2) == 3);
	assert(_iter_1 != _iter_2);
	assert(_iter_1 == _deq_1.begin());

	assert(_deq_1[1] == 2);
	assert(_deq_1.at(2) == 3);

	assert(_iter_2 - _iter_1 == 2);
	assert(_iter_1 + 2 == _iter_2);
	_iter_1 += 2;
	assert(_iter_1 == _iter_2);
}

void dequeTestCase3() {
	const Miku::deque<int> _deq_1{ 1,2,3 };
	Miku::deque<int>::const_iterator _iter_1 = _deq_1.begin();
	_iter_1++;			// ok
	// *_iter_1 = -1	// error

	Miku::deque<int> _deq_2{ 1,2,3 };
	const Miku::deque<int>::iterator _iter_2 = _deq_2.begin();
	// _iter_2++;		// error
	*_iter_2 = -1;		// ok

	Miku::deque<int> _deq_3{ 1,2,3 };
	Miku::deque<int>::const_iterator _iter_3 = _deq_3.cbegin();
	_iter_3 += 3;		// ok
	// *_iter_3 = -1;	// error

	assert(_deq_1[1] == 2);
}

void dequeTestCase4() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	assert(*(_deq_1.begin()) == 1);
	assert(*(_deq_1.end() - 1) == 3);
	assert(_deq_1.front() == 1);
	assert(_deq_1.back() == 3);

	const Miku::deque<int> _deq_2{ 3,2,1 };
	assert(_deq_2.front() == 3);
	assert(_deq_2.back() == 1);

}

void dequeTestCase5() {
	Miku::deque<int> _deq_1(300, 3);
	assert(_deq_1.size() == 300);
	_deq_1.clear();
	assert(_deq_1.size() == 0);
}

void dequeTestCase6() {
	/*Miku::deque<int> _deq_1(128 * 4, 2);
	std::cout << _deq_1.back_full() << std::endl;
	std::cout << _deq_1.front_full() << std::endl;*/

	Miku::deque<int> _deq_1{ 1,2,3 };
	assert(_deq_1.size() == 3);

	_deq_1.push_back(47);
	assert(_deq_1.size() == 4);
	assert(_deq_1.back() == 47);

	_deq_1.push_front(17);
	assert(_deq_1.size() == 5);
	assert(_deq_1.front() == 17);

	_deq_1.pop_back();
	assert(_deq_1.size() == 4);
	assert(_deq_1.back() == 3);

	_deq_1.pop_front();
	assert(_deq_1.size() == 3);
	assert(_deq_1.front() == 1);

}

void dequeTestCase7() {
	Miku::deque<int> _deq_1;
	
	// ����Ҳû������ʽ���ԣ�����������仰���Դ�ϵ㣬���ڴ����ݱ仯
	// ֮����127�� 129��Щ����Ϊint�ᵼ��buffer����Ϊ128

	// Ŀǰ����ƣ�����push_front() ������һ��buffer
	for (int i = 0; i != 127; ++i)
		_deq_1.push_front(1);
	assert(_deq_1.size() == 127);

	// ��push_front()���������buffer���������buffer��map�ĵ�һ��buffer
	_deq_1.push_front(1);
	assert(_deq_1.size() == 128);

	// ��push_front()������������һ�������ռ��map
	_deq_1.push_front(1);
	assert(_deq_1.size() == 129);	
}

void dequeTestCase8() {
	Miku::deque<int> _deq_1;

	// ��128������bufferδ��ʱ�����
	for (int i = 0; i != 128; ++i)
		_deq_1.push_back(1);
	assert(_deq_1.size() == 128);

	// ����ᵼ�� new һ���� buffer
	_deq_1.push_back(1);
	assert(_deq_1.size() == 129);

	// ������map�е����һ��buffer��push��
	// Ĭ��mapSizeΪ4������Ǵ�map[1]��ʼ����buffer������push_back����Ҫ3��buffer
	for (int i = 0; i != 127 + 128; ++i)
		_deq_1.push_back(1);
	assert(_deq_1.size() == 129 + 127 + 128);

	// ��ʱ����������һ�������ռ��map
	_deq_1.push_back(1);
	assert(_deq_1.size() == 129 + 127 + 128 + 1);

}

void dequeTestCase9() {
	Miku::deque<int> _deq_1{ 1,2,3 };

	auto _iter_1 = _deq_1.insert(_deq_1.begin(), 0);
	assert(_deq_1.size() == 4);
	assert(_deq_1.front() == 0);
	assert(*_iter_1 == 0);

	auto _iter_2 = _deq_1.insert(_deq_1.end(), 4);
	assert(_deq_1.size() == 5);
	assert(_deq_1.back() == 4);
	assert(*_iter_2 == 4);

}

void dequeTestCase10() {
	Miku::deque<int> _deq_1{ 1,2,3,4,5,6 };

	auto _iter_1 = _deq_1.insert(_deq_1.begin() + 2, 100);
	auto _iter_2 = _deq_1.insert(_deq_1.end() - 2, 200);

	assert(*(_deq_1.begin() + 2) == 100);
	assert(*(_deq_1.end() - 3) == 200);

	assert(*_iter_1 == 100);
	assert(*_iter_2 == 200);

}

void dequeTestCase11() {
	Miku::deque<int> _deq_1{ 1,2,3,4,5,6 };
	_deq_1.insert(_deq_1.begin(), 3, -1);
	assert(*_deq_1.begin() == -1);
	assert(_deq_1.size() == 9);

	_deq_1.insert(_deq_1.end(), 200, -1);
	assert(_deq_1.size() == 209);
}

void dequeTestCase12() {
	Miku::deque<int> _deq_1{ 1,2,3,4,5,6 };
	_deq_1.insert(_deq_1.begin() + 1, 3, -1);
	assert(_deq_1.size() == 9);

	_deq_1.insert(_deq_1.end() - 1, 3, -2);
	assert(_deq_1.size() == 12);

	// ����insert�� start._B_Node == map ���� ʣ��ռ䲻�� �����
	_deq_1.insert(_deq_1.begin(), 200, 3);
	assert(_deq_1.size() == 212);

}

void dequeTestCase13() {
	// ����insert��count����һ��buffer�����
	Miku::deque<int> _deq_1{ 1,2,3,4,5,6 };
	_deq_1.insert(_deq_1.begin(), 200, -1);
	assert(_deq_1.size() == 206);

	Miku::deque<int> _deq_2{ 1,2,3,4,5,6 };
	_deq_2.insert(_deq_2.end(), 200, -1);
	assert(_deq_2.size() == 206);
}

void dequeTestCase14() {
	Miku::deque<int> _deq_1{ 1,2,3,4,5,6 };
	Miku::deque<int> _deq_2{ -1,-2,-3,-4,-5,-6 };

	_deq_1.insert(_deq_1.begin(), _deq_2.begin(), _deq_2.end());

	assert(_deq_1.size() == 12);

	_deq_2.insert(_deq_2.begin() + 1, { 1,2,3,4,5 });
	
	assert(_deq_2.size() == 11);
}

void dequeTestCase15() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	Miku::deque<int> _deq_2{ 0,1,2,3 };

	assert(_deq_1 != _deq_2);
	_deq_1.push_front(0);
	assert(_deq_1 == _deq_2);
}

void dequeTestCase16() {
	Miku::deque<int> _deq_1{ 1,2,3,4 };
	auto _iter_1 = _deq_1.begin() + 1;
	auto _iter_2 = _deq_1.end() - 1;
	_deq_1.erase(_iter_1, _iter_2);
	
	Miku::deque<int> _deq_2{ 1,4 };
	assert(_deq_1 == _deq_2);
}

void dequeTestCase17() {
	Miku::deque<int> _deq_1{ 1,2,3 };
	auto _iter_1 = _deq_1.begin() + 1;

	Miku::deque<int> _deq_2{ -1,-2,-3,-4 };
	auto _iter_2 = _deq_2.begin() + 1;

	_deq_1.swap(_deq_2);

	assert(_deq_1.size() == 4);
	assert(_deq_2.size() == 3);
	assert(*_iter_1 == 2);
	assert(*_iter_2 == -2);
}

#endif // !TEST_DEQUE_H__
