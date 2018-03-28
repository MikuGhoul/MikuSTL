// #include "TinyList.h"

#ifndef TINYLIST_IMPL_H__
#define TINYLIST_IMPL_H__

#include "TinyList.h"
	
namespace Miku {

	template<class T, class Allocator>
	inline void list<T, Allocator>::_init_Iter() {
		head.node = node;
		tail.node = node;
	}

	template<class T, class Allocator>
	inline void list<T, Allocator>::_Construct_Proxy(size_type count, const_reference value) {
		Miku::allocator<list_node> _altor;
		node = _altor.allocate(1);
		link_type _nodeNull = _altor.allocate(1);

		_nodeNull->data = NULL;
		_nodeNull->prev = node;
		_nodeNull->next = nullptr;
		node->next = _nodeNull;
		node->prev = nullptr;
		node->data = value;
		_init_Iter();

		if (count == 1)
			return;

		link_type temp;
		// Î²ºó²åÈë
		for (int i = 1; i != count; ++i) {
			temp = _altor.allocate(1);
			temp->data = value;

			_nodeNull->prev->next = temp;
			temp->prev = _nodeNull->prev;

			temp->next = _nodeNull;
			_nodeNull->prev = temp;

			++tail;
		}
	}

	template<class T, class Allocator>
	inline list<T, Allocator>::list() {
		_Construct_Proxy(1, NULL);
	}

	template<class T, class Allocator>
	inline list<T, Allocator>::list(size_type count, const_reference value) {
		_Construct_Proxy(count, value);
	}

	/*template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, std::input_iterator_tag) {

	}*/

	template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value>::type *) {
		
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::size_type Miku::list<T, Allocator>::size() {
		int _size = 0;
		for (iterator i = begin(); i != end(); ++i) {
			++_size;
		}
		return _size;
	}
}
#endif // !TINYLIST_IMPL_H__
