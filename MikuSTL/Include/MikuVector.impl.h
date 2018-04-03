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

	/*template<class T, class Allocator>
	vector<T, Allocator>::~vector() {

	}*/

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

}


#endif // !MIKU_VECTOR_IMPL_H__

