#ifndef TINYITERATOR_H__
#define TINYITERATOR_H__

namespace Miku {

	// 用于迭代器分类的tag，分别对应后面的五个迭代器
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template<class T>
	class InputIterator {
		using iterator_category = input_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;
	};

	template<class T>
	class OutputIterator {
		using iterator_category = output_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;
	};

	template<class T>
	class ForwardIterator {
		using iterator_category = forward_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;
	};

	template<class T>
	class BidirectionalIterator {
		using iterator_category = bidirectional_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;
	};

	template<class T>
	class RandomAccessIterator {
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = typename std::ptrdiff_t;
		using pointer = value_type * ;
		using reference = value_type & ;
	};

	// iterator的traits
	template<class T>
	class Iterator_Traits {
		using iterator_category = typename T::iterator_category;
		using value_type = typename T::value_type;
		using difference_type = typename T::difference_type;
		using pointer = typename T::pointer;
		using reference = typename T::reference;
	};
	
	// iterator的traits 偏特化
	template<class T>
	class Iterator_Traits<T*> {
		using iterator_category = random_access_iterator_tag;
		// TODO
	};
	template<class T>
	class Iterator_Traits<const T*> {
		using iterator_category = random_access_iterator_tag;
		// TODO
	};
}


#endif // !TINYITERATOR_H__
