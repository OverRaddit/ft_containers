#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
# include <vector>
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include <stdexcept> // out of range

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{

// Member Type
public:
	typedef Alloc										allocator_type;
	typedef typename allocator_type::size_type			size_type; // non-negative value of difference_type

	typedef T											value_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	//iterator 4
	// 이 4가지 이터레이터의 타입을 어떻게 명시해줘야 할지 모르겠다.
	// typedef std::iterator<ft::random_access_iterator_tag, T,
	// 	typename allocator_type::difference_type, pointer, reference>		iterator;

	// iter, const_iter 타입정의 이해안됨.
	typedef pointer													iterator;
	typedef const_pointer											const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
	// ?
	// 어떻게 정의해야할지 모르겠다.

	// Member Variable
	pointer				_begin;
	pointer				_end;
	pointer				_end_cap;			// ??
	allocator_type		_alloc;

// Member functions
	// Constructor
	explicit vector (const allocator_type& alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc) {};
	explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type())
		: _alloc(alloc)
	{
		pointer _temp;

		// allocate
		_begin = _alloc.allocate(n); // hint??
		_temp = _begin;
		_end = _begin + n;
		_end_cap = _begin + n; // ?

		// construct
		for( ; _temp != _end; _temp++)
			_alloc.construct(_temp, val);
	};
	// template <class InputIterator>
    //      vector (InputIterator first, InputIterator last,
    //              const allocator_type& alloc = allocator_type())
	// {

	// };
	vector (const vector& x)
		: _begin(x.begin()), _end(x.end()), _end_cap(0), _alloc(x.get_allocator()) {};

	// Iterators ================================================================================
	iterator begin() { return _begin; };
	const_iterator begin() const { return const_cast<iterator>(_begin); };

	iterator end() { return _end; };
	const_iterator end() const { return const_cast<iterator>(end); };

	reverse_iterator rbegin() { return reverse_iterator(_begin); };
	const_reverse_iterator rbegin() const { return const_cast<reverse_iterator>(_begin); };

	reverse_iterator rend() { return reverse_iterator(_end); };
	const_reverse_iterator rend() const { return const_cast<reverse_iterator>(_end); };
	// ==========================================================================================

	// Capacity ================================================================================
	size_type size() const { return _end - _begin; };
	size_type max_size() const;	// ??
	void resize(size_type n, value_type val = value_type())
	{

	};
	size_type capacity() const { return _end_cap; };
	bool empty() const { return _end == _begin; };

	void reserve(size_type n)
	{
		if ( n > capacity() )
		{
			allocator_type new_alloc;
			pointer new_begin;
			pointer temp;

			// reallocate
			new_begin = new_alloc.allocate(n);
			temp = _alloc.address();
			// copy
			for(;temp != _end;)
			{
				temp++ = new_begin++;
			}
			_alloc.deallocate();
		}
	};
	// ==========================================================================================

	// Element access

	// random access iterator : indexing
	// other : ++ one by one
	reference operator[] (size_type n) { return _begin[n]; };
	const_reference operator[] (size_type n) const { return const_cast<const_reference>(_begin[n]); };

	reference at (size_type n) {
		if (size() > n)
			throw std::out_of_range("vector");
		return _begin[n];
	};
	const_reference at (size_type n) const {
		if (size() > n)
			throw std::out_of_range("vector");
		return const_cast<const_reference>(_begin[n]);
	};
	reference front() { return *_begin; };
	const_reference front() const { return const_cast<const_reference>(*_begin); };
	// access end -1. if not empty _ if empty, undefined
	reference back() { return *(_end - 1); };
	const_reference back() const { return const_cast<const_reference>(_end - 1); };
	// ==========================================================================================

	// Modifiers
	template <class InputIterator>
	void assign (InputIterator first, InputIterator last);
	void assign (size_type n, const value_type& val);
	void push_back (const value_type& val);
	void pop_back();
	iterator insert (iterator position, const value_type& val);
	void insert (iterator position, size_type n, const value_type& val);
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);
	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);
	void swap (vector& x);
	void clear();
	// ==========================================================================================

	// Allocator
	allocator_type get_allocator() const { return _alloc; };
	// ==========================================================================================
};

// Non-member function overloads
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

}
#endif
