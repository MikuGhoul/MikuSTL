#ifndef TINYALLOCTRAITS_H__
#define TINYALLOCTRAITS_H__

namespace Miku {

	template<class Alloc>
	class allocator_traits {

	public:
		using allocator_type = Alloc;
		using value_type = Alloc::value_type;
		using pointer = Alloc::pointer;
		using const_pointer = Alloc::const_pointer;
		// using void_pointer = Alloc::void_pointer;
		// using const_void_pointer = Alloc::const_void_pointer;
		using difference_type = Alloc::difference_type;
		using size_type = Alloc::size_type;

		using rebind_alloc<T> = Alloc::rebind<T>::other;


	};
}


#endif // !TINYALLOCTRAITS_H__
