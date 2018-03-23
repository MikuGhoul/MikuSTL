#ifndef TINYVECTOR_H__
#define TINYVECTOR_H__

#include "TinyAllocator.h"
#include "TinyAllocTraits.h"
#include "TinyIterator.h"

namespace Miku {
	template<class T, class Allocator = Miku::allocator<T>>
	class vector {
		using value_type = T;
		using allocator_type = typename Allocator;
		using size_type = typename std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference = typename value_type & ;
		using const_reference = typename const value_type & ;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;
		// using iterator = 

	};
}

#endif // !TINYVECTOR_H__

