#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include <stdexcept> // out of range
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "vector_iterator.hpp"

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
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	// iterator 4
	typedef ft::vector_iterator<T> iterator;
	typedef ft::vector_iterator<const T> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

	// Member Variable
	pointer _begin;
	pointer _end;
	pointer _end_cap;
	allocator_type _alloc;

	// Member functions
	// Constructor
	vector(const allocator_type &alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc){};
	vector(size_type n, const value_type &val = value_type(),
			const allocator_type &alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc)
	{
		// allocate
		reserve(n);

		// construct with value
		_end = _begin + n;
		construct_range_with_value(_begin, _end, val);
	};
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type hint = 0)
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc)
	{
		// allocate
		reserve(last - first);

		// init
		for (; first != last; first++)
			_alloc.construct(_end++, *first);
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

	vector &operator=(const vector &x)
	{
		// 할당된 것이 있을때만 free한다.
		if (_begin != _end_cap)
			free_vector();

		// x의 모든 원소를 저장할 용량이 있는가?
		if (capacity() < x.size())
		{
			size_type new_size = (capacity() * 2 < x.size()) ? x.size() : capacity() * 2;
			reserve(new_size);
		}

		// construct with copy
		_end = _begin + x.size();
		construct_range_with_range(_begin, _end, x._begin, x._end);

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
			construct_range_with_value(_end, _begin + n, val);
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

		// resize는 할당 + 초기화까지 같이 시켜줌
		// reserve는 할당만 하고 초기화는 하지 않음.
		// 즉, 둘은 다른 연산임.
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
	const_reference front() const { return const_cast<const_reference>(*_begin); };
	// access end -1. if not empty _ if empty, undefined
	reference back() { return *(_end - 1); };
	const_reference back() const { return const_cast<const_reference>(_end - 1); };
	// ==========================================================================================

	// Modifiers
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type hint = 0)
	{
		size_type n = last - first;

		// destroy current data
		clear();

		// deallocate & reallocate
		if (capacity() < n)
		{
			size_type new_size = (capacity() * 2 < n) ? n : capacity() * 2;
			reserve(new_size);
		}

		// construct with value
		construct_range_with_range(_begin, _begin + n, first.base(), last.base());
		_end += n;
	};
	void assign(size_type n, const value_type &val)
	{
		// destroy current data
		clear();

		// deallocate & reallocate
		if (capacity() < n)
		{
			size_type new_size = (capacity() * 2 < n) ? n : capacity() * 2;
			reserve(n);
		}

		// construct with value
		construct_range_with_value(_begin, _begin + n, val);
		_end += n;
	};

	void push_back(const value_type &val) { insert(_end, val); };
	// empty에서 호출하는건 정의되지않은 행동이다.
	void pop_back() { _alloc.destroy(--_end); };

	iterator insert(iterator position, const value_type &val)
	{
		// if vector is full, append twice or greater
		if (_end == _end_cap)
		{
			// reallocate
			size_type new_cap = (size() == 0) ? 1 : capacity() * 2;
			pointer new_begin = _alloc.allocate(new_cap);
			pointer new_end = new_begin + size() + 1;
			pointer new_end_cap = new_begin + new_cap;
			pointer new_position = new_begin + (position.base() - _begin);

			construct_range_with_range(new_begin, new_position, _begin, position.base());
			_alloc.construct(new_position, val);
			construct_range_with_range(new_position + 1, new_end, position.base(), _end);

			// dedalloc & destroy
			if (capacity() != 0)
			{
				free_vector();
			}

			// update member
			_begin = new_begin;
			_end = new_end;
			_end_cap = new_end_cap;

			return new_position;
		}
		else // 공간이 충분하다. shift + insert
		{
			shift_right(position.base(), _end, position.base() + 1, _end + 1, _end);
			*position = val;

			// update member
			_end = _end + 1;

			return position;
		}
	};
	void insert(iterator position, size_type n, const value_type &val)
	{
		pointer pos = position.base();

		if (_end + n > _end_cap) // 공간이 부족 -> 재할당
		{
			// 생각해볼것....!
			size_type new_cap = (capacity() * 2 > n) ? 2 * capacity() + (size() == 0) : size() + (size() == 0) + n;
			// reallocate
			pointer new_begin = _alloc.allocate(new_cap);
			pointer new_end = new_begin + size() + n;
			pointer new_end_cap = new_begin + new_cap;
			pointer new_position = new_begin + (pos - _begin);

			construct_range_with_range(new_begin, new_position, _begin, pos);
			// insert
			construct_range_with_value(new_position, new_position + n, val);
			// 구간 모두 고칠것
			construct_range_with_range(new_position + n, new_end, pos, _end);

			// dedalloc & destroy
			if (capacity() != 0)
			{
				free_vector();
			}

			// update member
			_begin = new_begin;
			_end = new_end;
			_end_cap = new_end_cap;
		}
		else // 공간이 충분하다.
		{
			// shift
			shift_right(pos, _end, pos + n, _end + n, _end);

			// insert
			//  destroy_range(pos, _end); // _end전까진 원소 destroy
			//  construct_range_with_value(pos, _end + n); // construct
			for (; pos != _end; pos++) // _end전까진 값 대입
				*pos = val;
			for (; pos != _end + n; pos++) // _end+n까진 construct
				_alloc.construct(pos, val);

			// update member
			_end = _end + n;
		}
	};
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type hint = 0)
	{
		size_type n = last - first;
		// iterator_traits<InputIterator>::difference_type Itern = last - first;
		pointer pos = position.base();

		if (_end + n > _end_cap) // 공간이 부족 -> 재할당
		{
			std::cout << "not Enough space!" << std::endl;
			// 생각해볼것....!
			size_type new_cap = (capacity() * 2 > n) ? 2 * capacity() + (size() == 0) : size() + (size() == 0) + n;
			// reallocate
			pointer new_begin = _alloc.allocate(new_cap);
			pointer new_end = new_begin + size() + n;
			pointer new_end_cap = new_begin + new_cap;
			pointer new_position = new_begin + (pos - _begin);

			try
			{
				//std::copy_backward();
				//construct_range_with_range_templateVer(new_position, new_position + n, first, last);
				std::uninitialized_copy(first, last, new_position);


				std::uninitialized_copy(_begin, pos, new_begin);
				//construct_range_with_range(new_begin, new_position, _begin, pos);
				std::uninitialized_copy(pos, _end, new_position + n);
				//construct_range_with_range(new_position + n, new_end, pos, _end);

				// insert
				// construct_range_with_range함수를 쓰면 서로 다른 데이터를 가리키는 pointer를 사용하기 때문에 컴파일 에러가 발생한다.
				// first, last에 .base()를 호출하면 타입호환이 안됨.... 왜안될까
				// construct_range_with_range(new_position, new_position + n, (pointer)first.base(), (pointer)last.base());


				// vector x(first, last);
				// std::cout << "X created!" << std::endl;
				// construct_range_with_range(new_position, new_position + n, x.begin().base(), x.end().base());
				// std::cout << "construct_range_with_range!" << std::endl;

				// dedalloc & destroy
				if (capacity() != 0)
				{
					free_vector();
				}

				// update member
				_begin = new_begin;
				_end = new_end;
				_end_cap = new_end_cap;
			}
			catch (...)
			{
				_alloc.deallocate(new_begin, new_end_cap - new_begin);
				std::cout << "Error while insert(range)! delete these elements..." << std::endl;
				// destroy_range(new_position, new_position + n);
				// construct_range_with_range(new_position, new_position + n, new_position + n, _end);
				// erase(iterator(new_position), iterator(new_position + n));
				throw;
			}
		}
		else // 공간이 충분하다.
		{
			std::cout << "Enough space!" << std::endl;
			// shift
			shift_right(pos, _end, pos + n, _end + n, _end);

			// insert
			for (; pos != _end; pos++) // _end전까진 값 대입
				*pos = *first++;
			for (; pos != _end + n; pos++) // _end+n까진 construct
				_alloc.construct(pos, *first++);

			// update member
			_end = _end + n;
		}
	};
	iterator erase(iterator position)
	{
		// position 원소 삭제
		_alloc.destroy(position.base());
		// shift left
		// 삭제한 원소 다음 ~ 마지막원소 전부 1 칸씩 땡기기.
		// 1 2 3 4 5
		// 1 2 4 5
		// 새 end로 최신화.
		construct_range_with_range(position.base(), --_end, position.base() + 1, _end);

		return position;
	};
	iterator erase(iterator first, iterator last)
	{
		size_type len = last - first;

		// position 원소 삭제
		destroy_range(first.base(), last.base());
		// 삭제한 원소 다음 ~ 마지막원소 전부 len 칸씩 땡기기.
		// 1 2 3 4 5
		// 1 2 5
		construct_range_with_range(first.base(), _end - len, first.base() + len, _end);

		// 새 end로 최신화.
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
		construct_range_with_range(new_begin, new_end, _begin, _end);

		// delete old data
		if (capacity() != 0)
			free_vector();

		// update member
		_begin = new_begin;
		_end = new_end;
		_end_cap = new_end_cap;
	};
	// =========================================================================

	// b~e 구간을 srcb~srce구간을 복사하여 초기화 한다.
	// srce가 필요없다.
	void construct_range_with_range(pointer b, pointer e, pointer srcb,
									pointer srce)
	{
		if (e - b != srce - srcb)
		{
			std::cerr << "Something's wrong with consturct_range_with_range()" << std::endl;
		}
		for (; b != e; b++)
		{
			_alloc.construct(b, *srcb++);
		}
	};
	template <class InputIterator>
	void construct_range_with_range_templateVer(pointer b, pointer e, InputIterator srcb, InputIterator srce)
	{
		// if (e - b != srce - srcb)
		// {
		// 	std::cerr << "Something's wrong with consturct_range_with_range()" << std::endl;
		// }
		try
		{
			size_type a = e - b;
			for (; b != e || srcb != srce; b++)
			{
				new(b) value_type(*srcb++);
				//_alloc.construct(b, *srcb++);
			}
		}
		catch(...)
		{
			// destroy
			for (; b != e || srcb != srce; b++)
			{
				new(b) value_type(*srcb++);
				//_alloc.construct(b, *srcb++);
			}
			throw;
		}


	};
	// =========================================================================

	// b~e구간을 val값으로 초기화한다.
	void construct_range_with_value(pointer b, pointer e, value_type val = value_type())
	{
		for (; b != e; b++)
		{
			_alloc.construct(b, val);
		}
	};
	// b~e구간을 srcb~srce 구간의 값으로 복사한다.
	void copy_range_with_range(pointer b, pointer e, pointer srcb,
								pointer srce)
	{
		if (e - b != srce - srcb)
		{
			std::cerr << "Something's wrong with consturct_range_with_range()" << std::endl;
		}
		for (; b != e; b++)
			*b = *srcb++;
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
	// srcb~srce => destb~deste, cap을 기준으로 대입/초기화가 갈린다.
	void shift_right(pointer srcb, pointer srce, pointer destb, pointer deste,
						pointer cap)
	{
		// 역방향으로 값을 넣어야 한다.
		// [ ) 기준을 역으로 접근하기 때문에 기존 방식과 아주약간 다른 것에 유의하자.
		for (; srce != cap; --srce)
			_alloc.construct(srce, *--deste);

		for (; srce != srcb; --srce)
			*srce = *--deste;
		*srce = *--deste;
	};
	// ==========================================================================================
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
