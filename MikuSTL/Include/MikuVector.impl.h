#ifndef MIKU_VECTOR_IMPL_H__
#define MIKU_VECTOR_IMPL_H__

#include "MikuVector.h"

namespace Miku {

	template<class T, class Allocator>
	typename vector<T, Allocator>::pointer vector<T, Allocator>::_New_Node() {
		return allocator_type::allocate();
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::pointer vector<T, Allocator>::_New_Node(size_type _size, const_reference _value) {
		auto p = allocator_type::allocate(_size);
		auto res = p;
		for (int i = 0; i != _size; ++i)
			allocator_type::construct(p++, _value);
		return res;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::_Ctor_Range(iterator _start, size_type _count, const_reference _value) {
		for (int i = 0; i != _count; ++i)
			allocator_type::construct(_start++, _value);
		return _start;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::_Dtor_Range(iterator _start, iterator _end) {
		for (; _start != _end; ++_start)
			allocator_type::destroy(_start);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::_Dest_All(iterator _start, iterator _end) {
		_Dtor_Range(_start, _end);
		allocator_type::deallocate(start, _end - _start);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::size_type vector<T, Allocator>::_Calc_Growth(size_type _New_size) {
		size_type _Old_size = capacity();
		size_type _Growth = _Old_size * 2;
		// 返回最大值，比如原size()为2，二倍增长后只有4，但要插入100个，需要2 + 100个空间
		if (_Growth < _New_size)
			return _New_size;
		return _Growth;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count, const_reference value) {
		start = _New_Node(count, value);
		finish = start + count;
		end_of_storage = finish;
	}

	template<class T, class Allocator>
	template<class InputIt>
	vector<T, Allocator>::vector(InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		size_type _distance = last - first;
		auto p = allocator_type::allocate(_distance);
		start = p;
		finish = start + _distance;
		end_of_storage = finish;
		for (int i = 0; i != _distance; ++i) {
			allocator_type::construct(p++, *first++);
		}
	}

	// 委托构造
	template<class T, class Allocator>
	vector<T, Allocator>::vector(vector& other) : vector(other.begin(), other.end()){}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(vector&& other) noexcept
		: start(other.start), finish(other.finish), end_of_storage(other.end_of_storage) {
		other.start = other.finish = other.end_of_storage = nullptr;
	}

	// 委托构造
	template<class T, class Allocator>
	vector<T, Allocator>::vector(std::initializer_list<value_type> init) : vector(init.begin(), init.end()) {}

	template<class T, class Allocator>
	vector<T, Allocator>::~vector() {
		clear();
		// shrink_to_fit();
		allocator_type::deallocate(start, size());
	}


	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
		insert(begin(), other.begin(), other.end());
		return *this;
	}

	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) noexcept {
		start = other.start;
		finish = other.finish;
		end_of_storage = other.end_of_storage;
		other.start = other.finish = other.end_of_storage = nullptr;
		return *this;
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type pos) {
		return *(begin() + pos);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type pos) const {
		return  *(begin() + pos);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type pos) {
		if (pos >= size())
			throw std::out_of_range("out of range.");
		return operator[](pos);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type pos) const {
		if (pos >= size())
			throw std::out_of_range("out of range.");
		return operator[](pos);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity())
			return;

		auto _new_start = allocator_type::allocate(new_cap);
		auto _new_finish = std::uninitialized_copy(start, finish, _new_start);

		_Dest_All(start, finish);

		start = _new_start;
		finish = _new_finish;
		end_of_storage = start + new_cap;
	}


	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::_Insert_Aux(iterator pos, size_type count, const_reference value) {
		if (end_of_storage - finish >= count) {
			// pos后的个数大于count，此时pos后有的直接copy assignment，有的需要uninitialized_copy(copy ctor)
			if (finish - pos > count) {
				// TODO
				// 以后用自己的 <memory> 或 <algorithm>替换

				// 1. 移动pos后的倒数count个空间(old)
				std::uninitialized_copy(finish - count, finish, finish);	// copy ctor

				// 2. 移动pos后的剩余部分	(old)
				std::copy_backward(pos, finish - count, finish);			// 第三个参数是末位

				// 3. "copy assignemnt" count个空间 (new)
				std::fill_n(pos, count, value);

			}
			// pos后的个数小于等于count，此时pos后的直接uninitialized_copy
			else {

				// 1. 移动pos后的原空间(old)
				std::uninitialized_copy(pos, finish, pos + count);

				// 2. "copy assignment" count的前finish - pos个(new)
				std::fill_n(pos, finish - pos, value);

				// 3. "copy ctor" count剩余的部分(new)
				std::uninitialized_fill_n(finish, count - (finish - pos), value);
				
			}
			finish += count;
			return pos;
		}
		else {
			// 空间增长
			size_type _new_size = _Calc_Growth(size() + count);

			// 重新申请空间
			auto _new_start = allocator_type::allocate(_new_size);

			// 原空间pos前的元素copy到新空间
			auto _temp_start = std::uninitialized_copy(start, pos, _new_start);

			// 在pos构造count个value
			auto _temp_end = _Ctor_Range(_temp_start, count, value);

			// 把原空间pos后的元素copy过来
			auto _new_finish = std::uninitialized_copy(pos, finish, _temp_end);

			// 释放原空间
			_Dest_All(start, finish);

			// 更新数据
			start = _new_start;
			finish = _new_finish;
			end_of_storage = start + _new_size;

			return _temp_start;
		}
	}

	template<class T, class Allocator>
	template<class InputIt>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::_Insert_Aux(iterator pos, InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		// 和上面的重载思路一样
		auto _size = last - first;
		if (end_of_storage - finish >= last - first) {

			if (finish - pos > _size) {
				std::uninitialized_copy(finish - _size, finish, finish);
				std::copy_backward(pos, finish - _size, finish);
				std::copy(first, last, pos);
			}
			else {
				std::uninitialized_copy(pos, finish, pos + _size);
				std::copy(first, first + (finish - pos), pos);
				std::uninitialized_copy(first + (finish - pos), last, finish);
			}
			finish += _size;
			return pos;
		}
		else {
			size_type _new_size = _Calc_Growth(size() + _size);
			iterator _new_start = allocator_type::allocate(_new_size);
			
			auto _temp_start = std::uninitialized_copy(start, pos, _new_start);
			auto _temp_end = std::uninitialized_copy(first, last, _temp_start);
			auto _new_finish = std::uninitialized_copy(pos, finish, _temp_end);

			_Dest_All(start, finish);

			start = _new_start;
			finish = _new_finish;
			end_of_storage = start + _new_size;

			return _temp_start;
		}
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::clear() noexcept {
		_Dtor_Range(start, finish);
		finish = start;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::shrink_to_fit() {
		if (end_of_storage == finish)
			return;

		auto _new_start = allocator_type::allocate(size());

		auto _new_finish = std::uninitialized_copy(start, finish, _new_start);
		
		_Dest_All(start, finish);

		start = _new_start;
		finish = _new_finish;
		end_of_storage = finish;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::resize(size_type count, const_reference value) {
		auto _size = size();
		if (count < _size) {
			while (count != _size) {
				pop_back();
				--_size;
			}
		}
		else {
			insert(end(), count, value);
			/*while (count != _size) {
				push_back(value);
				++_size;
			}*/
		}
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(iterator pos, const_reference value) {
		return _Insert_Aux(pos, 1, value);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::insert(iterator pos, size_type count, const_reference value) {
		_Insert_Aux(pos, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void vector<T, Allocator>::insert(iterator pos, InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		_Insert_Aux(pos, first, last);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> ilist) {
		return _Insert_Aux(const_cast<iterator>(pos), ilist.begin(), ilist.end());
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator pos) {
		return erase(pos, pos + 1);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(iterator first, iterator last) {
		auto _after_last = finish - last;
		auto _erase_len = last - first;
		// _Dtor_Range(first, last);
		for (; _after_last != 0; --_after_last) {
			auto temp = last - _erase_len;
			*temp = *last++;
		}
		finish -= _erase_len;
		return first;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(const_reference value) {
		insert(end(), value);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(value_type&& value) {
		insert(end(), value);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::pop_back() {
		allocator_type::destroy(--finish);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::swap(vector& other) noexcept {
		std::swap(start, other.start);
		std::swap(finish, other.finish);
		std::swap(end_of_storage, other.end_of_storage);
	}

}


#endif // !MIKU_VECTOR_IMPL_H__

