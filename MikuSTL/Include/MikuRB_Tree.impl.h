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
				
				// ��Ϊ�������ĵ�����Զ��β�������������node����ָ��header( �� end() )
				// ������������䣬��ܵ������������ "������Ϊ��"�ĸ��ڵ� �����
				if (_Parent != node->right)
					node = _Parent;
			}
		}

		void _RB_Tree_Iterator_Base::_Decrement() {
			// nodeΪend()ʱ���ݼ��õ����е����ڵ㣬��_Increment��Ȼ�Ͳ��������������
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
				// �ݼ��ĵ�������Զ�ǵ�һ��Ԫ�صĵ�����( �� begin() ), �������ﲻ����
				// ���ﴦ���������У�1. node��parent���Ҷ��� 2. �ղ�������˳��� 3. ��header�ˣ�����һ��ע��
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
		// ���ctor���õ��𣿣�

	}
}


#endif // !MIKU_RB_TREE_IMPL_H__
