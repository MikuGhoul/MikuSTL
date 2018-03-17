#ifndef TINY_ALLOCATOR_H_
#define TINY_ALLOCATOR_H_

namespace Miku {

	template<typename T>
	class allocator {

	public:
		// typedef
		using value_type = T;
		using pointer = value_type* ;
		using const_pointer = const value_type* ;
		using reference = value_type& ;
		using const_reference = const value_type& ;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;

		template<typename U>
		class rebind {
			using other = allocator<U>;
		};

		// constructor
		allocator() = default;
		allocator(const allocator& other) = default;
		template<typename U>
		allocator(const allocator<U>& other);
		
		// destructor
		~allocator() = default;


		// defined in class ,so default inline
		pointer allocate(size_type n) {
			return static_cast<pointer>(::operator new(n * sizeof(value_type)));
		}

		// all right, I don't know what n can do
		void deallocate(pointer p, size_type n) {
			::operator delete(p);
		}

		// placement new
		void construct(pointer p, const_reference val) {
			new ((void*)p) value_type(val);
		}

		/*template<class U, class... Args>
		void  construct(U* p, Args&&... args) {
			new ((void*)p) U(std::forward<Args>(args)...);
		}*/

		void destroy(pointer p) {
			p->~value_type();
		}


	};


	template<typename T1, typename T2>
	bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) {
		return true;
	}

	template<typename T1, typename T2>
	bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) {
		return false;
	}



}


#endif // !TINY_ALLOCATOR_H_
