#ifndef MIKU_DEQUE_IMPL_H__
#define MIKU_DEQUE_IMPL_H__

namespace Miku {

	namespace Internal {

		/*template<class T>
		_Deque_Iterator<T>::_Deque_Iterator() {

		}*/
	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque() : start(), finish(), map(nullptr), mapSize(0){

	}

	template<class T, class Allocator>
	explicit deque<T, Allocator>::deque(size_type count, const_reference value) {

	}

	template<class T, class Allocator>
	template<class InputIt>
	deque<T, Allocator>::deque(InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque& other) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(const deque&& ohter) {

	}

	template<class T, class Allocator>
	deque<T, Allocator>::deque(std::initializer_list<value_type> init) {

	}

}

#endif // !MIKU_DEQUE_IMPL_H__
