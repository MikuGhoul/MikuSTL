#ifndef MIKU_RB_TREE_IMPL_H__
#define MIKU_RB_TREE_IMPL_H__

#include "MikuRB_Tree.h"

namespace Miku{

	namespace Internal {

		void _RB_Tree_Iterator_Base::_Increment() {
			if (node->right) {
				node = node->right;
				while (node->left)
					node = node->left;
			}
			else {
				_Base_Ptr _Parent = node->parent;
				while (node == _Parent->right) {
					node = _Parent;
					_Parent = _Parent->parent;
				}
				
				// 因为迭代器的递增最远是尾后迭代器，所以node可以指向header( 即 end() )
				// 正常都会走这句，规避的特判情况是求 "右子树为空"的根节点 的情况
				if (_Parent != node->right)
					node = _Parent;
			}
		}

		void _RB_Tree_Iterator_Base::_Decrement() {
			// node为end()时，递减得到树中的最大节点，而_Increment当然就不存在这种情况了
			if (node->parent->parent == node && node->node_color == color::Red)
				node = node->right;
			else if (node->left) {
				node = node->left;
				while (node->right)
					node = node->right;
			}
			else {
				_Base_Ptr _Parent = node->parent;
				while (node == _Parent->left) {
					node = _Parent;
					_Parent = _Parent->parent;
				}
				// 递减的迭代器最远是第一个元素的迭代器( 即 begin() ), 所以这里不特判
				// 这里处理的是情况有：1. node是parent的右儿子 2. 刚才左儿子退出的 3. 到header了，接上一句注释
				node = _Parent;
			}
		}

		template<class Value>
		typename _RB_Tree_Iterator<Value>::self& _RB_Tree_Iterator<Value>::operator++() {
			_Increment();
			return *this;
		}

		template<class Value>
		typename _RB_Tree_Iterator<Value>::self _RB_Tree_Iterator<Value>::operator++(int) {
			self temp = *this;
			++*this;
			return temp;
		}

		template<class Value>
		typename _RB_Tree_Iterator<Value>::self& _RB_Tree_Iterator<Value>::operator--() {
			_Decrement();
			return *this;
		}

		template<class Value>
		typename _RB_Tree_Iterator<Value>::self _RB_Tree_Iterator<Value>::operator--(int) {
			self temp = *this;
			++*this;
			return temp;
		}

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_New_Node() {
		return allocator_type::allocate();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::RB_Tree(Compare& comp)
		: node_count(0), key_compare(comp) {
		header = _New_Node();

		header->node_color = color::Red;
		header->parent = nullptr;
		header->left = header;
		header->right = header;

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::RB_Tree(const RB_Tree& _r)
		: node_count(_r.node_count), key_compare(_r.key_compare) {
		header = _New_Node();

		header->node_color = color::Red;
		// TODO
		// 这个ctor会用到吗？？

	}
}


#endif // !MIKU_RB_TREE_IMPL_H__
