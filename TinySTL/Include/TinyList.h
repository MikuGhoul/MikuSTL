#ifndef TINYLIST_H__
#define TINYLIST_H__

#include <cstddef>
#include "TinyAllocator.h"
#include "TinyAllocTraits.h"
#include "TinyIterator.h"
#include <iterator>
#include <type_traits>
#include <initializer_list>

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
	public:

		template<class T>
		friend bool operator==(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);
		template<class T>
		friend bool operator!=(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs);

		using iterator_category = typename Miku::bidirectional_iterator_tag;
		using value_type = T;
		using pointer = T * ;
		using reference = T & ;
		using difference_type = typename std::ptrdiff_t;
		using link_type = _List_Node<T> * ;
		using self = _List_Iterator<T>;
		
		link_type node;

		_List_Iterator() = default;
		_List_Iterator(link_type _Node) {
			node = _Node;
		}
		~_List_Iterator() = default;

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
		return lhs.node == rhs.node;
	}

	template<class T>
	bool operator!=(const _List_Iterator<T>& lhs, const _List_Iterator<T>& rhs) {
		return lhs.node != rhs.node;
	}

	// 与SGI的list的一样，是环状双向链表
	template<class T, class Allocator = Miku::allocator<_List_Node<T>>>
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
		// list的头节点，不存放数据
		link_type node;

	public:
		list();
		// TODO
		// SFINAE解决重载决议冲突问题，但我不知道为什么第三种写法不会触发SFINAE，以及第一种会traits失败
		list(size_type, const_reference = value_type());
		template<class InputIt>
		list(InputIt, InputIt,
			// typename std::enable_if<std::is_same<typename Iterator_Traits<InputIt>::iterator_category, bidirectional_iterator_tag>::value>::type* = nullptr);
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
			// std::input_iterator_tag = typename std::iterator_traits<InputIt>::iterator_category{});
			// input_iterator_tag = typename Iterator_Traits<InputIt>::iterator_category{});
		list(list&);
		list(std::initializer_list<value_type>);

	private:
		link_type _New_Node();
		link_type _New_Node(const_reference);
		// 构造空链表，只有一个node，prev与next指向自己
		void _Void_Init();

	public:
		iterator begin() { return node->next; }
		iterator end() { return node; }

		size_type size();
		// TODO
		// void push_back( T&& value );
		void push_back(const_reference);
		void push_front(const_reference);

		iterator insert(iterator, const_reference);
		// TODO 
		// const_iterator
		void insert(iterator, size_type, const_reference);
		template<class InputIt>
		void insert(iterator, InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
	};
	
}


#include "TinyList.impl.h"

#endif // !TINYLIST_H__

