// #include "TinyList.h"

#ifndef TINYLIST_IMPL_H__
#define TINYLIST_IMPL_H__

#include "TinyList.h"
	
namespace Miku {

	template<class T, class Allocator>
	inline void list<T, Allocator>::_init_Iter() {
		head = node;
		tail = node;
	}

	template<class T, class Allocator>
	inline list<T, Allocator>::list() {

		Miku::allocator<list_node> a;
		// auto p = a.allocate(1);
		// a.construct(p, 0);
		node = a.allocate(1);
		// a.construct(node, T());

		_init_Iter();

		link_type _nodeNull = a.allocate(1);
		_nodeNull->data = NULL;
		_nodeNull->prev = node;
		_nodeNull->next = nullptr;
		node->next = _nodeNull;
	}

	/*template<class T, class Allocator>
	inline list<T, Allocator>::list(typename size_type count, typename const value_type & value) {
		Miku::allocator<list_node> a;
		node = a.allocate(count);
		 _init_Iter();

		link_type temp = node;
		while (temp) {
			temp->data = value;
			temp = temp->next;
			if (temp->next)
				++tail;
		}
	}*/


	/*template<class T, class Allocator>
	size_type list<T, Allocator>::size() const {
		return 1;
	}*/
	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::size_type Miku::list<T, Allocator>::size() {
		size_type _size = 0;
		//iterator i = begin();
		//std::cout << *i << std::endl;
		//if (i != end()) {
		//	// return 1000;
		//	std::cout << "i != end()" << std::endl;
		//}
		//++i;
		//std::cout << *i << std::endl;
		/*if (i == end()) {
			std::cout << "done" << std::endl;
		}*/
		// ++i;
		// std::cout << *i << std::endl;
		for (iterator i = begin(); i != end(); ++i) {
			++_size;
		}
		return _size;
	}
}
#endif // !TINYLIST_IMPL_H__
