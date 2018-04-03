#ifndef MIKU_LIST_IMPL_H__
#define MIKU_LIST_IMPL_H__

#include "MikuList.h"
	
namespace Miku {

	template<class T, class Allocator>
	typename list<T, Allocator>::link_type list<T, Allocator>::_New_Node() {
		return allocator_type::allocate();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::link_type list<T, Allocator>::_New_Node(const_reference value) {
		auto p = _New_Node();
		Miku::allocator<value_type>::construct(&p->data, value);
		return p;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::_Void_Init() {
		node = _New_Node();
		node->next = node;
		node->prev = node;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::_Destroy(link_type _Node) {
		_Node->prev->next = _Node->next;
		_Node->next->prev = _Node->prev;
		allocator_type::destroy(_Node);
		allocator_type::deallocate(_Node);
	}

	template<class T, class Allocator>
	list<T, Allocator>::list() {
		_Void_Init();
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count, const_reference value) {
		_Void_Init();
		insert(begin(), count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, 
		typename std::enable_if<!std::is_integral<InputIt>::value>::type *) {
		_Void_Init();
		insert(begin(), first, last);
	}
	/*template<class T, class Allocator>
	template<class InputIt>
	inline Miku::list<T, Allocator>::list(InputIt first, InputIt last, 
		typename std::enable_if<std::is_same<typename Iterator_Traits<InputIt>::iterator_category, bidirectional_iterator_tag>::value>::type *) {
		std::cout << "what the fuck???" << std::endl;
	}*/

	template<class T, class Allocator>
	list<T, Allocator>::list(list& other) {
		_Void_Init();
		insert(begin(), other.begin(), other.end());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(list&& other) : node(other.node){
		other.node = nullptr;
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(std::initializer_list<value_type> init) {
		_Void_Init();
		insert(begin(), init.begin(), init.end());
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::front() {
		return *begin();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::front() const {
		return *begin();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::reference list<T, Allocator>::back() {
		return *(--end());
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::const_reference list<T, Allocator>::back() const {
		return *(--end());
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::size_type Miku::list<T, Allocator>::size() noexcept {
		int _size = 0;
		for (iterator i = begin(); i != end(); ++i) {
			++_size;
		}
		return _size;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(const_reference value) {
		insert(end(), value);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(value_type&& value) {
		// TODO
		insert(end(), std::move(value));
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(const_reference value) {
		insert(begin(), value);
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::pop_back() {
		_Destroy(node->prev);
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::pop_front() {
		_Destroy(node->next);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::clear() noexcept {
		link_type _curr = node->next;
		while (_curr != node) {
			link_type temp = _curr;
			_curr = _curr->next;
			_Destroy(temp);
		}
		node->next = node;
		node->prev = node;
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::insert(iterator pos, const_reference value) {
		link_type p = _New_Node(value);
		pos.node->prev->next = p;
		p->prev = pos.node->prev;
		p->next = pos.node;

		pos.node->prev = p;
		return p;
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::insert(iterator pos, size_type count, const_reference value) {
		for (int i = 0; i != count; ++i)
			insert(pos, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void Miku::list<T, Allocator>::insert(iterator pos, InputIt first, InputIt last,
		typename std::enable_if<!std::is_integral<InputIt>::value>::type*) {
		// 插入在pos前，而且pos不更改，所以可以直接调用insert(iterator, const_reference)
		for (; first != last; ++first)
			insert(pos, *first);
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::erase(iterator pos) {		
		pos.node->prev->next = pos.node->next;
		pos.node->next->prev = pos.node->prev;
		link_type res = pos.node->next;
		_Destroy(pos.node);
		return res;
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::erase(iterator first, iterator last) {
		iterator res;
		// first会被析构，所以这里first的递增不能写在for里
		for (; first != last; )
			res = erase(first++);
		return res;
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::erase(const_iterator pos) {
		// erase(static_cast<iterator>(pos));
		pos.node->prev->next = pos.node->next;
		pos.node->next->prev = pos.node->prev;
		link_type res = pos.node->next;
		_Destroy(const_cast<Miku::Internal::_List_Node<T>*>(pos.node));
		return res;
	}

	template<class T, class Allocator>
	typename Miku::list<T, Allocator>::iterator Miku::list<T, Allocator>::erase(const_iterator first, const_iterator last) {
		iterator res;
		for (; first != last;)
			res = erase(first++);
		return res;
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::resize(size_type count, const_reference value) {
		auto _size = size();
		if (count < _size) {
			while (count != _size) {
				pop_back();
				--_size;
			}
		}
		else {
			while (count != _size) {
				push_back(value);
				++_size;
			}
		}
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::swap(list& other) noexcept {
		std::swap(node, other.node);
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::merge(list& other) {
		size_type _size = size();
		auto l_beg = begin();
		auto r_beg = other.begin();
		auto l_end = end();
		auto r_end = other.end();
		for (; l_beg != l_end && r_beg != r_end; ++l_beg) {
			if (*l_beg > *r_beg) {
				auto temp = r_beg++;

				l_beg.node->prev->next = temp.node;
				temp.node->prev = l_beg.node->prev;
				l_beg.node->prev = temp.node;
				temp.node->next = l_beg.node;
			}
		}
		if (r_beg != r_end) {
			// 除了other list的null node的之外都要merge到this list中
			l_end.node->prev->next = r_beg.node;
			r_beg.node->prev = l_end.node->prev;
			r_end.node->prev->next = l_end.node;
			l_end.node->prev = r_end.node->prev;

			// other list清空
			r_end.node->next = r_end.node;
			r_end.node->prev = r_end.node;
		}
	}
	

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::sort() {
		// TODO, 用快排或归并重写
		// 冒泡
		size_type _size = size();
		for (iterator i = begin(); i != end(); ++i) {
			iterator temp = i;
			for (iterator j = ++temp; j != end(); ++j) {
				if (*i > *j) {
					std::swap(i.node->data, j.node->data);
				}
			}
		}
	}

	template<class T, class Allocator>
	template<class Compare>
	void Miku::list<T, Allocator>::sort(Compare comp) {
		size_type _size = size();
		for (iterator i = begin(); i != end(); ++i) {
			iterator temp = i;
			for (iterator j = ++temp; j != end(); ++j) {
				if (!comp(*i, *j)) {
					std::swap(i.node->data, j.node->data);
				}
			}
		}
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::splice(iterator pos, list& other) {
		splice(pos, other, other.begin(), other.end());
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::splice(iterator pos, list& other, iterator it) {
		splice(pos, other, it, other.end());
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::splice(iterator pos, list& other, iterator first, iterator last) {
		// [first, last) == [first, last->prev]
		pos.node->prev->next = first.node;
		first.node->prev = pos.node->prev;
		pos.node->prev = last.node->prev;
		last.node->prev->next = pos.node;

		other.node->next = last.node;
		last.node->prev = other.node;
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::remove(const_reference value) {
		// erase会_Destroy, i的递增要注意
		for (auto i = begin(); i != end(); ) {
			if (*i == value) {
				erase(i++);
				continue;
			}
			++i;
		}
	}

	template<class T, class Allocator>
	template<class UnaryPredicate>
	void Miku::list<T, Allocator>::remove_if(UnaryPredicate p) {
		for (auto i = begin(); i != end(); ) {
			if (p(*i)) {
				erase(i++);
				continue;
			}
			++i;
		}
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::reverse() noexcept {
		auto _Now_Iter = end();

		do {
			auto temp = _Now_Iter.node->next;
			_Now_Iter.node->next = _Now_Iter.node->prev;
			_Now_Iter.node->prev = temp;
		} while (++_Now_Iter != end());
	}

	template<class T, class Allocator>
	void Miku::list<T, Allocator>::unique() {
		auto i = begin();
		auto j = ++begin();
		for (; j != end() && i != end(); ++i, ++j) {
			if (*i == *j) {
				erase(j);
				auto temp = i;
				j = ++temp;
			}
		}
	}

	template<class T, class Allocator>
	template<class BinaryPredicate>
	void Miku::list<T, Allocator>::unique(BinaryPredicate p) {
		auto i = begin();
		auto j = ++begin();
		for (; j != end() && i != end(); ++i, ++j) {
			if (p(*i, *j)) {
				erase(j);
				auto temp = i;
				j = ++temp;
			}
		}
	}

}
#endif // !MIKU_LIST_IMPL_H__
