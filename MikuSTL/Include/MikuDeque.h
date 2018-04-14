#ifndef MIKU_DEQUE_H__
#define MIKU_DEQUE_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"

namespace Miku {

	namespace Internal {

		template<class T>
		class _Deque_Iterator {

		public:
			using iterator_category = typename std::random_access_iterator_tag;
			using value_type = T;
			using pointer = T * ;
			using reference = T & ;
			using const_reference = const T & ;
			using size_type = typename std::size_t;
			using difference_type = typename std::ptrdiff_t;

			using self = _Deque_Iterator<T>;

			using map_pointer = pointer * ;

			// TODO��û����ƺó������...
			// buffer���ȷ������
			// 1. ָ��Ϊ��Ϊ���_Size
			// 2. ��_SizeΪ0����ÿ��Ԫ��С��512 byte������Ϊ 512 / sizeof(T)
			// 3. ��_SizeΪ0����ÿ��Ԫ�ش���512 byte������Ϊ 1
			static size_type _Deque_Buffer_Size(size_type _Size = 0) {
				return _Size != 0 ? _Size : (sizeof(T) < 512 ? 512 / sizeof(T) : 1);
			}

		/*private:*/
			pointer _B_First;		// iterator���ڵ�buffer��ͷ
			pointer _B_Last;		// iterator���ڵ�buffer��β�ĺ�һ��Ԫ��
			pointer _B_Cur;			// iterator�ڵ�ǰbuffer�е�λ��

			map_pointer _B_Node;	// iterator���ڵ�buffer��map��λ��

		/*private:*/
			void _Set_Node(map_pointer);

		public:
			_Deque_Iterator() : _B_First(nullptr), _B_Last(nullptr), _B_Cur(nullptr), _B_Node(nullptr) {}
			_Deque_Iterator(size_type _index, pointer _cur, map_pointer _node) :
				_B_First(*_node), _B_Last(_B_First + _index), _B_Cur(_cur), _B_Node(_node) {}
			_Deque_Iterator(const _Deque_Iterator& other) :
				_B_First(other._B_First), _B_Last(other._B_Last), _B_Cur(other._B_Cur), _B_Node(other._B_Node) {}


			reference operator*() const { return *_B_Cur; }
			pointer operator->() const { return _B_Cur; }

			self& operator++();
			self operator++(int);

			self& operator--();
			self operator--(int);

			difference_type operator-(const self&) const;

			self& operator+=(difference_type);
			self operator+(difference_type);

			self& operator-=(difference_type);
			self operator-(difference_type);

			bool operator==(const self& other) const { return _B_Cur == other._B_Cur; }
			bool operator!=(const self& other) const { return _B_Cur != other._B_Cur; }
			bool operator<(const self& other) const {
				return _B_Node == other._B_Node ? _B_Cur < other._B_Cur : _B_Node < other._B_Node;
			}

		};

		template<class T>
		class _Deque_Const_Iterator {

		public:
			using iterator_category = typename std::random_access_iterator_tag;
			using value_type = T;
			using pointer = const T * ;
			using reference = const T & ;
			using const_reference = const T &;
			using size_type = typename std::size_t;
			using difference_type = typename std::ptrdiff_t;

			using self = _Deque_Const_Iterator<T>;

			using map_pointer = T** ;
			static size_type _Deque_Buffer_Size(size_type _Size = 0) {
				return _Size != 0 ? _Size : (sizeof(T) < 512 ? 512 / sizeof(T) : 1);
			}

		/*private:*/
			pointer _B_First;
			pointer _B_Last;
			pointer _B_Cur;

			map_pointer _B_Node;

		/*private:*/
			void _Set_Node(map_pointer);

		public:
			_Deque_Const_Iterator() : _B_First(nullptr), _B_Last(nullptr), _B_Cur(nullptr), _B_Node(nullptr) {}
			_Deque_Const_Iterator(size_type _index, pointer _cur, map_pointer _node) :
				_B_First(*_node), _B_Last(_B_First + _index), _B_Cur(_cur), _B_Node(_node) {}
			_Deque_Const_Iterator(const _Deque_Const_Iterator& other) :
				_B_First(other._B_First), _B_Last(other._B_Last), _B_Cur(other._B_Cur), _B_Node(other._B_Node) {}
			_Deque_Const_Iterator(const _Deque_Iterator<value_type>& other) :
				_B_First(other._B_First), _B_Last(other._B_Last), _B_Cur(other._B_Cur), _B_Node(other._B_Node) {}


			reference operator*() const { return *_B_Cur; }
			pointer operator->() const { return _B_Cur; }

			self& operator++();
			self operator++(int);

			self& operator--();
			self operator--(int);

			difference_type operator-(const self&) const;

