#ifndef MIKU_DEQUE_H__
#define MIKU_DEQUE_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"

namespace Miku {

	template<class T, class Allocator>
	class deque;

	namespace Internal {

		template<class T>
		class _Deque_Iterator {
			template<class T, class Allocator>
			friend class deque;

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

		private:
			pointer _B_First;		// iterator���ڵ�buffer��ͷ
			pointer _B_Last;		// iterator���ڵ�buffer��β�ĺ�һ��Ԫ��
			pointer _B_Cur;			// iterator�ڵ�ǰbuffer�е�λ��

			map_pointer _B_Node;	// iterator���ڵ�buffer��map��λ��

		private:
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

		};

		template<class T>
		bool operator==(const _Deque_Iterator<T>& lhs, const _Deque_Iterator<T>& rhs) {
			return lhs._B_Cur == rhs._B_Cur;
		}

		template<class T>
		bool operator!=(const _Deque_Iterator<T>& lhs, const _Deque_Iterator<T>& rhs) {
			return (!(lhs == rhs));
		}

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
		deque(const deque&&);
		deque(std::initializer_list<value_type>);
		// ~deque();

	private:
		pointer _New_Buffer();
		map_pointer _New_Map(const size_type);

		// ��ʼ��map��������ʾelement������buffer��������Ĭ��ֵΪ���
		// Ŀǰ������ǣ�deque���ٰ���_Min_Buffer_Count��buffer��ÿ��buffer����iterator::_Deque_Buffer_Size()��element
		void _Init_Map(size_type = 0);
		// ÿ��deque�����ٵ�buffer��
		static size_type _Min_Buffer_Count() { return 4; }

	public:
		iterator begin() { return start; }

		iterator end() { return finish; }

		size_type size() noexcept { return end() - begin(); }

		bool empty() const noexcept { return begin() == end(); }
	};
}

#include "MikuDeque.impl.h"

#endif // !MIKU_DEQUE_H__
