#ifndef FT_MAP
#define FT_MAP

# include "utility.hpp"
# include "mytree2.hpp"

namespace ft
{

template <class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<ft::pair<const Key, T> >
			>
class map
{
public:
// typedefs:

	typedef Key										key_type;
	typedef T										mapped_type;
	typedef ft::pair<const Key, T>					value_type;
	typedef Compare									key_compare;
	typedef Alloc									allocator_type;

	class value_compare
		: public std::binary_function<value_type, value_type, bool>
	{
	friend class map; // map이 value_compare의 필드에 접근할 수 있게된다? 왜필요한지 잘 모르겠다.
	protected :
		key_compare comp;
		value_compare(key_compare c) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const
		{ return comp(x.first, y.first); }
	};

private:
	typedef ft::rb_tree<value_type, key_compare, Alloc> rep_type;
	rep_type t;  // red-black tree representing map
public:
	typedef typename rep_type::reference						reference;
	typedef typename rep_type::const_reference					const_reference;
	typedef typename rep_type::pointer							pointer;
	typedef typename rep_type::const_pointer					const_pointer;
	typedef typename rep_type::iterator							iterator;
	typedef typename rep_type::const_iterator					const_iterator;
	typedef typename rep_type::reverse_iterator					reverse_iterator;
	typedef typename rep_type::const_reverse_iterator			const_reverse_iterator;
	typedef typename rep_type::difference_type					difference_type;
	typedef typename rep_type::size_type						size_type;
private:
	typedef pair<iterator, bool>						pair_iterator_bool;
public:
// allocation/deallocation

	// empty
	// tree
	explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
		: t(comp, false, alloc){}

	// range
	// insert를 트리생성자에서 하는 방식
	// insert를 맵생성자에서 하는 방식
	template <class InputIterator>
	map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: t(first, last, comp, false, alloc)
	{};

	// copy
	map(const map& x) : t(x.t, false, allocator_type()) {}

	map& operator=(const map& x) { t = x.t; return *this; }

// Iteartors:

	iterator begin() { return t.begin(); }
	const_iterator begin() const { return t.begin(); }
	iterator end() { return t.end(); }
	const_iterator end() const { return t.end(); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return reverse_iterator(begin()); }

// Capacity:

	bool empty() const { return t.empty(); }
	size_type size() const { return t.size(); }
	size_type max_size() const { return t.max_size(); }
	mapped_type& operator[] (const key_type& k)
	{
		return (*((insert(value_type(k, T()))).first)).second;
	};

// Modifiers:
	// single
	pair_iterator_bool insert (const value_type& val) { return t.insert(val); };
	// with hint
	// const 호환
	iterator insert (const_iterator position, const value_type& val) { return t.insert(position, val); };
	// range
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		t.insert(first, last);
	};

	void erase(iterator position) { t.erase(position); }
	size_type erase(const key_type& k) { return t.erase(k); }
	void erase(iterator first, iterator last) { t.erase(first, last); }
	void swap(map& x) { t.swap(x.t); }
	// 구현되어 있지 않은 함수!
	void clear() { t.clear(); }

// Observers:

	key_compare key_comp() const { return t.key_comp(); }
	value_compare value_comp() const { return value_compare(t.key_comp()); }

// map operations:

	iterator find(const key_type& k) { return t.find(k); }
	const_iterator find(const key_type& k) const { return t.find(k); }
	size_type count(const key_type& k) const { return t.count(k); }
	iterator lower_bound(const key_type& k) {return t.lower_bound(k); }
	const_iterator lower_bound(const key_type& k) const { return t.lower_bound(k); }
	iterator upper_bound(const key_type& k) {return t.upper_bound(k); }
	const_iterator upper_bound(const key_type& k) const { return t.upper_bound(k); }

	typedef ft::pair<iterator, iterator> pair_iterator_iterator;

	// 없을시, upper_bound(k) 2개를 pair에 넣어 반환
	pair_iterator_iterator equal_range(const key_type& x) { return t.equal_range(x); }

	typedef ft::pair<const_iterator, const_iterator> pair_citerator_citerator;
	pair_citerator_citerator equal_range(const key_type& x) const { return t.equal_range(x); }

// allocator:
	allocator_type get_allocator() const { return allocator_type(); };
};

template <class Key, class T, class Compare, class Alloc>
bool operator== ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
};
template <class Key, class T, class Compare, class Alloc>
bool operator!= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
};
template <class Key, class T, class Compare, class Alloc>
bool operator< ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};
template <class Key, class T, class Compare, class Alloc>
bool operator<= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (lhs < rhs || lhs == rhs);
};
template <class Key, class T, class Compare, class Alloc>
bool operator>  ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs <= rhs);
};
template <class Key, class T, class Compare, class Alloc>
bool operator>= ( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
};


}

#endif
