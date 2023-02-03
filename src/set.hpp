#ifndef FT_SET
#define FT_SET

# include "utility.hpp"
# include "mytree2.hpp"

namespace ft
{

template <class T,							// set::key_type/value_type
			class Compare = std::less<T>,	// set::key_compare/value_compare
			class Alloc = std::allocator<T>	// set::allocator_type
			>
class set
{
public:
// typedefs:
	// pair가 아닌 T만 보내는 방법?
	// 여기를 어떻게 해줘야 할지 모르겠다.
	//typedef ft::pair<const T, int>						value_type;
	//typedef const T										value_type;
	typedef T											value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;

	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	class value_compare
		: public std::binary_function<value_type, value_type, bool>
	{
	friend class set; // set이 value_compare의 필드에 접근할 수 있게된다? 왜필요한지 잘 모르겠다.
	protected:
		key_compare comp;
		value_compare(key_compare c) : comp(c) {}
	public:
		bool operator()(const value_type& x, const value_type& y) const
		{ return comp(x, y); }
	};

private:
	// value_type을 넘기면 rb_tree에서는 pair로 해석한다... 어떢할까
	typedef ft::rb_tree<value_type, key_compare, Alloc> rep_type;
	rep_type t;  // red-black tree representing set
public:
	// 멤버타입 rep_type을 선언해야 함.
	typedef typename rep_type::iterator						iterator;
	typedef typename rep_type::const_iterator				const_iterator;
	typedef typename rep_type::reverse_iterator				reverse_iterator;
	typedef typename rep_type::const_reverse_iterator		const_reverse_iterator;
	typedef typename rep_type::difference_type				difference_type;
	typedef typename rep_type::size_type					size_type;
private:
	typedef pair<iterator, bool>						pair_iterator_bool;
public:

	explicit set(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
		: t(comp, false, alloc) {}

	template <class InputIterator>
	set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: t(first, last, comp, false, alloc) {}

	set(const set& x) : t(x.t, false, allocator_type()) {}
	~set() {}
	set& operator= (const set& x) { t = x.t; return *this; }

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

// Modifiers:
	// single
	pair_iterator_bool insert (const value_type& val) { return t.insert(val); };
	// hint
	iterator insert (iterator position, const value_type& val) { return t.insert(position, val); };
	// range
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		t.insert(first, last);
	};

	void erase(iterator position) { t.erase(position); }
	size_type erase(const value_type& val) { return t.erase(val); }
	void erase(iterator first, iterator last) { t.erase(first, last); }
	void swap(set& x) { t.swap(x.t); }
	// 구현되어 있지 않은 함수!
	void clear() { t.clear(); }

// Observers: <- 왜 옵저버라고 부르는지 모르겠다.

	key_compare key_comp() const { return t.key_comp(); }
	value_compare value_comp() const { return value_compare(t.key_comp()); }

// set operations:

	iterator find(const value_type& val) { return t.find(val); }
	const_iterator find(const value_type& val) const { return t.find(val); }
	size_type count(const value_type& val) const { return t.count(val); }
	iterator lower_bound(const value_type& val) {return t.lower_bound(val); }
	const_iterator lower_bound(const value_type& val) const { return t.lower_bound(val); }
	iterator upper_bound(const value_type& val) {return t.upper_bound(val); }
	const_iterator upper_bound(const value_type& val) const { return t.upper_bound(val); }

	typedef ft::pair<iterator, iterator> pair_iterator_iterator;

	pair_iterator_iterator equal_range(const value_type& val) { return t.equal_range(val); }

	typedef ft::pair<const_iterator, const_iterator> pair_citerator_citerator;
	pair_citerator_citerator equal_range(const value_type& val) const { return t.equal_range(val); }

};

template <class T, class Compare, class Alloc>
bool operator== ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
};
template <class T, class Compare, class Alloc>
bool operator!= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return !(lhs == rhs);
};
template <class T, class Compare, class Alloc>
bool operator< ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};
template <class T, class Compare, class Alloc>
bool operator<= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return (lhs < rhs || lhs == rhs);
};
template <class T, class Compare, class Alloc>
bool operator>  ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return !(lhs <= rhs);
};
template <class T, class Compare, class Alloc>
bool operator>= ( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
{
	return !(lhs < rhs);
};

template <class T, class Compare, class Alloc>
void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
{
	set<T,Compare,Alloc> z = x;
	x = y;
	y = z;
};

}

#endif
