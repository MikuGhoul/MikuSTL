// #include "TinyList.h"

#ifndef TINYLIST_IMPL_H__
#define TINYLIST_IMPL_H__

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

	/*template<class T, class Allocator>
	void Miku::list<T, Allocator>::sort() {

	}*/

}
#endif // !TINYLIST_IMPL_H__
