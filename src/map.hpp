#ifndef FT_MAP
#define FT_MAP

#include <map>
#include "pair.hpp"
#include "make_pair.hpp"
#include "reverse_iterator.hpp"
// #include "rbtree.hpp"
#include <__tree>

namespace ft
{

// template <class _TreeIterator>
// class __map_iterator
// {
// 	typedef typename _TreeIterator::_NodeTypes NodeTypes;
// 	typedef typename _TreeIterator::__pointer_traits __pointer_traits;

// 	_TreeIterator __i_;

// public:
// 	typedef bidirectional_iterator_tag iterator_category;
// 	typedef typename _NodeTypes::__map_value_type value_type;
// 	typedef typename _TreeIterator::difference_type difference_type;
// 	typedef value_type &reference;
// 	typedef typename _NodeTypes::__map_value_type_pointer pointer;
// };

template <class Key,										   // map::key_type
			class T,											   // map::mapped_type
			class Compare = std::less<Key>,					   // map::key_compare
			class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
			>
class map
{
public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef ft::pair<const Key, T>									value_type;
	typedef Compare													key_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;

	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::size_type						size_type;
	typedef typename allocator_type::difference_type				difference_type;

	class value_compare
		: std::binary_function<value_type, value_type, bool>
	{
		friend class map; // x.first, y.first를 하기 위해 friend???
	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
	public:
		bool operator()(const value_type &x, const value_type &y) const
		{ return comp(x.first, y.first); }
	};

private:
	// typedef __rbtree<value_type, value_compare, allocator_type> __base;
	typedef std::__tree<value_type, value_compare, allocator_type> __base; // ㅇㅣ후 custom tree로 바꿀것.
	__base __tree;

public:
	typedef typename __base::iterator						iterator;
	typedef typename __base::const_iterator					const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	// constructor & destructor
	explicit map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type())
		: __tree(comp, alloc){};

	template <class InputIterator>
	map(InputIterator __f, InputIterator __l,
		const key_compare &__comp = key_compare(),
		const allocator_type &__a = allocator_type())
		: __tree(value_compare(__comp), typename __base::allocator_type(__a))
	{
		insert(__f, __l);
	};
	map(const map &__x)
		: __tree(__x.__tree)
	{
		insert(__x.begin(), __x.end());
	};
	~map(){};

	// [O]iterator
	iterator begin() { return iterator(__tree.begin()); };
	const_iterator begin() const { return const_iterator(__tree.begin()); };
	iterator end() { return iterator(__tree.end()); };
	const_iterator end() const { return const_iterator(__tree.end()); };
	reverse_iterator rbegin() { reverse_iterator(__tree.begin()); };
	const_reverse_iterator rbegin() const { const_reverse_iterator(__tree.begin()); };
	reverse_iterator rend() { reverse_iterator(__tree.end()); };
	const_reverse_iterator rend() const { const_reverse_iterator(__tree.end()); };

	// [O]capacity
	bool empty() const { return __tree.size() == 0; };
	size_type size() const { return __tree.size(); };
	size_type max_size() const { return __tree.max_size(); };

	// element access
	mapped_type &operator[](const key_type &__k)
	{
		// pair중 first가 k와 일치하는 노드를 rbtree에서 찾는다.
		iterator __i = lower_bound(__k);

		// if key not exist, insert that
		if (__i == end())
			*((this->insert(make_pair(__k, mapped_type()))).first);
		else
			return (*__i).second;
	};

	// modifiers ==============================================================
	// - const_iter, iter 2개를 모두 만들어 줬는데 이렇게 하는게 맞는지?

	// INSERT
	// - 삽입할 원소의 키가 이미 맵에 존재하면, 해당 원소의 이터레이터를 반환합니다.
	// - 존재하지않을시, 삽입후 size를 늘려줍니다.
	ft::pair<iterator, bool> insert(const value_type &__v)
	{
		return __tree.__insert_unique(__v);
	};
	iterator insert(iterator __p, const value_type &__v)
	{
		return __tree.__insert_unique(__p.__i_, __v);
	};
	const_iterator insert(const_iterator __p, const value_type &__v)
	{
		return __tree.__insert_unique(__p.__i_, __v);
	};
	template <class InputIterator>
	void insert(InputIterator __f, InputIterator __l)
	{
		// insert할때마다 end가 바뀌어야 하는 게 아닌가?
		for (iterator __e = end(); __f != __l; ++__f)
		{
			insert(__e.__i_, *__f);
		}
	};

	// ERASE
	void erase(iterator __p) { return __tree.erase(__p.__i_); };
	void erase(const_iterator __p) { return __tree.erase(__p.__i_); };
	size_type erase(const key_type &__k) { return __tree.erase_unique(__k); };
	void erase(iterator __f, iterator __l) { return __tree.erase(__f.__i_, __l.__i_); };
	void erase(const_iterator __f, const_iterator __l) { return __tree.erase(__f.__i_, __l.__i_); };
	// ========================================================================

	void swap(map &__x) { __tree.swap(__x.__tree); };
	void clear() { __tree.clear(); };

	// observers ?????
	key_compare key_comp() const { return __tree.value_comp().key_comp(); };
	value_compare value_comp() const { return value_compare(__tree.value_comp().key_comp()); };

	// [O]operations
	iterator find(const key_type &__k) { return __tree.find(__k); };
	const_iterator find(const key_type &__k) const { return __tree.find(__k); };
	size_type count(const key_type &__k) const { return __tree.count(); };
	iterator lower_bound(const key_type &__k) { return __tree.lower_bound(__k); };
	const_iterator lower_bound(const key_type &__k) const { return __tree.lower_bound(__k); };
	iterator upper_bound(const key_type &__k) { return __tree.upper_bound(__k); };
	const_iterator upper_bound(const key_type &__k) const { return __tree.upper_bound(__k); };
	pair<const_iterator, const_iterator> equal_range(const key_type &__k) const { return __tree.equal_range(__k); };
	pair<iterator, iterator> equal_range(const key_type &__k) { return __tree.equal_range(__k); };
	// 1 2 3 4 5 6 7 8 9 [k = 5]
	// [O]allocator
	allocator_type get_allocator() const { return allocator_type(__tree._alloc()); };
};

template <class Key, class T, class Compare, class Alloc>
bool operator== (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return __l.size() == __r.size() && ft::equal(__l.begin(), __l.end(), __r.begin()); };

template <class Key, class T, class Compare, class Alloc>
bool operator< (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return ft::lexicographical_compare(__l.begin(), __l.end(), __r.begin(), __r.end()); };

template <class Key, class T, class Compare, class Alloc>
bool operator!= (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return !(__l == __r); };

template <class Key, class T, class Compare, class Alloc>
bool operator> (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return (__r < __l); };

template <class Key, class T, class Compare, class Alloc>
bool operator>= (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return !(__l < __r); };

template <class Key, class T, class Compare, class Alloc>
bool operator<= (const map<Key,T,Compare,Alloc>& __l,
					const map<Key,T,Compare,Alloc>& __r)
{return !(__r > __l); };

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& __x, map<Key,T,Compare,Alloc>& __y)
{ __x.swap(__y); };

}

#endif
