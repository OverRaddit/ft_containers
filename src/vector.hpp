#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
# include <vector>
# include <iostream>

# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include <stdexcept> // out of range

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{

// Member Type
public:
	typedef Alloc										allocator_type;
	// 어떻게 정의해야할지 모르겠다.
	typedef typename allocator_type::size_type			size_type; // non-negative value of difference_type

	typedef T											value_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	//iterator 4
	// iter, const_iter 타입정의 이해안됨.
	typedef pointer													iterator;
	typedef const_pointer											const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

	// Member Variable
	pointer				_begin;
	pointer				_end;
	pointer				_end_cap;
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
		_end = _begin;
		_end_cap = _begin + n;

		// construct
		for( ; _temp != _end; _temp++)
		// 	_alloc.construct(_temp, val);

		//append() ->   초기화값?
	};
	template <class InputIterator>
		vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type hint = 0)
	//: _end(last - first), _end_cap(last - first)
	{
		difference_type n = last - first;

		// allocate
		_begin = _alloc.allocate(n);
		pointer _temp = _begin;
		_end = _begin + n;
		_end_cap = _begin + n;

		// _end보다 커지면?
		for( ; first != last; first++)
			_alloc.construct(_temp++, *first);
	};
	vector (const vector& x)
	{
		*this = x;
	};

	~vector ()
	{
		if (!empty())
			free_range(_begin, _end);
	}

	// 다시 구현. 매우문제많음.
	vector& operator= (const vector& x)
	{
		// realloc
		if (size() < x.size())
		{
			difference_type n = x.size();
			_begin = _alloc.allocate(n);
			_end = _begin + n;
			_end_cap = _end;
		}

		// construct with copy
		pointer dest = _begin;
		pointer src = x._begin;
		for( ; dest != _end; dest++)
			_alloc.construct(dest, *src++);
		// construct with default
		for( ; dest != _end_cap; dest++)
			_alloc.construct(dest, value_type());

		// free current data
		if (!empty())
			free_range(_begin, _end);

		return *this;
	};

	// Iterators ================================================================================
	iterator begin() { return _begin; };
	const_iterator begin() const { return const_cast<iterator>(_begin); };

	iterator end() { return _end; };
	const_iterator end() const { return const_cast<iterator>(_end); };

	reverse_iterator rbegin() { return reverse_iterator(_begin); };
	const_reverse_iterator rbegin() const { return const_cast<reverse_iterator>(_begin); };

	reverse_iterator rend() { return reverse_iterator(_end); };
	const_reverse_iterator rend() const { return const_cast<reverse_iterator>(_end); };
	// ==========================================================================================

	// Capacity ================================================================================
	size_type size() const { return _end - _begin; };
	size_type max_size() const { _alloc.max_size(); };
	// 포인터 재재할할당당시  포포이이ㅏㅏㄴㄴ터  값  최최신신화화할할것것.
	void resize (size_type n, value_type val = value_type())
	{
		if (n > capacity())
		{
			append(n);
		}
		else if (n < size())
		{
			// n 초과의 원소에 대해 remove & destroy
			pointer new_end = _begin + n;
			destroy_range(new_end, _end);
			_end = new_end;
		}
		// capacity안에서 값 채우기
		else if (n > size())
		{
			pointer new_end = _begin + n;

			// copy
			while(_end != new_end)
				*_end++ = val; // end에 val값을 넣는다.
			// already update end
		}
	};
	size_type capacity() const { return _end_cap - _begin; };
	bool empty() const { return _end == _begin; };

	void reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("vector");
		if (n <= capacity())
			return ;

		resize(n);
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

// Gshim's work
	// 현재 벡터의 용량을 확장한다.
	void append(size_type n)
	{
		pointer new_begin;
		pointer new_end;
		pointer new_end_cap;

		// reallocate
		allocator_type temp;
		pointer iter = temp.allocate(n);
		new_begin = iter;
		new_end = iter + size();
		new_end_cap = iter + n;

		// construct with copy
		consturct_range_with_range(new_begin, new_end, _begin, _end)
		// construct with val
		consturct_range_with_value(iter, new_end_cap, value_type());

		// delete old data
		if (!empty())
			free_range(_begin, _end)

		// update member
		_begin = new_begin;
		_end = new_end;
		_end_cap = new_end_cap;
	};
	// b~e 구간을 srcb~srce구간을 복사하여 초기화 한다.
	// srce가 필요없다.
	void consturct_range_with_range(pointer b, pointer e, pointer srcb,
		pointer srce)
	{
		if (e - b != srce - srcb)
		{
			std::cerr << "Something's wrong with consturct_range_with_range()" << std::endl;
		}
		for(;b != e;b++)
			_alloc.construct(b, srcb++);
	};
	// b~e구간을 val값으로 초기화한다.
	void consturct_range_with_value(pointer b, pointer e, value_type val = value_type())
	{
		for(;b != e;b++)
			_alloc.construct(b, val);
	};
	void copy_range(pointer b, pointer e, bool is_init)
	{
		for(;b != e;b++)
			_alloc.destroy(b);
	};
	void destroy_range(pointer b, pointer e)
	{
		for(;b != e;b++)
			_alloc.destroy(b);
	};
	void free_range(pointer b, pointer e)
	{
		size_type	len = e - b;

		destroy_range(b, e);
		_alloc.deallocate(b, len);
	};
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
