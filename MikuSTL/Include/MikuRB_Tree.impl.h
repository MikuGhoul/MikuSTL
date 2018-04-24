#ifndef MIKU_RB_TREE_IMPL_H__
#define MIKU_RB_TREE_IMPL_H__

#include "MikuRB_Tree.h"

namespace Miku{

	namespace Internal {

		template<class Value>
		void _RB_Tree_Iterator<Value>::_Increment() {
			if (node->right) {

				node = node->right;
				while (node->left) {
					node = node->left;
				}

			}
			else {
				link_type _Parent = node->parent;
				while (node == _Parent->right) {
					node = _Parent;
					_Parent = _Parent->parent;
				}
				// TODO
				// 这里header好像有特判?
			}
		}

		template<class Value>
		void _RB_Tree_Iterator<Value>::_Decrement() {

		}

	}

}


#endif // !MIKU_RB_TREE_IMPL_H__
