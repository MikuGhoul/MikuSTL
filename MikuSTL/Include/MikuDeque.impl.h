#ifndef MIKU_DEQUE_IMPL_H__
#define MIKU_DEQUE_IMPL_H__

namespace Miku {

	namespace Internal {

		/*template<class T>
		_Deque_Iterator<T>::_Deque_Iterator() {

		}*/

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
		typename _Deque_Iterator<T>::difference_type _Deque_Iterator<T>::operator-(const_reference other) const {
			// 每个buffer中的元素个数 * 两个iterator距离之间满数据的buffer + 两个iterator所在的buffer中元素剩余数
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
	void deque<T, Allocator>::_Init_Map() {
		mapSize = 2;
		map = _New_Map(mapSize);

		// TODO

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque() : start(), finish(), map(nullptr), mapSize(0){}

	template<class T, class Allocator>
	explicit deque<T, Allocator>::deque(size_type count, const_reference value) :deque() {
		// 
	}

	template<class T, class Allocator>
	template<class InputIt>
	deque<T, Allocator>::deque(InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque& other) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque&& ohter) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(std::initializer_list<value_type> init) {

	}

}

#endif // !MIKU_DEQUE_IMPL_H__
