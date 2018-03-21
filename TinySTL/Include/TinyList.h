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
		using iterator_category = Miku::bidirectional_iterator_tag;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;
		using difference_type = std::ptrdiff_t;
		using link_type = _List_Node<T> * ;
		using self = _List_Iterator<T>;
		
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


	template<class T, class Allocator = Miku::allocator>
	class list {

	private:
		using list_node = _List_Node<T>;
		using link_type = list_node * ;

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = Miku::allocator_traits<Allocator>::const_pointer;

		using iterator = _List_Iterator<T>;

	private:
		link_type node;
	
	};
}


#endif // !TINYLIST_H__

