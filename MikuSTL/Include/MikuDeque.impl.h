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
		/*map_pointer _N_map = Miku::allocator<pointer>::allocate(_Map_Size);
		for (int i = 0; i != _Map_Size; ++i)
			_N_map[i] = _New_Buffer();
		return _N_map;*/
		// �ع���һ�£���ʼ������������mapSize������buffer
		return Miku::allocator<pointer>::allocate(_Map_Size);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Init_Map(size_type _Element_Size) {

		// map����Ҫ��buffer�� = element���� / ÿ��buffer��element�ĸ��� + 1
		size_type _Buffer_Count = _Element_Size / iterator::_Deque_Buffer_Size() + 1;
		
		// +2����Ϊ����start��finish��λ��Ҫ������map���м䲿��
		mapSize = std::max(_Min_Buffer_Count(), _Buffer_Count + 2);

		// ������map��û���κ�buffer
		map = _New_Map(mapSize);

		// start��finish�����ԳƷ�����map������
		map_pointer _Tmp_start = map + (mapSize - _Buffer_Count) / 2;
		map_pointer _Tmp_finish = _Tmp_start + _Buffer_Count - 1;

		// ֻ����start��finish֮���buffer����������mapSize��buffer����ʡ�ڴ�
		for (auto i = _Tmp_start; i <= _Tmp_finish; ++i)
			*i = _New_Buffer();


		// _Set_Node���Է������_B_First��_B_Last
		start._Set_Node(_Tmp_start);
		finish._Set_Node(_Tmp_finish);

		start._B_Cur = start._B_First;
		finish._B_Cur = finish._B_First + _Element_Size % iterator::_Deque_Buffer_Size();
	}



	template<class T, class Allocator>
	void deque<T, Allocator>::_Push_Front_Aux(size_type value) {
		*(start._B_Node - 1) = _New_Buffer();
		start._Set_Node(start._B_Node - 1);
		start._B_Cur = start._B_Last - 1;
		allocator_type::construct(start._B_Cur, value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Push_Back_Aux(size_type value) {
		*(finish._B_Node + 1) = _New_Buffer();
		finish._Set_Node(finish._B_Node + 1);
		finish._B_Cur = finish._B_First + 1;
		allocator_type::construct(finish._B_Cur - 1, value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Map_Growth() {
		size_type _Old_Buf_Count = finish._B_Node - start._B_Node + 1;

		// ����vector, ��������2���ռ�
		mapSize *= 2;
		auto _new_map = _New_Map(mapSize);

		// old map ���� new map ���м䣬ֻ����old map����buffer�Ĳ��־ͺ���
		map_pointer _Tmp_start = _new_map + (mapSize - _Old_Buf_Count) / 2;

		// ����������ָ��buffer��ָ�룬ʵ��element�����п���
		for (int i = 0; i != _Old_Buf_Count; ++i)
			*(_Tmp_start + i) = *(start._B_Node + i);

		start._Set_Node(_Tmp_start);
		finish._Set_Node(_Tmp_start + _Old_Buf_Count - 1);

		Miku::allocator<pointer>::deallocate(map);

		map = _new_map;
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
	void deque<T, Allocator>::push_front(const_reference value) {
		// 1. start���ڵ�buffer���ˣ�Ҳ��һ����������finish��start��һ��buffer�Ϳ��Բ������������ָ������ǰpush��
		if (start._B_Cur == start._B_First) {
			// 1.1 ���˵����buffer��map�ĵ�һ��buffer
			if (start._B_Node == map) {
				/* map�ռ�������� */
				_Map_Growth();

				/* ��push���пռ��� */
				_Push_Front_Aux(value);
			}
			// 1.2 ���ǵ�һ��buffer
			else {
				/* ����һ��buffer��map�е�ǰһ���ڵ㣬start�ƹ�ȥ */
				_Push_Front_Aux(value);
			}
		}
		// 2. ��ǰbufferδ����ֱ�ӹ���
		else {
			--start;
			allocator_type::construct(start._B_Cur, value);
		}
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_front(value_type&& value) {
		push_front(value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::pop_front() {
		allocator_type::destroy(start._B_Cur);
		++start;
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_back(const_reference value) {
		// ˼·��push_frontһ��
		if (finish._B_Cur == finish._B_Last) {
			if (finish._B_Node == map + mapSize - 1) {

				_Map_Growth();

				_Push_Back_Aux(value);

			}
			else {
				_Push_Back_Aux(value);
			}
		}
		else {
			allocator_type::construct(finish._B_Cur, value);

			// finish._B_Cur ��������һ��element��������������������л�����һ��buffer
			if (finish._B_Cur == finish._B_Last - 1)
				++finish._B_Cur;
			else
				++finish;
		}
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::push_back(value_type&& value) {
		push_back(value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::pop_back() {
		--finish;
		allocator_type::destroy(finish._B_Cur);
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::Insert_Aux(iterator pos, const_reference value) {
		
		difference_type _pos_index = pos - start;

		// pos ������ start
		if (_pos_index < size() / 2) {

		}
		// pos ������ finish
		else {

		}

		return start;

	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::Insert_Aux(iterator pos, size_type count, const_reference value) {

		difference_type _pos_index = pos - start;

		// 1. pos ������ start
		if (_pos_index < size() / 2) {
			// 1.1 start����bufferǰ��Ŀ�λ��������count
			if (start._B_Cur - start._B_First >= count) {
				// 1.1.1 [start._B_Cur, pos)�ĳ��ȴ���count
				if (pos - start._B_Cur > count) {

					// 1.1.1.1 �ƶ�posǰ��ǰcount���ռ� (old����)
					std::uninitialized_copy_n(start._B_Cur, count, start._B_Cur - count);

					// 1.1.1.2 �ƶ�posǰ��ʣ�ಿ��(old)
					std::copy(start._B_Cur + count, pos, start._B_Cur);

					// 1.1.1.3 copy assignment count���ռ�(new)
					std::fill_n(pos - count, count, value);

				}
				// 1.1.2 [start._B_Cur, pos)�ĳ���С�ڵ���count
				else {

					// 1.1.2.1 �ƶ�posǰ��ȫ���ռ� (old)
					std::uninitialized_copy(start._B_Cur, pos, start._B_Cur - count);

					// 1.1.2.2 copy ctor count��ǰ start._B_Cur - pos ���ռ�(new)
					std::uninitialized_fill_n(start._B_Cur - (pos - start._B_Cur), count - (pos - start._B_Cur), value);

					// 1.1.2.3 copy assignment count��ʣ�ಿ��(new)
					std::fill(pos - (pos - start._B_Cur), pos, value);

				}
				start -= count;
				return pos - count;
			}
			// 1.2 start���ڵ�bufferǰ��Ŀ�λ����
			else {
				// 1.2.1 ���buffer��map�ĵ�һbuffer
				if (start._B_Node == map) {
					// TODO
					// ���_Map_Growth()һ�κ�Ŀռ䶼�����أ�
				}
				// 1.2.2 ���ǵ�һ��buffer
				else {
					// TODO
					// ���һ��_New_Buffer()�󲻹��أ�
				}
			}
		}
		// 2. pos ������ finish
		else {

		}
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(iterator pos, const_reference value) {
		if (pos._B_Cur == start._B_Cur) {
			push_front(value);
			return start;
		}
		else if (pos._B_Cur == finish._B_Cur) {
			push_back(value);
			return finish - 1;
		}
		else
			return Insert_Aux(pos, value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Insert_Start_Aux(size_type count, const_reference value) {
		*(start._B_Node - 1) = _New_Buffer();
		start -= count;
		std::uninitialized_fill_n(start, count, value);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Insert_Finish_Aux(size_type count, const_reference value) {
		*(finish._B_Node + 1) = _New_Buffer();
		std::uninitialized_fill_n(finish, count, value);
		finish += count;
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::insert(iterator pos, size_type count, const_reference value) {
		// 1. ���У�����λ����begin()
		if (pos._B_Cur == start._B_Cur) {
			// 1.1. ���start����bufferǰ��Ŀ�λ��������count
			if (start._B_Cur - start._B_First >= count) {
				start -= count;
				std::uninitialized_fill_n(start, count, value);
			}
			// 1.2. ���start���ڵ�bufferǰ��Ŀ�λ����
			else {
				// 1.2.1. ������buffer����map�еĵ�һ��buffer
				if (start._B_Node == map) {
					_Map_Growth();

					_Insert_Start_Aux(count, value);
				}
				// 1.2.2. ���ǵ�һ��buffer
				else {
					_Insert_Start_Aux(count, value);
				}
			}
		}
		// 2. ���У�����λ����end()
		else if (pos._B_Cur == finish._B_Cur) {
			// 2.1. ���finish���ڵ�buffer����Ŀ�λ��������count
			if (finish._B_Last - finish._B_Cur >= count) {
				std::uninitialized_fill_n(finish, count, value);
				finish += count;
			}
			// 2.2 ���finish���ڵ�buffer����Ŀ�λ����
			else {
				// 2.2.1 ���һ��buffer
				if (finish._B_Node == map + mapSize - 1) {
					_Map_Growth();
					
					_Insert_Finish_Aux(count, value);
				}
				// 2.2.2 �������һ��buffer
				else {
					_Insert_Finish_Aux(count, value);
				}
			}
		}
		// 3. ��begin()��end()֮��
		else
			return Insert_Aux(pos, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void deque<T, Allocator>::insert(iterator pos, InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		
	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist) {

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