			self& operator+=(difference_type);
			self operator+(difference_type);

			self& operator-=(difference_type);
			self operator-(difference_type);

			bool operator==(const self& other) const { return _B_Cur == other._B_Cur; }
			bool operator!=(const self& other) const { return _B_Cur != other._B_Cur; }
			bool operator<(const self& other) const {
				return _B_Node == other._B_Node ? _B_Cur < other._B_Cur : _B_Node < other._B_Node;
			}

		};

	}

	// ʵ����ƣ�һ����Ϊmap�������ռ䣬�洢ָ��buffer��ָ�룬buffer�������������
	template<class T, class Allocator = Miku::allocator<T>>
	class deque {

	public:
		using value_type = T;
		using allocator_type = Allocator;
		using size_type = typename std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type&;
		using pointer = typename Miku::allocator_traits<Allocator>::pointer;
		using const_pointer = typename Miku::allocator_traits<Allocator>::const_pointer;

		using map_pointer = pointer * ;

		using iterator = Internal::_Deque_Iterator<T>;
		using const_iterator = Internal::_Deque_Const_Iterator<T>;

	private:
		// start��finish�������ݵ�buffer��ͷβ������map��ͷβ
		iterator start;
		// finish���ﲻ���ҿ�����. [start, finish]
		iterator finish;
		map_pointer map;
		size_type mapSize;

	public:
		deque();
		explicit deque(size_type, const_reference = value_type());
		template<class InputIt>
		deque(InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		deque(const deque&);
		deque(deque&&);
		deque(std::initializer_list<value_type>);
		// ~deque();

	private:
		pointer _New_Buffer();

		map_pointer _New_Map(const size_type);

		// ��ʼ��map��������ʾelement������buffer��������Ĭ��ֵΪ���
		// Ŀǰ������ǣ�deque���ٰ���_Min_Buffer_Count��buffer��ÿ��buffer����iterator::_Deque_Buffer_Size()��element
		void _Init_Map(size_type = 0);

		// void _Start_Move_Left();

		// void _Finish_Move_Right();
		
		void _Push_Front_Aux(size_type);

		void _Push_Back_Aux(size_type);

		void _Map_Growth();

		void _Insert_Start_Aux(size_type, const_reference, size_type);
		template<class InputIt>
		void _Insert_Start_Aux(InputIt, InputIt, size_type);


		void _Insert_Finish_Aux(size_type, const_reference, size_type);
		template<class InputIt>
		void _Insert_Finish_Aux(InputIt, InputIt, size_type);

		iterator Insert_Aux(iterator, const_reference);
		iterator Insert_Aux(iterator, size_type, const_reference);
		template<class InputIt>
		iterator Insert_Aux(iterator, InputIt, InputIt);

		// ÿ��deque�����ٵ�buffer��
		static size_type _Min_Buffer_Count() { return 4; }

	public:

		iterator begin() noexcept { return start; }
		const_iterator begin() const noexcept { return start; }
		const_iterator cbegin() const noexcept { return start; }

		iterator end() noexcept { return finish; }
		const_iterator end() const noexcept { return finish; }
		const_iterator cend() const noexcept { return finish; }

		reference operator[](size_type);
		const_reference operator[](size_type) const;

		reference at(size_type);
		const_reference at(size_type) const ;

		reference front() { return *start; }
		const_reference front() const { return *(static_cast<const_iterator>(start)); }

		reference back() { return *(finish - 1); }
		const_reference back() const { return *(static_cast<const_iterator>(finish) - 1); }

		size_type size() noexcept { return end() - begin(); }

		bool empty() const noexcept { return begin() == end(); }

		void push_front(const_reference);
		void push_front(value_type&&);

		void pop_front();

		void push_back(const_reference);
		void push_back(value_type&&);

		void pop_back();

		iterator insert(iterator, const_reference);
		iterator insert(iterator, size_type, const_reference);
		template<class InputIt>
		iterator insert(iterator, InputIt, InputIt,
			typename std::enable_if<!std::is_integral<InputIt>::value>::type* = nullptr);
		iterator insert(iterator, std::initializer_list<value_type>);

		iterator erase(iterator);
		iterator erase(iterator, iterator);

		void swap(deque&) noexcept;

		void clear() noexcept;

	};


	// ������������Ժ�ŵ�һ��algorithm�ÿ���������񶼲����
	template<class T, class Allocator>
	bool operator==(deque<T, Allocator>& lhs, deque<T, Allocator>& rhs) {
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
	bool operator!=(deque<T, Allocator>& lhs, deque<T, Allocator>& rhs) {
		return (!(lhs == rhs));
	}
}

#include "MikuDeque.impl.h"

#endif // !MIKU_DEQUE_H__
