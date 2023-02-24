#ifndef FT_VECTOR
#define FT_VECTOR

# include <iostream>
# include <algorithm>
# include <stdexcept> // out of range
# include <iterator>
# include "utility.hpp"
# include "vector_iterator.hpp"

namespace ft
{

template <class T, class Alloc = std::allocator<T> >
class vector
{
	// Member Type
public:
	typedef Alloc allocator_type;
	// 어떻게 정의해야할지 모르겠다.
	typedef typename allocator_type::size_type size_type; // non-negative value of difference_type

	typedef T value_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	// iterator
	typedef ft::v__iterator<pointer>					iterator;
	typedef ft::v__iterator<const_pointer>				const_iterator;
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

	// Member Variable
	pointer _begin;
	pointer _end;
	pointer _end_cap;
	allocator_type _alloc;

	// Member functions
	// Constructor
	explicit vector(const allocator_type &alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc){};
	explicit vector(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc)
	{
		reserve(n);
		_end = _begin + n;
		std::uninitialized_fill(_begin, _end, val);
	};
	template <class InputIterator>
	vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
			InputIterator last, const allocator_type &alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc)
	{
		//insert(_begin, first, last);

		size_type n = std::distance(first, last);
		// allocate
		reserve(n);
		// init
		// for (; first != last; first++)
		// 	_alloc.construct(_end++, *first);
		// 다른타입을 가리키는 이터레이터인 경우 릭이 나는 경우가 있어 대체한다.
		try
		{
			/* code */
			std::uninitialized_copy(first, last, _end);
			_end += n;
		}
		catch(...)
		{
			while(_begin != _end)
			{
				_alloc.destroy(_begin++);
			}
			throw;
		}

	};
	vector(const vector &x)
		: _begin(0), _end(0), _end_cap(0), _alloc(allocator_type())
	{
		*this = x;
	};

	~vector()
	{
		free_vector();
	}

protected:
	//  Precondition:  __new_size > capacity()
	size_type __recommend(size_type __new_size) const
	{
		const size_type __ms = max_size();
		// max_size()이상의 재할당은 불가능
		if (__new_size > __ms)
			throw std::length_error("vector");
		const size_type __cap = capacity();
		// 현 용량의 2배가 max_size()를 넘어가면 max_size()로 할당한다.
		if (__cap >= __ms / 2)
			return __ms;
		// 현재용량의 2배와 __new_size중 더 큰 값으로 재할당한다.
		return std::max(2*__cap, __new_size);
	}

public:
	vector &operator=(const vector &x)
	{
		if (_begin != _end_cap)
			free_vector();
		if (capacity() < x.size())
		{
			//size_type new_size = (capacity() * 2 < x.size()) ? x.size() : capacity() * 2;
			size_type new_size = __recommend(x.size());
			reserve(new_size);
		}
		//reserve(__recommend(x.size()));
		_end = _begin + x.size();
		std::uninitialized_copy(x._begin, x._end, _begin);

		return *this;
	};

