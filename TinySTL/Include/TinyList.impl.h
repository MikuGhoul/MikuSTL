// #include "TinyList.h"

#ifndef TINYLIST_IMPL_H__
#define TINYLIST_IMPL_H__

#include "TinyList.h"
	
namespace Miku {

	template<class T, class Allocator>
	typename list<T, Allocator>::link_type list<T, Allocator>::_New_Node() {
		return allocator_type::allocate();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::link_type list<T, Allocator>::_New_Node(const_reference value) {
		auto p = _New_Node();
		Miku::allocator<value_type>::construct(&p->data, value);
		return p;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::_Void_Init() {
		node = _New_Node();
		node->next = node;
		node->prev = node;
	}

	template<class T, class Allocator>
	list<T, Allocator>::list() {
		_Void_Init();
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count, const_reference value) {
		_Void_Init();
		insert(begin(), count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, 
		typename std::enable_if<!std::is_integral<InputIt>::value>::type *) {
		_Void_Init();
		insert(begin(), first, last);
	}
	/*template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, 
		typename std::enable_if<std::is_same<typename Iterator_Traits<InputIt>::iterator_category, bidirectional_iterator_tag>::value>::type *) {
		std::cout << "what the fuck???" << std::endl;
	}*/

	template<class T, class Allocator>
	list<T, Allocator>::list(list& other) {
		_Void_Init();
		insert(begin(), other.begin(), other.end());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(std::initializer_list<value_type> init) {
		_Void_Init();
		insert(begin(), init.begin(), init.end());
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::size_type Miku::list<T, Allocator>::size() {
		int _size = 0;
		for (iterator i = begin(); i != end(); ++i) {
			++_size;
		}
		return _size;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(const_reference value) {
		insert(end(), value);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(const_reference value) {
		insert(begin(), value);
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::insert(iterator pos, const_reference value) {
		link_type p = _New_Node(value);
		pos.node->prev->next = p;
		p->prev = pos.node->prev;
		p->next = pos.node;
		pos.node->prev = p;
		return p;
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::insert(iterator pos, size_type count, const_reference value) {
		for (int i = 0; i != count; ++i)
			insert(pos, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void Miku::list<T, Allocator>::insert(iterator pos, InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		// 插入在pos前，而且pos不更改，所以可以直接调用insert(iterator, const_reference)
		for (; first != last; ++first)
			insert(pos, *first);
	}
}
#endif // !TINYLIST_IMPL_H__
