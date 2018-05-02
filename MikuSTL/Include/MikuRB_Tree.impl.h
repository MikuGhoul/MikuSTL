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
	inline typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_New_Node() {
		return allocator_type::allocate();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	inline typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_New_Node(reference value) {
		link_type p = allocator_type::allocate();
		Miku::allocator<Value>::construct(&p->value_field, value);
		return p;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::RB_Tree(Compare comp)
		: node_count(0), key_compare(comp) {
		header = _New_Node();

		header->node_color = color::Red;
		_Root() = nullptr;
		_Left_Most() = header;
		_Right_Most() = header;

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::RB_Tree(const RB_Tree& _r)
		: node_count(_r.node_count), key_compare(_r.key_compare) {
		header = _New_Node();

		header->node_color = color::Red;
		// TODO
		// ���ctor���õ��𣿣�

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rotate_Left(link_type _x) {

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rotate_Right(link_type _x) {

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rebalance(link_type _x) {
		
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(link_type _x, link_type _y, const value_type& value) {

		link_type _z = _New_Node(value);
		// (_yΪheader) || (����ֵ С�� �丸�ڵ�ֵ)
		if (_y == header || key_compare(KeyOfValue()(value), _Key(_y))) {

			_y->left = _z;

			if (_y == header)
				_Root() = _Left_Most() = _Right_Most() = _z;
			else if (_y == _Left_Most())
				_Left_Most() = _z;
		}
		// 
		else {

			_y->right = _z;

			if (_y == _Right_Most())
				_Right_Most() == _z;
		}

		_z->parent = _y;
		_z->left = _z->right = nullptr;
		// ��������ʣ�������½ڵ��Ϊ��ɫ
		_z->node_color = color::Red;
		++node_count;

		_RB_Tree_Rebalance(_z);
		return _z;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::insert_euqal(const value_type& value) {
		
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::insert_unique(const value_type& value) {
		link_type _y = header;
		link_type _x = _Root();

		// Ѱ�ҵ����ʵĲ���λ��
		while (_x) {
			_y = _x;
			// key_compare �����Ƚϴ�С��������������ȡ������key
			_x = key_compare(KeyOfValue()(value), _Key(_x)) ?
				_x->left : _x->right;
		}

		// _y Ϊ����ڵ�ĸ��ڵ㣬_x Ϊ����ڵ��λ��
		return insert(_x, _y, value);

	}
}


#endif // !MIKU_RB_TREE_IMPL_H__
