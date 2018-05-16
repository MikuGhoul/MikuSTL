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
		// 这个ctor会用到吗？？

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rotate_Left(link_type _x) {
		link_type _y = _x->right;
		_x->right = _y->left;

		if (_y->left)
			_y->left->parent = _x;

		_y->parent = _x->parent;
		// TODO
		// _x == _Root()这里是否需要对header的parent有操作？
		if (_x == _Root())
			_Root() = _y;
		else if (_x == _x->parent->left)
			_x->parent->left = _y;
		else
			_x->parent->right = _y;

		_y->left = _x;
		_x->parent = _y;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rotate_Right(link_type _x) {
		link_type _y = _x->left;
		_x->left = _y->right;

		if (_y->right)
			_y->right->parent = _x;

		_y->parent = _x->parent;
		// TODO
		// 同 _RB_Tree_Rotate_Left
		if (_x == _Root())
			_Root() = _y;
		else if (_x == _x->parent->right)
			_x->parent->right = _y;
		else
			_x->parent->left = _y;

		_y->right = _x;
		_x->parent = _y;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void Miku::RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::_RB_Tree_Rebalance(link_type _x) {
		/* 
		红黑树性质：
			1. 节点是红色或黑色。
			2. 根是黑色。
			3. 所有叶子都是黑色（叶子是NIL节点）。
			4. 每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
			5. 从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点。
		*/

		// 非根节点 并且 父节点的颜色为红色时
		// 因为新插入的节点的颜色必为红色，所以违反性质5
		while (_x != _Root() && _x->parent->node_color == color::Red) {
			// 1. 插入节点x的父节点是x的祖父节点的左子节点
			if (_x->parent == _x->parent->parent->left) {
				link_type _y = _x->parent->parent->right;
				// 1.1 插入节点x的叔叔节点为红色
				if (_y && _y->node_color == color::Red) {
					// 父节点与叔叔节点变黑，祖父节点变红
					_x->parent->node_color = color::Black;
					_y->node_color = color::Black;
					_y->parent->node_color = color::Red;

					// 通过祖父节点向上递归调整
					_x = _y->parent;
				}
				// 1.2 插入节点x的叔叔节点为黑色，并且x为左子节点，此时可以进行一次右旋，并改变相应颜色
				// 1.3 插入节点x的叔叔节点为黑色，并且x为右子节点，此时可以进行一次左旋，转化为 1.2
				else {
					// 1.3
					if (_x == _x->parent->right) {
						_x = _x->parent;
						_RB_Tree_Rotate_Left(_x);
					}

					// 1.2
					_RB_Tree_Rotate_Right(_x->parent->parent);
					_x->parent->node_color = color::Black;
					_x->parent->right->node_color = color::Red;
				}
			}
			// 2. 插入节点x的父节点是x的祖父节点的右子节点，与1的操作对称
			else {
				link_type _y = _x->parent->parent->left;
				if (_y && _y->node_color == color::Red) {
					_x->parent->node_color = color::Black;
					_y->node_color = color::Black;
					_y->parent->node_color = color::Red;

					_x = _y->parent;
				}
				else {
					if (_x == _x->parent->left) {
						_x = _x->parent;
						_RB_Tree_Rotate_Right(_x);
					}
					_RB_Tree_Rotate_Left(_x->parent->parent);
					_x->parent->node_color = color::Black;
					_x->parent->left->node_color = color::Red;
				}
			}

		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	typename RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator
		RB_Tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(link_type _x, link_type _y, const value_type& value) {

		link_type _z = _New_Node(value);
		// (_y为header) || (插入值 小于 其父节点值)
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
		// 红黑树性质，插入的新节点必为红色
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

		// 寻找到合适的插入位置
		while (_x) {
			_y = _x;
			// key_compare 用作比较大小，两个参数是提取出来的key
			_x = key_compare(KeyOfValue()(value), _Key(_x)) ?
				_x->left : _x->right;
		}

		// _y 为安插节点的父节点，_x 为插入节点的位置
		return insert(_x, _y, value);

	}
}


#endif // !MIKU_RB_TREE_IMPL_H__
