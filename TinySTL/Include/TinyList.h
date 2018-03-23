#ifndef TINYLIST_H__
#define TINYLIST_H__

 #include "TinyAllocator.h"
 #include "TinyAllocTraits.h"
 #include "TinyIterator.h"

namespace Miku {

	template<class T>
	struct _List_Node {
		using list_pointer = _List_Node<T>*;
		list_pointer prev;
		list_pointer next;
		T date;
	};

	template<class T>
	class _List_Iterator {

	public:
		using iterator_category = typename Miku::bidirectional_iterator_tag;
		using value_type = typename T;
		using pointer = typename T * ;
		using reference = typename T & ;
		using difference_type = typename std::ptrdiff_t;
		using link_type = typename _List_Node<T> * ;
		using self = typename _List_Iterator<T>;
		
	private:
		link_type node;

	public:
		reference operator*() const {
			return node->date;
		}
		pointer operator->() const {
			return &(operator*());
		}
		self& operator++() const {
			node = node->next;
			return *this;
		}
		self operator++(int) const {
			link_type temp = node;
			node = node->next;
			return temp;
		}

	};


	template<class T, class Allocator = Miku::allocator<T>>
	class list {

	private:
		using list_node = _List_Node<T>;
		using link_type = list_node * ;

	public:
		using value_type = T;
		using allocator_type = typename Allocator;
		using size_type = typename std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference = typename value_type&;
		using const_reference = typename const value_type&;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;

		using iterator = _List_Iterator<T>;

	private:
		link_type node;

	public:
		list();
		// list(size_type count, const T& value = T(), const allocator_type& alloc = Allocator());

	private:

	};
	

}
//namespace Miku {
//	template<class T, class Allocator>
//	inline list<T, Allocator>::list() {
//
//	}
//}

#include "TinyList.impl.h"

#endif // !TINYLIST_H__

