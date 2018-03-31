#ifndef TINYALLOCTRAITS_H__
#define TINYALLOCTRAITS_H__

#include "MikuAllocator.h"
#include <utility>

namespace Miku {

	template<class Alloc>
	class allocator_traits {

	public:
		using allocator_type = Alloc;
		using value_type = typename Alloc::value_type;
		using pointer = typename Alloc::pointer;
		using const_pointer = typename Alloc::const_pointer;
		// using void_pointer = Alloc::void_pointer;
		// using const_void_pointer = Alloc::const_void_pointer;
		using difference_type = typename Alloc::difference_type;
		using size_type = typename Alloc::size_type;

		
		// alias template
		/*template<typename T>
		using rebind_alloc = typename Alloc::rebind<T>::other;*/

		// constructor && destructor
		/*allocator_traits() = default;
		~allocator_traits() = default;*/


		// static function in template class
		static pointer allocate(Alloc& a, size_type n) {
			return a.allocate(n);
		}

		static void deallocate(Alloc& a, pointer p, size_type n) {
			a.deallocate(p, n);
		}



		template<class T, class... Args>
		static void construct(Alloc& a, T* p, Args&&... args) {
			a.construct(p, std::forward<Args>(args)...);
		}



	};


}


#endif // !TINYALLOCTRAITS_H__
