#ifndef TINYITERATOR_H__
#define TINYITERATOR_H__

namespace Miku {

	struct input_iterator_tag {

	};

	struct output_iterator_tag {

	};

	struct forward_iterator_tag : public input_iterator_tag, public output_iterator_tag {

	};

	struct bidirectional_iterator_tag : public forward_iterator_tag{

	};

	struct random_access_iterator_tag : public bidirectional_iterator_tag {

	};

	template<class T>
	class InputIterator {

	};

	template<class T>
	class OutputIterator {

	};

	template<class T>
	class RandomAccessIterator {

	};
	
}


#endif // !TINYITERATOR_H__
