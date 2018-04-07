#ifndef MIKU_ARRAY_H__
#define MIKU_ARRAY_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"

namespace Miku {

	template<class T, std::size_t _Size>
	class array{

	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type &;
		using pointer = value_type * ;
		using const_pointer = const value_type * ;

		using iterator = T * ;
		using const_iterator = const T * ;

	
		value_type elems[_Size ? _Size : 1];

	public:
		// ctor, dto和copy assignment会隐式声明
		constexpr reference at(size_type pos) { return &elems[pos]; }
		constexpr const_reference at(size_type pos) const { return &elems[pos]; }

		constexpr reference operator[](size_type pos) { return &elems[pos]; }
		constexpr const_reference operator[](size_type pos) const { return &elems[pos]; }

		constexpr reference front() { return *begin(); }
		constexpr const_reference front() const { return *begin(); }

		constexpr reference back() { return *(end() - 1); }
		constexpr const_reference back() const { return *(end() - 1); }

		constexpr pointer data() noexcept { return &elems[0]; }
		constexpr const_pointer data() const noexcept { return &elems[0]; }

		constexpr iterator begin() noexcept { return &elems[0]; }
		constexpr const_iterator begin() const noexcept { return &elems[0]; }
		constexpr const_iterator cbegin() const noexcept { return &elems[0]; }

		constexpr iterator end() noexcept { return &elems[_Size]; }
		constexpr const_iterator end() const noexcept { return &elems[_Size]; }
		constexpr const_iterator cend() const noexcept { return &elems[_Size]; }

		constexpr bool empty() const noexcept { return begin() == end(); }
		constexpr size_type size() const noexcept { return end() - begin(); }

		void fill(const_reference value) {
			for (auto i = begin(); i != end(); ++i)
				*i = value;
		}

		void swap(array& other) noexcept {
			auto l_beg = begin();
			auto r_beg = other.begin();
			for (; l_beg != end(); ++l_beg, ++r_beg) {
				auto temp = *l_beg;
				*l_beg = *r_beg;
				*r_beg = temp;
			}
		}

	};

	template<class T, std::size_t _Size>
	bool operator==(const array<T, _Size>& lhs, const array<T, _Size>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto l_beg = lhs.begin();
		auto r_beg = rhs.begin();
		for (; l_beg != lhs.end(); ++l_beg, ++r_beg) {
			if (*l_beg != *r_beg)
				return false;
		}
		return true;
	}

	template<class T, std::size_t _Size>
	bool operator!=(const array<T, _Size>& lhs, const array<T, _Size>& rhs) {
		return (!(lhs == rhs));
	}

}

#include "MikuArray.impl.h"

#endif // !MIKU_ARRAY_H__

