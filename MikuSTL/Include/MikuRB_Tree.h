#ifndef MIKU_RB_TREE_H__
#define MIKU_RB_TREE_H__

#include "MikuAllocator.h"
#include "MikuAllocTraits.h"
#include "MikuIterator.h"
#include <iterator>
#include <type_traits>
#include <initializer_list>

namespace Miku {

	namespace Internal {

		enum class _Node_Color { Red, Black };

		class _RB_Tree_Node_Base {

		public:
			using _Base_Ptr = _RB_Tree_Node_Base * ;

			_Node_Color node_color;
			_Base_Ptr parent;
			_Base_Ptr left;
			_Base_Ptr right;

		};

		template<class Value>
		class _RB_Tree_Node : public _RB_Tree_Node_Base {

		public:
			Value value_field;
		};

		class _RB_Tree_Iterator_Base {

		public:
			using iterator_category = typename Miku::bidirectional_iterator_tag;
			using _Base_Ptr = _RB_Tree_Node_Base * ;
			using color = typename _Node_Color;

			_Base_Ptr node;

			void _Increment();
			void _Decrement();

		};

		template<class Value>
		class _RB_Tree_Iterator : public _RB_Tree_Iterator_Base {

		public:
			using value_type = Value;
			using pointer = value_type * ;
			using reference = value_type & ;
			using link_type = _RB_Tree_Node<value_type> * ;
			using self = _RB_Tree_Iterator<value_type>;

		public:
			_RB_Tree_Iterator() = default;
			_RB_Tree_Iterator(link_type)

		public:
			self operator++(int);
			self& operator++();
			self operator--(int);
			self& operator--();

			reference operator*() const {
				// TODO
				// ���ﵽ������static_cast����dynamic_cast?
				// ������dynamic_cast? ָ���������ĸ���ָ�룬ת��Ϊ����ָ��
				return static_cast<link_type>(node)->value_field;
			}
			pointer operator->() const {
				return &(operator*());
			}

		};
	}


	// ʵ����ƣ�һ��header(Red)ָ��rb-tree�ĸ��ڵ�(Black), header��leftָ����С�Ľڵ㣬rightָ�����Ľڵ�
	template<class Key, class Value, class KeyOfValue, class Compare,
			class Allocator = Miku::allocator<Internal::_RB_Tree_Node<Value>>>
	class RB_Tree {

	public:
		using key_type = Key;
		using value_type = Value;
		using allocator_type = Allocator;
		using size_type = typename std::size_t;
		using difference_type = typename std::ptrdiff_t;
		using reference = value_type & ;
		using const_reference = const value_type &;
		using pointer = value_type * ;

		using rb_tree_node = typename Internal::_RB_Tree_Node<Value>;
		using link_type = rb_tree_node * ;
		using color = typename Internal::_Node_Color;

		using iterator = typename Internal::_RB_Tree_Iterator<value_type>;



	protected:
		size_type node_count;
		link_type header;
		Compare key_compare;

	public:
		RB_Tree(Compare& = Compare());
		RB_Tree(const RB_Tree&);
		// ~RB_Tree();

	private:
		link_type _New_Node();

	public:
		iterator begin() noexcept { return header->left; }

		iterator end() noexcept { return header; }

		bool empty() const noexcept { return node_count == 0; }

		size_type size() noexcept { return node_count; }

	};

}

#include "MikuRB_Tree.impl.h"

#endif // !MIKU_RB_TREE_H__