	// Iterators ================================================================================
	iterator begin() { return iterator(_begin); };
	const_iterator begin() const { return const_iterator(_begin); };
	iterator end() { return iterator(_end); };
	const_iterator end() const { return const_iterator(_end); };
	reverse_iterator rbegin() { return reverse_iterator(end()); };
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); };
	reverse_iterator rend() { return reverse_iterator(begin()); };
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); };
	// ==========================================================================================

	// Capacity ================================================================================
	size_type size() const { return _end - _begin; };
	size_type max_size() const { return _alloc.max_size(); };

	// 원소의 개수를 조정한다.
	void resize(size_type n, value_type val = value_type())
	{
		if (n == size())
			return;

		if (n > size())
		{
			if (n > capacity())
			{
				size_type new_size = (n > capacity() * 2) ? n : capacity() * 2;
				reserve(new_size);
			}
			std::uninitialized_fill(_end, _begin + n, val);
			//construct_range_with_value(_end, _begin + n, val);
		}
		else if (n < size())
			destroy_range(_begin + n, _end);
		_end = _begin + n;
	};
	size_type capacity() const { return _end_cap - _begin; };
	bool empty() const { return _end == _begin; };

	void reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("vector");
		if (n <= capacity())
			return;

		append(n);
	};
	// ==========================================================================================

	// Element access

	// random access iterator : indexing
	// other : ++ one by one
	reference operator[](size_type n) { return _begin[n]; };
	const_reference operator[](size_type n) const { return const_cast<const_reference>(_begin[n]); };

	reference at(size_type n)
	{
		if (size() < n)
			throw std::out_of_range("vector");
		return _begin[n];
	};
	const_reference at(size_type n) const
	{
		if (size() < n)
			throw std::out_of_range("vector");
		return const_cast<const_reference>(_begin[n]);
	};
	reference front() { return *_begin; };
	const_reference front() const { return *_begin; };
	reference back() { return *(_end - 1); };
	//const_reference back() const { return const_cast<const_reference>(_end - 1); };
	const_reference back() const { return *(_end - 1); };
	// ==========================================================================================

	// Modifiers
	template <class InputIterator>
	void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
					InputIterator last)
	{
		// distance를 바로 구하지 않고 다른 방법있나????
		// insert를 호출할까?
		size_type n = std::distance(first, last);
		clear();
		if (capacity() < n)
			reserve(__recommend(n));
		std::uninitialized_copy(first, last, _begin);
		_end += n;
	};
	void assign(size_type n, const value_type &val)
	{
		clear();
		if (capacity() < n)
			reserve(__recommend(n));
		std::uninitialized_fill(_begin, _begin + n, val);
		_end += n;
	};
	void push_back(const value_type &val) { insert(_end, val); };
	void pop_back() { _alloc.destroy(--_end); };
	iterator insert(iterator position, const value_type &val)
	{
		difference_type len = position.base() - _begin;
		// ㅌㅔ스트기마다 기준다름.
		if (_end == _end_cap)
			reserve(__recommend(capacity() + 1));
		//reserve(__recommend(capacity() + 1));

		// pos ~ end 를 우측으로 n 이동하여 construct.
		pointer end = _end;
		pointer pos = _begin + len;
		while(end != pos)
		{
			--end;
			_alloc.construct(end + 1, *end);
			_alloc.destroy(end);
		}
		_alloc.construct(pos, val);
		_end++;

		return iterator(pos);
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		difference_type len = position - begin();
		// if (size() + n > capacity())
		// 	reserve(__recommend(size() + n));
		reserve(__recommend(size() + n));

		// pos ~ end 를 우측으로 n 이동하여 construct.
		pointer pos = _begin + len;
		pointer end = _end;
		while(end != pos)
		{
			--end;
			_alloc.construct(end + n, *end);
			_alloc.destroy(end);
		}
		std::uninitialized_fill(pos, pos + n, val);
		_end = _end + n;
	};

	// 대입할 수 없는 이터레이터 범위를 억지로 대입하는 케이스에서,, 대입을 못해도 미리 할당은 해놓는 문제 발생.
	// Input_iter, Bidir_iter로 각각 구현하면 어떨까?

	// input
	// template <class InputIterator>
	// void insert(iterator position,
	// 				InputIterator first, InputIterator last)
	// {
	// 	difference_type offset = position - begin();
	// 	pointer pos;
	// 	for (int i = 0; first != last; ++first, ++i) {
	// 		pos = _begin + offset;
	// 		//std::cout << *first << std::endl;
	// 		insert(pos + i, *first);
	// 	}
	// };

	// bi
	template <class InputIterator>
	void insert(iterator position,
					typename ft::enable_if<
						!ft::is_integral<InputIterator>::value, InputIterator
					>::type first, InputIterator last)
	{
		difference_type len = position - begin();
		//size_type n = std::distance(first, last);
		try
		{
			vector copy(first, last);

			// if type not match, this code will blow this function.
			// vector x(1);
			// std::uninitialized_copy(copy.begin(), copy.end(), x.begin());
			// _alloc.construct(it.base(),  *copy.begin());
			//*it = copy.begin();

			size_type n = copy.size();
			// if (size() + n > capacity())
			// 	reserve(__recommend(size() + n));
			reserve(__recommend(size() + n));

			// pos ~ end 를 우측으로 n 이동하여 construct.
			pointer pos = _begin + len;
			pointer end = _end;
			while(end != pos)
			{
				--end;
				_alloc.construct(end + n, *end);
				_alloc.destroy(end);
			}
			std::uninitialized_copy(copy.begin(), copy.end(), pos);
			_end = _end + n;
		}
		catch(...)
		{
			throw;
		}
	};

	iterator erase(iterator position)
	{
		_alloc.destroy(position.base());
		std::uninitialized_copy(position.base() + 1, _end--, position.base());

		return position;
	};
	iterator erase(iterator first, iterator last)
	{
		size_type len = last - first;

		destroy_range(first.base(), last.base());
		std::uninitialized_copy(first.base() + len, _end, first.base());
		_end -= len;

		return first;
	};
	void swap(vector &x) // vector x는 *this와 같은 템플릿 인자를 공유하는 건가...?
	{
		pointer temp_begin = _begin;
		pointer temp_end = _end;
		pointer temp_end_cap = _end_cap;

		_begin = x._begin;
		_end = x._end;
		_end_cap = x._end_cap;

		x._begin = temp_begin;
		x._end = temp_end;
		x._end_cap = temp_end_cap;
	};
	void clear()
	{
		// destroy all
		destroy_range(_begin, _end);
		// update member
		_end = _begin;
	};
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
		std::uninitialized_copy(_begin, _end, new_begin);

		// delete old data
		if (capacity() != 0)
			free_vector();

		// update member
		_begin = new_begin;
		_end = new_end;
		_end_cap = new_end_cap;
	};

	void destroy_range(pointer b, pointer e)
	{
		if (b == e)
			return;
		for (; b != e; b++)
		{
			_alloc.destroy(b);
			// std::cout << "destroy one item : " << b << std::endl;
		}
	};
	void free_vector()
	{
		if (!empty())
			destroy_range(_begin, _end);
		if (_begin != 0)
		{
			_alloc.deallocate(_begin, _end_cap - _begin);
		}
		_begin = 0;
		_end = 0;
		_end_cap = 0;
	}
};

// Non-member function overloads
template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;

	// compare each element
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
};
template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs == rhs);
};
template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										rhs.end());
};
template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (lhs < rhs) || (lhs == rhs);
};

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return !(lhs == rhs) && !(lhs < rhs);
};

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
{
	return (lhs == rhs) || !(lhs < rhs);
};

template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); };

}
#endif
