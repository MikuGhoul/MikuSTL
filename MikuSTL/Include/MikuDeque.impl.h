#ifndef MIKU_DEQUE_IMPL_H__
#define MIKU_DEQUE_IMPL_H__

namespace Miku {

	namespace Internal {

		template<class T>
		void _Deque_Iterator<T>::_Set_Node(map_pointer _New_Node) {
			_B_Node = _New_Node;
			_B_First = *_New_Node;
			_B_Last = _B_First + static_cast<difference_type>(_Deque_Buffer_Size());
		}

		template<class T>
		typename _Deque_Iterator<T>::self& _Deque_Iterator<T>::operator++() {
			++_B_Cur;
			if (_B_Cur == _B_Last) {		// iterator���ﵱǰbufferĩβ
				_Set_Node(_B_Node + 1);		// �л�����һ��buffer
				_B_Cur = _B_First;			// iteratorָ����һ��buffer�����Ŀ�ͷ
			}
			return *this;
		}

		template<class T>
		typename _Deque_Iterator<T>::self _Deque_Iterator<T>::operator++(int) {
			self _temp = *this;
			++*this;
			return _temp;
		}

		template<class T>
		typename _Deque_Iterator<T>::self& _Deque_Iterator<T>::operator--() {
			if (_B_Cur == _B_First) {		// iterator���ǵ�ǰbuffer���
				_Set_Node(_B_Node - 1);		// �л�����һ��buffer
				_B_Cur = _B_Last;			// iteratorָ����һ��buffer��ĩβ�ĺ�һ��Ԫ��
			}
			--_B_Cur;
			return *this;
		}

		template<class T>
		typename _Deque_Iterator<T>::self _Deque_Iterator<T>::operator--(int) {
			self _temp = *this;
			--*this;
			return _temp;
		}

		template<class T>
		typename _Deque_Iterator<T>::difference_type _Deque_Iterator<T>::operator-(const self& other) const {
			// ÿ��buffer�е�Ԫ�ظ��� * ����iterator����֮�������ݵ�buffer + ����iterator���ڵ�buffer��Ԫ��ʣ����
			return difference_type(_Deque_Buffer_Size()) * (_B_Node - other._B_Node - 1) +
				(_B_Cur - _B_First) + (other._B_Last - other._B_Cur);
		}

	}


	template<class T, class Allocator>
	typename deque<T, Allocator>::pointer deque<T, Allocator>::_New_Buffer() {
		return allocator_type::allocate(iterator::_Deque_Buffer_Size());
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::map_pointer deque<T, Allocator>::_New_Map(const size_type _Map_Size) {
		map_pointer _N_map = Miku::allocator<pointer>::allocate(_Map_Size);
		for (int i = 0; i != _Map_Size; ++i)
			_N_map[i] = _New_Buffer();
		return _N_map;
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Init_Map(size_type _Element_Size) {

		// map����Ҫ��buffer�� = element���� / ÿ��buffer��element�ĸ��� + 1
		size_type _Buffer_Count = _Element_Size / iterator::_Deque_Buffer_Size() + 1;
		
		// +2����Ϊ����start��finish��λ��Ҫ������map���м䲿��
		mapSize = std::max(_Min_Buffer_Count(), _Buffer_Count + 2);
		map = _New_Map(mapSize);

		// start��finish�����ԳƷ�����map������
		map_pointer _Tmp_start = map + (mapSize - _Buffer_Count) / 2;
		map_pointer _Tmp_finish = _Tmp_start + _Buffer_Count - 1;

		// _Set_Node���Է������_B_First��_B_Last
		start._Set_Node(_Tmp_start);
		finish._Set_Node(_Tmp_finish);

		start._B_Cur = start._B_First;
		finish._B_Cur = finish._B_First + _Element_Size % iterator::_Deque_Buffer_Size();
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque() : start(), finish(), map(nullptr), mapSize(0){
		_Init_Map();
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(size_type count, const_reference value) : start(), finish(), map(nullptr), mapSize(0) {
		_Init_Map(count);
		// ��finishǰ��ÿһ��buffer���ض������ģ��е�element����copy ctor
		for (map_pointer i = start._B_Node; i != finish._B_Node; ++i)
			std::uninitialized_fill(*i, *i + iterator::_Deque_Buffer_Size(), value);
		// finishָ���buffer����
		std::uninitialized_fill(finish._B_First, finish._B_Cur, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	deque<T, Allocator>::deque(InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) : start(), finish(), map(nullptr), mapSize(0) {
		_Init_Map(last - first);
		std::uninitialized_copy(first, last, start);
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque& other) : start(), finish(), map(nullptr), mapSize(0) {
		_Init_Map(other.size());
		std::uninitialized_copy()
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque&& other) : start(other.start), finish(other.finish), map(other.map), mapSize(other.mapSize) {
		other.map = nullptr;
		other.mapSize = 0;
		// TODO, ������Ϊstart��finish����ָ�룬���Բ���ֱ����nullptr��Ӧ��дһ����iterator��ָ�붼�ÿյĺ�����
		// start = ;
		// finish = ;

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(std::initializer_list<value_type> init) {

	}

}

#endif // !MIKU_DEQUE_IMPL_H__
