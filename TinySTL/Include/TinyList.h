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
		T data;
	};

	template<class T>
	class _List_Iterator {
		template<class U>
		friend bool operator==(const _List_Iterator<U>& lhs, const _List_Iterator<U>& rhs);
		template<class U>
		friend bool operator!=(const _List_Iterator<U>& lhs, const _List_Iterator<U>& rhs);

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
		_List_Iterator() = default;
		~_List_Iterator() = default;
		_List_Iterator operator=(link_type _node) {
			node = _node;
			return *this;
		}

	public:
		reference operator*() const {
			return node->data;
		}
		pointer operator->() const {
			return &(operator*());
		}
		self& operator++() {
			node = node->next;
			return *this;
		}
		self operator++(int) {
			link_type temp = node;
			node = node->next;
			return temp;
		}

	};
	
	template<class T>
	bool operator==(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs) {
		/*if (lhs.node == rhs.node)
			return true;
		return false;*/
		std::cout << " == " << std::endl;
		/*if (!lhs.node  || !rhs.node)
			return false;*/
		if (lhs.node->data == rhs.node->data &&
			lhs.node->next == rhs.node->next &&
			lhs.node->prev == rhs.node->prev)
			return true;
		return false;
	}

	template<class T>
	bool operator!=(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs) {
		std::cout << " != " << std::endl;
		if (lhs == rhs)
			return false;
		return true;
	}


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
		iterator head;
		iterator tail;

	public:
		list();
		list(size_type count, const value_type& value = value_type());
		template<class InputIt>
		list(InputIt first, InputIt last);
		list(const list& other);
		list(std::initializer_list<value_type> init);

	private:
		void _init_Iter();

	public:
		iterator begin() { return head; }
		iterator end() {
			iterator temp = tail;
			return ++temp;
		}

		// size_type size() const { return std::distance(head, ++tail); }
		size_type size();
	};
	
}


#include "TinyList.impl.h"

#endif // !TINYLIST_H__

