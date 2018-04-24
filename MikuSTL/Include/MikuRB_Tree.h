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

		template<class Value>
		class _RB_Tree_Node {

		public:
			using _Node_Pointer = _RB_Tree_Node<Value> * ;


			_Node_Color node_color;

			_Node_Pointer parent;
			_Node_Pointer left;
			_Node_Pointer right;

			Value value_field;

		};

		template<class Value>
		class _RB_Tree_Iterator {

		public:
			using iterator_category = typename Miku::bidirectional_iterator_tag;
			using value_type = Value;
			using pointer = value_type * ;
			using reference = value_type & ;
			using link_type = _RB_Tree_Node<value_type> * ;

			link_type node;

			void _Increment();

			void _Decrement();

		};

	}

	template<class Key,
			class Value,
			class KeyOfValue,
			class Compare,
			class Allocator = Miku::allocator<Internal::_RB_Tree_Node<Value>>
	class RB_Tree {

	public:
		using size_type = std::size_t;
		using rb_tree_node = Internal::_RB_Tree_Node<Value>;
		using link_type = rb_tree_node * ;

	protected:
		size_type node_count;
		link_type header;
		Compare key_compare;


	};

}

#include "MikuRB_Tree.impl.h"

#endif // !MIKU_RB_TREE_H__
