#ifndef FT_MAP
#define FT_MAP

# include <map>
# include "pair.hpp"
# include "reverse_iterator.hpp"
# include "rbtree.hpp"

namespace ft
{
template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = std::less<Key>,                     // map::key_compare
			class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
			>
class map
{
public:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef allocator_type::reference					reference;
	typedef allocator_type::const_reference				const_reference;

	typedef allocator_type::pointer						pointer;
	typedef allocator_type::const_pointer				const_pointer;
	typedef allocator_type::size_type					size_type;
	typedef allocator_type::difference_type				difference_type;

	// ?
	typedef allocator_type::iterator					iterator;
	typedef allocator_type::const_iterator				const_iterator;

	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	template <class Key, class T, class Compare, class Alloc>
	class value_compare
	: std::binary_function<value_type,value_type,bool>
	{
		friend class map; // ?
	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	}

private:
	// member variable
	allocator_type		_alloc;
	typedef rbtree<value_type, allocator_type>				__base;
	typedef __rbtree<__value_type, __vc, __allocator_type>	__base;
	__base __tree;

	// pointer				_begin;
	// pointer				_end;
	// pointer				_end_cap;

public:
	// constructor & destructor
	explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
		: __tree(comp, alloc) {};

	template <class InputIterator>
	map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: __tree(first, last, comp, alloc) {};
	map (const map& x)
		: __tree(x) {};
	~map() {};

	// [O]iterator
	iterator begin() { return iterator(__tree._begin()); };
	const_iterator begin() const { return const_iterator(__tree._begin()); };
	iterator end() { return iterator(__tree._end()); };
	const_iterator end() const { return const_iterator(__tree._end()); };
	reverse_iterator rbegin() { reverse_iterator(__tree._begin()); };
	const_reverse_iterator rbegin() const { const_reverse_iterator(__tree._begin()); };
	reverse_iterator rend() { reverse_iterator(__tree._end()); };
	const_reverse_iterator rend() const { const_reverse_iterator(__tree._end()); };

	// [O]capacity
	bool empty() const { return __tree.size() == 0; };
	size_type size() const { return __tree.size(); };
	size_type max_size() const { return __tree.max_size(); };

	// element access
	// ??
	mapped_type& operator[] (const key_type& k)
	{
		// pair중 first가 k와 일치하는 노드를 rbtree에서 찾는다.
	};

	// modifiers ==============================================================
	pair<iterator,bool> insert (const value_type& val)
	{
		// pair를 rbtree에 추가한다.
	};
	iterator insert (iterator position, const value_type& val);
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last);

	void erase (iterator position);
	size_type erase (const key_type& k);
	void erase (iterator first, iterator last);
	// ========================================================================

	void swap (map& x) { __tree.swap(x.__tree); };
	void clear() { __tree.clear(); };

	// observers ?????
	key_compare key_comp() const { return __tree.value_comp().key_comp(); };
	value_compare value_comp() const { return value_compare( __tree.value_comp().key_comp()); };

	// [O]operations
	iterator find (const key_type& k) { return __tree.find(k); };
	const_iterator find (const key_type& k) const { return __tree.find(k); };
	size_type count (const key_type& k) const { return __tree.count(); };
	iterator lower_bound (const key_type& k) { return __tree_.lower_bound(k); };
	const_iterator lower_bound (const key_type& k) const { return __tree_.lower_bound(k); };
	iterator upper_bound (const key_type& k) { return __tree_.upper_bound(k); };
	const_iterator upper_bound (const key_type& k) const { return __tree_.upper_bound(k); };
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const { return __tree_.equal_range(k); };
	pair<iterator,iterator> equal_range (const key_type& k) { return __tree_.equal_range(k); };

	// [O]allocator
	allocator_type get_allocator() const { return allocator_type(__tree._alloc()); };

};

}

#endif