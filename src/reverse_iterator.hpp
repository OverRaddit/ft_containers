#ifndef FT_REVERSE_ITERATOR
#define FT_REVERSE_ITERATOR

#include "iterator_traits.hpp"

namespace ft
{

template <class Iterator>
class reverse_iterator
{
public:
// ================================================================================
// Member Types
// ================================================================================
typedef Iterator													iterator_type;
typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
typedef typename ft::iterator_traits<Iterator>::reference			reference;

// Member Variable
iterator_type iter;

// ================================================================================
// Member Functions
// ================================================================================

//constructors
reverse_iterator() : iter() {};

explicit reverse_iterator( iterator_type x ) : iter(x) {};

template< class U >
reverse_iterator( const reverse_iterator<U>& other ) : iter(other.base()) {};

iterator_type base() const
{
	return iter;
};

template <class U>
reverse_iterator& operator=(const reverse_iterator<U>& other)
{
	iter = other.base();
	return *this;
};

reference operator*() const
{
	iterator_type copy = iter;
	return *--copy;
	//return *(iter - 1);
};
reverse_iterator operator+(difference_type n) const
{
	return reverse_iterator(iter - n);
};
reverse_iterator& operator++(){ --iter; return *this;};
reverse_iterator operator++(int) {
	reverse_iterator copy(*this);
	iter--;
	return copy;
};
reverse_iterator& operator+=(difference_type n) { iter -= n; return *this; };
reverse_iterator operator-(difference_type n) const { return reverse_iterator(iter + n); };
reverse_iterator& operator--() { ++iter; return *this;};
reverse_iterator operator--(int) {
	reverse_iterator copy(*this);
	iter++;
	return copy;
};
// a->x;
// *a.x
reverse_iterator& operator-=(difference_type n) { iter += n; return *this; };
pointer operator->() const { return &(operator*()); };
reference operator[](difference_type n) const { return *(*this + n); };
};

// ================================================================================
// Non-member function overloads
// ================================================================================
// 관계연산
template <class T, class U> bool operator== (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{return lhs.base() == rhs.base();};

template <class T, class U> bool operator!= (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{
	return lhs.base() != rhs.base();
};

// 부등호방향도 reverse다.
template <class T, class U> bool operator< (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{return lhs.base() > rhs.base();};
template <class T, class U> bool operator<= (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{return lhs.base() >= rhs.base();};
template <class T, class U> bool operator> (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{return lhs.base() < rhs.base();};
template <class T, class U> bool operator>= (const reverse_iterator<T>& lhs,
	const reverse_iterator<U>& rhs)
{return lhs.base() <= rhs.base();};

// r_iter + 1은 멤버함수로 가능 but 1 + r_iter는 불가능
template<class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
	const reverse_iterator<Iter>& rev_it)
{ return reverse_iterator<Iter>(rev_it.base() - n); };

// 두 iter의 거리 계산
// reverse 이기 때문에 방향이 반대가 된다. 유의할것.
template<class T, class U>
typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T>&lhs,
	const reverse_iterator<U>& rhs)
{
	return rhs.base() - lhs.base();
};

}
#endif