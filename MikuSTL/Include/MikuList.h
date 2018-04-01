#ifndef TINYLIST_H__
#define TINYLIST_H__

#include <cstddef>
#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"
#include <iterator>
#include <type_traits>
#include <initializer_list>

namespace Miku {

	namespace Internal {

		template<class T>
		struct _List_Node {
			using list_pointer = _List_Node<T>*;

			list_pointer prev;
			list_pointer next;
			T data;

			_List_Node(list_pointer p, list_pointer n, T d) : prev(p), next(n), data(d) {}
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
			using link_type = _List_Node<T> *;
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

		// TODO
		// 看了MSVC的实现是针对const_iterator有个特化类，也不算特化，就是单独一个类
		// 不然List是const的时候进行迭代器操作，我也没想出来有什么好办法可以用non-const_iterator操作
		template<class T>
		class _List_Const_Iterator {
		public:

			template<class T>
			friend bool operator==(const _List_Const_Iterator<T>& lhs, const _List_Const_Iterator<T>& rhs);
			template<class T>
			friend bool operator!=(const _List_Const_Iterator<T>& lhs, const _List_Const_Iterator<T>& rhs);

			using iterator_category = typename Miku::bidirectional_iterator_tag;
			using value_type = T;
			using pointer = const T * ;
			using reference = const T & ;
			using difference_type = typename std::ptrdiff_t;
			using link_type = const _List_Node<T> *;
			using self = _List_Const_Iterator<T>;

			link_type node;

			_List_Const_Iterator() = default;
			_List_Const_Iterator(link_type _Node) {
				node = _Node;
			}
			~_List_Const_Iterator() = default;

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
		bool operator==(const _List_Const_Iterator<T>& lhs, const _List_Const_Iterator<T>& rhs) {
			return lhs.node == rhs.node;
		}

		template<class T>
		bool operator!=(const _List_Const_Iterator<T>& lhs, const _List_Const_Iterator<T>& rhs) {
			return lhs.node != rhs.node;
		}
	}
	
	// 与SGI的list的一样，是环状双向链表
	template<class T, class Allocator = Miku::allocator<Internal::_List_Node<T>>>
	class list {

	private:
		using list_node = Internal::_List_Node<T>;
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

		using iterator = Internal::_List_Iterator<T>;
		using const_iterator = Internal::_List_Const_Iterator<T>;

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
		list(list&&);
		list(std::initializer_list<value_type>);
		// ~list();

	private:
		link_type _New_Node();
		link_type _New_Node(const_reference);
		// 构造空链表，只有一个node，prev与next指向自己
		void _Void_Init();
		void _Destroy(link_type);

	public:
		iterator begin() noexcept { return node->next; }
		const_iterator begin() const noexcept { return node->next; }
		const_iterator cbegin() const noexcept { return node->next; }

		iterator end() noexcept { return node; }
		const_iterator end() const noexcept { return node; }
		const_iterator cend() const noexcept { return node; }
		// TODO
		// rbegin/rend, 再写个iterator就可以了

		size_type size() noexcept;

		bool empty() const noexcept { return node->next == node; }

		void push_back(const_reference);
		void push_back(value_type&& value);

		void push_front(const_reference);

		void pop_back();

		void pop_front();

		void clear() noexcept;

		iterator insert(iterator, const_reference);
		void insert(iterator, size_type, const_reference);
		template<class InputIt>
		void insert(iterator, InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);

		// TODO
		/*template<class... Args>
		iterator emplace(iterator, Args&&...);*/

		iterator erase(iterator);
		// erase [first, last)
		iterator erase(iterator, iterator);
		iterator erase(const_iterator);
		iterator erase(const_iterator, const_iterator);

		void resize(size_type, const_reference = value_type());

		void swap(list&) noexcept;

		/*void merge(list&);
		template<class Compare>
		void merge(list&, Compare);*/

		/*void sort();
		template<class Compare>
		void sort(Compare comp);*/
	};
	
}


#include "MikuList.impl.h"

#endif // !TINYLIST_H__

