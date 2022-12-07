#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
#include <vector>

template <class T, class Alloc = std::allocator<T>>
class vector
{

// Member Type
typedef T														value_type;
typedef typename Alloc::value_type								allocator_type;
typedef typename allocator_type::reference						reference;
typedef typename allocator_type::const_reference				const_reference;
typedef typename allocator_type::pointer						pointer;
typedef typename allocator_type::const_pointer					const_pointer;
//iterator 4
// 이 4가지 이터레이터의 타입을 어떻게 명시해줘야 할지 모르겠다.
typedef typename T											iterator;
typedef typename T											const_iterator;
typedef typename T											reverse_iterator;
typedef typename T											const_reverse_iterator;

typedef typename iterator_traits<iterator>::difference_type		difference_type;
// ?
// 어떻게 정의해야할지 모르겠다.
typedef typename iterator_traits<iterator>::size_type		size_type; // non-negative value of difference_type



// Member functions
	vector(/* args */);
	~vector();

	// Iterators
	iterator begin() {

	}
	const_iterator begin() const;

	// Capacity
	size_type size() const;
	size_type max_size() const;
	void resize(size_type n, value_type val = value_type());
	size_type capacity() const;
	bool empty() const;
	void reserve(size_type n);

	// Element access
	reference operator[] (size_type n);
	const_reference operator[] (size_type n) const;
	reference at (size_type n);
	const_reference at (size_type n) const;
	reference front();
	const_reference front() const;
	reference back();
	const_reference back() const;

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

	// Allocator
	allocator_type get_allocator() const;
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

#endif
