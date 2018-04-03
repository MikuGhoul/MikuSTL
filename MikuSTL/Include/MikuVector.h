#ifndef MIKU_VECTOR_H__
#define MIKU_VECTOR_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"
#include <stdexcept>


namespace Miku {

	template<class T, class Allocator = Miku::allocator<T>>
	class vector {

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type &;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;

		// vector的iterator用指针就可以了(和list对比)，以后algorithm用的时候，通过allocator_traits特化一个指针的版本
		using iterator = T * ;
		using const_iterator = const T * ;

	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;

	public:
		vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
		vector(size_type, const_reference = value_type());
		template<class InputIt>
		// 使用SFINAE，和List一样
		vector(InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		vector(vector&);
		vector(vector&&) noexcept;
		vector(std::initializer_list<value_type>);
		// ~vector();

	private:
		pointer _New_Node();
		pointer _New_Node(size_type, const_reference);

	public:
		reference operator[](size_type);
		const_reference operator[](size_type) const;

		reference at(size_type);
		const_reference at(size_type) const;

		reference front() { return *start; }
		const_reference front() const { return *start; }

		reference back() { return *(finish - 1); }
		const_reference back() const { return *(finish - 1); }

		pointer data() noexcept { return start; }
		const_pointer data() const noexcept { return start; }

		iterator begin() noexcept { return start; }
		const_iterator begin() const noexcept { return start; }
		const_iterator cbegin() const noexcept { return start; }

		iterator end() noexcept { return finish; }
		const_iterator end() const noexcept { return finish; }
		const_iterator cend() const noexcept { return finish; }

		bool empty() const noexcept { return start == finish; }

		size_type size() const noexcept { return finish - start; }

		size_type capacity() const noexcept { return end_of_storage - start; }

	};
	
}

#include "MikuVector.impl.h"

#endif // !MIKU_VECTOR_H__