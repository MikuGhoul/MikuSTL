#ifndef TINYLIST_H__
#define TINYLIST_H__

 #include <cstddef>
 #include "TinyAllocator.h"
 #include "TinyAllocTraits.h"
 #include "TinyIterator.h"
 #include <iterator>
#include <type_traits>

namespace Miku {

	// 前置声明，一对一友好关系时候用。这里的实现用的是一对多关系
	/*template<class T, class Allocator = Miku::allocator<T>>
	class list;
	template<class T>
	class _List_Iterator;
	template<class T>
	bool operator==(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);
	template<class T>
	bool operator!=(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);*/


	template<class T>
	struct _List_Node {
		using list_pointer = _List_Node<T>*;
		list_pointer prev;
		list_pointer next;
		T data;
	};

	template<class T>
	class _List_Iterator {

		template<class T, class Allocator>
		friend class list;

		template<class T>
		friend bool operator==(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);
		template<class T>
		friend bool operator!=(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);

	public:
		using iterator_category = typename Miku::bidirectional_iterator_tag;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;
		using difference_type = typename std::ptrdiff_t;
		using link_type = _List_Node<T> * ;
		using self = _List_Iterator<T>;
		
	private:
		link_type node;
	public:
		_List_Iterator() = default;
		~_List_Iterator() = default;
		/*_List_Iterator operator=(link_type _node) {
			node = _node;
			return *this;
		}*/

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
			self temp = *this;
			++*this;
			return temp;

		}
		self& operator--() {
			node = node->prev;
			return *this;
		}
		self operator--(int) {
			self temp = *this;
			--*this;
			return temp;
		}
	};
	
	template<class T>
	bool operator==(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs) {
		/*if (lhs.node == rhs.node)
			return true;
		return false;*/
		// std::cout << " == " << std::endl;
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
		// std::cout << " != " << std::endl;
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
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference =  value_type&;
		using const_reference =  const value_type&;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;

		using iterator = _List_Iterator<T>;

	private:
		link_type node;
		iterator head;
		iterator tail;

	public:
		list();
		// TODO
		// SFINAE解决重载决议冲突问题，但我不知道为什么第二种写法不会触发SFINAE
		list(size_type count, const_reference value = value_type());
		template<class InputIt>
		list(InputIt first, InputIt last,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
			// std::input_iterator_tag = typename std::iterator_traits<InputIt>::iterator_category{});
			// input_iterator_tag = typename Iterator_Traits<InputIt>::iterator_category{});

		list(const list& other);
		list(std::initializer_list<value_type> init);

	private:
		void _init_Iter();
		// not include the last `NULL` node
		void _Construct_Proxy(size_type, const_reference value);

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

