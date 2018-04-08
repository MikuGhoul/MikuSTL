#ifndef MIKU_VECTOR_H__
#define MIKU_VECTOR_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"
#include <memory>
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
		~vector();

	private:
		pointer _New_Node();
		pointer _New_Node(size_type, const_reference);
		iterator _Ctor_Range(iterator, size_type, const_reference);
		void _Dtor_Range(iterator, iterator);
		void _Dest_All(iterator, iterator);
		size_type _Calc_Growth(size_type);
		iterator _Insert_Aux(iterator, size_type, const_reference);
		template<class InputIt>
		iterator _Insert_Aux(iterator, InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		


	public:
		vector& operator=(const vector&);
		vector& operator=(vector&&) noexcept;

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

		// 增加 end_of_storage - finish
		void reserve(size_type);

		// 析构 finish - start. end_of_storage不变
		void clear() noexcept;

		// 使 end_of_storage 减少到 finish
		void shrink_to_fit();

		// 第一个参数大于size(), 则以第二个参数的值扩充
		// 第一个参数小于size(), 则析构多余的部分
		void resize(size_type, const_reference = value_type());

		iterator insert(iterator, const_reference);
		void insert(iterator, size_type, const_reference);
		template<class InputIt>
		void insert(iterator, InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		iterator insert(const_iterator, std::initializer_list<value_type>);

		iterator erase(iterator);
		iterator erase(iterator, iterator);

		void push_back(const_reference);
		void push_back(value_type&&);

		void pop_back();

		void swap(vector&) noexcept;
	};

	template<class T, class Allocator>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto l_beg = lhs.begin();
		auto r_beg = rhs.begin();
		auto l_end = lhs.end();
		for (; l_beg != l_end; ++l_beg, ++r_beg) {
			if (*l_beg != *r_beg)
				return false;
		}
		return true;
	}

	template<class T, class Allocator>
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		return (!(lhs == rhs));
	}
	
}

#include "MikuVector.impl.h"

#endif // !MIKU_VECTOR_H__