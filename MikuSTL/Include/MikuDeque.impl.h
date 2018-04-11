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

		template<class T>
		typename _Deque_Iterator<T>::self& _Deque_Iterator<T>::operator+=(difference_type _Dis) {
			if (_Dis < _B_Last - _B_Cur)
				_B_Cur += _Dis;
			else {
				auto _Left_Size = _B_Last - _B_Cur;
				_Dis -= _Left_Size;
				_Set_Node(_B_Node + _Dis / _Deque_Buffer_Size() + 1);
				_B_Cur = _B_First + _Dis % _Deque_Buffer_Size();
				// auto _Buf_count = _Dis / _Deque_Buffer_Size();
				
			}
			return *this;
		}

		template<class T>
		typename _Deque_Iterator<T>::self _Deque_Iterator<T>::operator+(difference_type _Dis) {
			self _temp = *this;
			return _temp += _Dis;
		}

		template<class T>
		typename _Deque_Iterator<T>::self& _Deque_Iterator<T>::operator-=(difference_type _Dis) {
			if (_Dis <= _B_Cur - _B_First)
				_B_Cur -= _Dis;
			else {
				auto _Left_Size = _B_Cur - _B_First;
				_Dis -= _Left_Size;
				_Set_Node(_B_Node - _Dis / _Deque_Buffer_Size() + 1);
				_B_Cur = _B_Last - _Dis % _Deque_Buffer_Size();
			}
			return *this;
		}

		template<class T>
		typename _Deque_Iterator<T>::self _Deque_Iterator<T>::operator-(difference_type _Dis) {
			self _temp = *this;
			return _temp -= _Dis;
		}


		// TOOD
		// const_iterator

		template<class T>
		void _Deque_Const_Iterator<T>::_Set_Node(map_pointer _New_Node) {
			_B_Node = _New_Node;
			_B_First = *_New_Node;
			_B_Last = _B_First + static_cast<difference_type>(_Deque_Buffer_Size());
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self& _Deque_Const_Iterator<T>::operator++() {
			++_B_Cur;
			if (_B_Cur == _B_Last) {		// iterator���ﵱǰbufferĩβ
				_Set_Node(_B_Node + 1);		// �л�����һ��buffer
				_B_Cur = _B_First;			// iteratorָ����һ��buffer�����Ŀ�ͷ
			}
			return *this;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self _Deque_Const_Iterator<T>::operator++(int) {
			self _temp = *this;
			++*this;
			return _temp;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self& _Deque_Const_Iterator<T>::operator--() {
			if (_B_Cur == _B_First) {		// iterator���ǵ�ǰbuffer���
				_Set_Node(_B_Node - 1);		// �л�����һ��buffer
				_B_Cur = _B_Last;			// iteratorָ����һ��buffer��ĩβ�ĺ�һ��Ԫ��
			}
			--_B_Cur;
			return *this;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self _Deque_Const_Iterator<T>::operator--(int) {
			self _temp = *this;
			--*this;
			return _temp;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::difference_type _Deque_Const_Iterator<T>::operator-(const self& other) const {
			// ÿ��buffer�е�Ԫ�ظ��� * ����iterator����֮�������ݵ�buffer + ����iterator���ڵ�buffer��Ԫ��ʣ����
			return difference_type(_Deque_Buffer_Size()) * (_B_Node - other._B_Node - 1) +
				(_B_Cur - _B_First) + (other._B_Last - other._B_Cur);
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self& _Deque_Const_Iterator<T>::operator+=(difference_type _Dis) {
			if (_Dis < _B_Last - _B_Cur)
				_B_Cur += _Dis;
			else {
				auto _Left_Size = _B_Last - _B_Cur;
				_Dis -= _Left_Size;
				_Set_Node(_B_Node + _Dis / _Deque_Buffer_Size() + 1);
				_B_Cur = _B_First + _Dis % _Deque_Buffer_Size();
				// auto _Buf_count = _Dis / _Deque_Buffer_Size();

			}
			return *this;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self _Deque_Const_Iterator<T>::operator+(difference_type _Dis) {
			self _temp = *this;
			return _temp += _Dis;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self& _Deque_Const_Iterator<T>::operator-=(difference_type _Dis) {
			if (_Dis <= _B_Cur - _B_First)
				_B_Cur -= _Dis;
			else {
				auto _Left_Size = _B_Cur - _B_First;
				_Dis -= _Left_Size;
				_Set_Node(_B_Node - _Dis / _Deque_Buffer_Size() + 1);
				_B_Cur = _B_Last - _Dis % _Deque_Buffer_Size();
			}
			return *this;
		}

		template<class T>
		typename _Deque_Const_Iterator<T>::self _Deque_Const_Iterator<T>::operator-(difference_type _Dis) {
			self _temp = *this;
			return _temp -= _Dis;
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
		std::uninitialized_copy(other.begin(), other.end(), start);
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(deque&& other) : start(other.start), finish(other.finish), map(other.map), mapSize(other.mapSize) {
		other.map = nullptr;
		other.mapSize = 0;
		// TODO, ������Ϊstart��finish����ָ�룬���Բ���ֱ����nullptr��Ӧ��дһ����iterator��ָ�붼�ÿյĺ�����
		// start = ;
		// finish = ;

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(std::initializer_list<value_type> init) {
		_Init_Map(init.size());
		std::uninitialized_copy(init.begin(), init.end(), start);
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::reference deque<T, Allocator>::operator[](size_type pos) {
		return *(start + pos);
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::const_reference deque<T, Allocator>::operator[](size_type pos) const {
		return *(static_cast<const_iterator>(start) + pos);
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::reference deque<T, Allocator>::at(size_type pos) {
		if (pos >= size())
			throw std::out_of_range("out of range.");
		return operator[](pos);
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::const_reference deque<T, Allocator>::at(size_type pos) const {
		if (pos >= size())
			throw std::out_of_range("out of range.");
		return operator[](pos);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_back(const_reference value) {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_back(value_type&& value) {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::pop_back() {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_front(const_reference value) {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_front(value_type&& value) {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::pop_front() {

	}

	template<class T, class Allocator>
	void deque<T, Allocator>::clear() noexcept {
		// dtor �� deallocate start��finish֮�����buffer
		for (map_pointer _i_node = start._B_Node + 1; _i_node < finish._B_Node; ++_i_node) {
			allocator_type::destroy(*_i_node, *_i_node + iterator::_Deque_Buffer_Size());
			allocator_type::deallocate(*_i_node);
		}
		// dtor �� deallocate�� start��finishָ������bufferʱ
		if (start._B_Cur != finish._B_Cur) {
			allocator_type::destroy(start._B_Cur, start._B_Last);
			/* allocator_type::deallocate(start._B_First); */

			allocator_type::destroy(finish._B_First, finish._B_Cur);
			allocator_type::deallocate(finish._B_First);
		}
		// start��finishָ��ͬһ��bufferʱ
		else {
			allocator_type::destroy(start._B_Cur, finish._B_Cur);
			allocator_type::deallocate(start._B_First);
		}

		// ��û������deallocate����buffer, ����һ��
		start._B_Cur = start._B_First;
		finish = start;
		// Miku::allocator<map_pointer>::deallocate(map);

	}

}

#endif // !MIKU_DEQUE_IMPL_H__
