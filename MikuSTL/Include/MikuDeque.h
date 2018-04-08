#ifndef MIKU_DEQUE_H__
#define MIKU_DEQUE_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"

namespace Miku {

	namespace Internal {

		template<class T>
		class _Deque_Iterator {

		public:
			using iterator_category = typename Miku::bidirectional_iterator_tag;
			using value_type = T;
			using pointer = T * ;
			using reference = T & ;
			using size_type = typename std::size_t;
			using difference_type = typename std::ptrdiff_t;

			using map_pointer = pointer * ;

		
			pointer first;		// buffer的头
			pointer last;		// buffer的尾
			pointer cur;		// 当前元素在buffer的位置

			map_pointer node;	// buffer在"中控器"的位置

		
			_Deque_Iterator() : first(nullptr), last(nullptr), cur(nullptr), node(nullptr) {}
			_Deque_Iterator(size_type _index, pointer _cur, map_pointer _node) :
				first(*_node), last(first + _index), cur(_cur), node(_node) {}
			_Deque_Iterator(const _Deque_Iterator& other) :
				first(other.first), last(other.last), cur(other.cur), node(other.node) {}


			reference operator*() const { return *cur; }
			pointer operator->() const { return cur; }

		};

	}

	template<class T, class Allocator = Miku::allocator<T>>
	class deque {

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = typename std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;

		using map_pointer = pointer * ;

		using iterator = Internal::_Deque_Iterator<T>;

	private:
		iterator start;
		iterator finish;
		map_pointer map;
		size_type mapSize;

	public:
		deque();
		explicit deque(size_type, const_reference = value_type());
		template<class InputIt>
		deque(InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		deque(const deque&);
		deque(const deque&&);
		deque(std::initializer_list<value_type>);
		// ~deque();

	private:

	public:
		iterator begin() { return start; }

		iterator end() { return finish; }

		size_type size() const noexcept { return end() - begin(); }

		bool empty() const noexcept { return begin() == end(); }
	};
}

#include "MikuDeque.impl.h"

#endif // !MIKU_DEQUE_H__
