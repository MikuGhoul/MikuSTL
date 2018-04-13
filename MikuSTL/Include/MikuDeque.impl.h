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
			if (_B_Cur == _B_Last) {		// iterator到达当前buffer末尾
				_Set_Node(_B_Node + 1);		// 切换至下一个buffer
				_B_Cur = _B_First;			// iterator指向下一个buffer的起点的开头
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
			if (_B_Cur == _B_First) {		// iterator已是当前buffer起点
				_Set_Node(_B_Node - 1);		// 切换至上一个buffer
				_B_Cur = _B_Last;			// iterator指向上一个buffer的末尾的后一个元素
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
			// 每个buffer中的元素个数 * 两个iterator距离之间满数据的buffer + 两个iterator所在的buffer中元素剩余数
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
			if (_B_Cur == _B_Last) {		// iterator到达当前buffer末尾
				_Set_Node(_B_Node + 1);		// 切换至下一个buffer
				_B_Cur = _B_First;			// iterator指向下一个buffer的起点的开头
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
			if (_B_Cur == _B_First) {		// iterator已是当前buffer起点
				_Set_Node(_B_Node - 1);		// 切换至上一个buffer
				_B_Cur = _B_Last;			// iterator指向上一个buffer的末尾的后一个元素
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
			// 每个buffer中的元素个数 * 两个iterator距离之间满数据的buffer + 两个iterator所在的buffer中元素剩余数
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
		// 重构了一下，初始不会立刻申请mapSize个数的buffer
		return Miku::allocator<pointer>::allocate(_Map_Size);
	}

	template<class T, class Allocator>
	void deque<T, Allocator>::_Init_Map(size_type _Element_Size) {

		// map中需要的buffer数 = element总数 / 每个buffer中element的个数 + 1
		size_type _Buffer_Count = _Element_Size / iterator::_Deque_Buffer_Size() + 1;
		
		// +2是因为后面start和finish的位置要尽量靠map的中间部分
		mapSize = std::max(_Min_Buffer_Count(), _Buffer_Count + 2);

		// 先申请map，没有任何buffer
		map = _New_Map(mapSize);

		// start和finish尽量对称分配在map的两侧
		map_pointer _Tmp_start = map + (mapSize - _Buffer_Count) / 2;
		map_pointer _Tmp_finish = _Tmp_start + _Buffer_Count - 1;

		// 只申请start到finish之间的buffer，不会申请mapSize个buffer，节省内存
		for (auto i = _Tmp_start; i <= _Tmp_finish; ++i)
			*i = _New_Buffer();


		// _Set_Node可以方便控制_B_First和_B_Last
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

		// 类似vector, 重新申请2倍空间
		mapSize *= 2;
		auto _new_map = _New_Map(mapSize);

		// old map 放在 new map 的中间，只考虑old map中有buffer的部分就好了
		map_pointer _Tmp_start = _new_map + (mapSize - _Old_Buf_Count) / 2;

		// 仅调整所有指向buffer的指针，实际element不进行拷贝
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
		// 对finish前的每一个buffer（必定是满的）中的element调用copy ctor
		for (map_pointer i = start._B_Node; i != finish._B_Node; ++i)
			std::uninitialized_fill(*i, *i + iterator::_Deque_Buffer_Size(), value);
		// finish指向的buffer特判
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
		// TODO, 这里因为start和finish不是指针，所以不能直接置nullptr，应该写一个把iterator的指针都置空的函数？
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
		// 1. start所在的buffer满了（也不一定满，比如finish和start在一个buffer就可以不满，这里就是指不能往前push了
		if (start._B_Cur == start._B_First) {
			// 1.1 满了的这个buffer是map的第一个buffer
			if (start._B_Node == map) {
				/* map空间二倍增长 */
				_Map_Growth();

				/* 再push就有空间了 */
				_Push_Front_Aux(value);
			}
			// 1.2 不是第一个buffer
			else {
				/* 申请一个buffer给map中的前一个节点，start移过去 */
				_Push_Front_Aux(value);
			}
		}
		// 2. 当前buffer未满，直接构造
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
		// 思路和push_front一样
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

			// finish._B_Cur 如果是最后一个element，避免自增的重载里会切换到下一个buffer
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

		// pos 更靠近 start
		if (_pos_index < size() / 2) {

		}
		// pos 更靠近 finish
		else {

		}

		return start;

	}

	template<class T, class Allocator>
	typename deque<T, Allocator>::iterator deque<T, Allocator>::Insert_Aux(iterator pos, size_type count, const_reference value) {

		difference_type _pos_index = pos - start;

		// 1. pos 更靠近 start
		if (_pos_index < size() / 2) {
			// 1.1 start所在buffer前面的空位数不少于count
			if (start._B_Cur - start._B_First >= count) {
				// 1.1.1 [start._B_Cur, pos)的长度大于count
				if (pos - start._B_Cur > count) {

					// 1.1.1.1 移动pos前的前count个空间 (old数据)
					std::uninitialized_copy_n(start._B_Cur, count, start._B_Cur - count);

					// 1.1.1.2 移动pos前的剩余部分(old)
					std::copy(start._B_Cur + count, pos, start._B_Cur);

					// 1.1.1.3 copy assignment count个空间(new)
					std::fill_n(pos - count, count, value);

				}
				// 1.1.2 [start._B_Cur, pos)的长度小于等于count
				else {

					// 1.1.2.1 移动pos前的全部空间 (old)
					std::uninitialized_copy(start._B_Cur, pos, start._B_Cur - count);

					// 1.1.2.2 copy ctor count的前 start._B_Cur - pos 个空间(new)
					std::uninitialized_fill_n(start._B_Cur - (pos - start._B_Cur), count - (pos - start._B_Cur), value);

					// 1.1.2.3 copy assignment count的剩余部分(new)
					std::fill(pos - (pos - start._B_Cur), pos, value);

				}
				start -= count;
				return pos - count;
			}
			// 1.2 start所在的buffer前面的空位不够
			else {
				// 1.2.1 这个buffer是map的第一buffer
				if (start._B_Node == map) {
					// TODO
					// 如果_Map_Growth()一次后的空间都不够呢？
				}
				// 1.2.2 不是第一个buffer
				else {
					// TODO
					// 如果一次_New_Buffer()后不够呢？
				}
			}
		}
		// 2. pos 更靠近 finish
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
		// 1. 特判：插入位置在begin()
		if (pos._B_Cur == start._B_Cur) {
			// 1.1. 如果start所在buffer前面的空位数不少于count
			if (start._B_Cur - start._B_First >= count) {
				start -= count;
				std::uninitialized_fill_n(start, count, value);
			}
			// 1.2. 如果start所在的buffer前面的空位不够
			else {
				// 1.2.1. 如果这个buffer还是map中的第一个buffer
				if (start._B_Node == map) {
					_Map_Growth();

					_Insert_Start_Aux(count, value);
				}
				// 1.2.2. 不是第一个buffer
				else {
					_Insert_Start_Aux(count, value);
				}
			}
		}
		// 2. 特判：插入位置在end()
		else if (pos._B_Cur == finish._B_Cur) {
			// 2.1. 如果finish所在的buffer后面的空位数不少于count
			if (finish._B_Last - finish._B_Cur >= count) {
				std::uninitialized_fill_n(finish, count, value);
				finish += count;
			}
			// 2.2 如果finish所在的buffer后面的空位不够
			else {
				// 2.2.1 最后一个buffer
				if (finish._B_Node == map + mapSize - 1) {
					_Map_Growth();
					
					_Insert_Finish_Aux(count, value);
				}
				// 2.2.2 不是最后一个buffer
				else {
					_Insert_Finish_Aux(count, value);
				}
			}
		}
		// 3. 在begin()和end()之间
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
		// dtor 和 deallocate start与finish之间的满buffer
		for (map_pointer _i_node = start._B_Node + 1; _i_node < finish._B_Node; ++_i_node) {
			allocator_type::destroy(*_i_node, *_i_node + iterator::_Deque_Buffer_Size());
			allocator_type::deallocate(*_i_node);
		}
		// dtor 和 deallocate， start与finish指向两个buffer时
		if (start._B_Cur != finish._B_Cur) {
			allocator_type::destroy(start._B_Cur, start._B_Last);
			/* allocator_type::deallocate(start._B_First); */

			allocator_type::destroy(finish._B_First, finish._B_Cur);
			allocator_type::deallocate(finish._B_First);
		}
		// start和finish指向同一个buffer时
		else {
			allocator_type::destroy(start._B_Cur, finish._B_Cur);
			allocator_type::deallocate(start._B_First);
		}

		// 并没有真正deallocate所有buffer, 留下一个
		start._B_Cur = start._B_First;
		finish = start;
		// Miku::allocator<map_pointer>::deallocate(map);

	}

}

#endif // !MIKU_DEQUE_IMPL_H__
