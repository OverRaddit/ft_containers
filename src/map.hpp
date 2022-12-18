#ifndef FT_MAP
#define FT_MAP

# include <map>

namespace ft
{
template < class Key,                                     // map::key_type
			class T,                                       // map::mapped_type
			class Compare = less<Key>,                     // map::key_compare
			class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
			>
struct map
{
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef asdf										value_compare; // ?
	typedef Alloc										allocator_type;
	typedef allocator_type::reference					reference;
	typedef allocator_type::const_reference				const_reference;
	typedef allocator_type::pointer						pointer;
	typedef allocator_type::const_pointer				const_pointer;
	typedef allocator_type::iterator					iterator;
	typedef allocator_type::const_iterator				const_iterator;

	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	typedef iterator_traits<iterator>::difference_type	difference_type;
	typedef size_t										size_type; // ?

	// member variable
	allocator_type		_alloc;
	pointer				_begin;
	pointer				_end;
	pointer				_end_cap;

	// constructor & destructor
	explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
	map (const map& x);
	~map();

	// [O]iterator
	iterator begin() { return iterator(_begin); };
	const_iterator begin() const { return const_iterator(_begin); };
	iterator end() { return iterator(_end); };
	const_iterator end() const { return const_iterator(_end); };
	reverse_iterator rbegin() { reverse_iterator(_begin); };
	const_reverse_iterator rbegin() const { const_reverse_iterator(_begin); };
	reverse_iterator rend() { reverse_iterator(_end); };
	const_reverse_iterator rend() const { const_reverse_iterator(_end); };

	// [O]capacity
	bool empty() const { return _begin == _end; };
	size_type size() const { return _end - begin; };
	size_type max_size() const { return _alloc.max_size(); };

	// element access
	mapped_type& operator[] (const key_type& k);

	// modifiers
	pair<iterator,bool> insert (const value_type& val);
	iterator insert (iterator position, const value_type& val);
	template <class InputIterator>
	void insert (InputIterator first, InputIterator last);

	void erase (iterator position);
	size_type erase (const key_type& k);
	void erase (iterator first, iterator last);

	void swap (map& x);
	void clear();

	// observers
	key_compare key_comp() const;
	value_compare value_comp() const;

	// operations
	iterator find (const key_type& k);
	const_iterator find (const key_type& k) const;
	size_type count (const key_type& k) const;
	iterator lower_bound (const key_type& k);
	const_iterator lower_bound (const key_type& k) const;
	iterator upper_bound (const key_type& k);
	const_iterator upper_bound (const key_type& k) const;
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
	pair<iterator,iterator> equal_range (const key_type& k);

	// allocator
	allocator_type get_allocator() const { return _alloc; };

};

}

#endif