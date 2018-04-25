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
				// 这里到底是用static_cast还是dynamic_cast?
				// 好像是dynamic_cast? 指向子类对象的父类指针，转型为子类指针
				return static_cast<link_type>(node)->value_field;
			}
			pointer operator->() const {
				return &(operator*());
			}

		};
	}


	// 实现设计：一个header(Red)指向rb-tree的根节点(Black), header的left指向最小的节点，right指向最大的节点
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
