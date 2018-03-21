#ifndef TINYLIST_H__
#define TINYLIST_H__

#include "TinyAllocator.h"
#include "TinyAllocTraits.h"

namespace Miku {
	template<class T, class Allocator = Miku::allocator>
	class list {

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = Miku::allocator_traits<Allocator>::const_pointer;
		

	
	};
}


#endif // !TINYLIST_H__

