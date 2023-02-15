#ifndef FT_VECTOR_ITERATOR
#define FT_VECTOR_ITERATOR

# include <iterator>
# include "iterator_traits.hpp"

namespace ft
{

// template <class T>
// class vector_iterator;

// template <class T>
// class vector_const_iterator;

// // 해당 이터레이터를 태그이터레이터로 감싸면?

// // const_iterator
// template <class T>
// class vector_const_iterator : public ft::iterator<std::random_access_iterator_tag, T>
// {
// public:
// 	friend class vector_iterator<T>;

// 	typedef typename vector_const_iterator::value_type			value_type;
// 	typedef typename vector_const_iterator::difference_type		difference_type;
// 	typedef typename vector_const_iterator::pointer				pointer;
// 	typedef typename vector_const_iterator::reference			reference;
// 	typedef typename vector_const_iterator::iterator_category	iterator_category;
// 	typedef pointer												iterator_type;

// 	pointer p;

// 	pointer base() const { return p; }
// 	pointer base() { return p; }

// 	vector_const_iterator() :p(0) {}
// 	vector_const_iterator(pointer x) :p(x) {}
// 	vector_const_iterator(const vector_const_iterator<T>& mit) : p(mit.p) {}
// 	vector_const_iterator(const vector_iterator<T>& mit) : p(mit.p) {}

// 	// const_iter(iter)
// 	vector_const_iterator& operator++() { ++p;return *this; }
// 	vector_const_iterator operator++(int) {
// 		vector_const_iterator tmp(*this);
// 		operator++();
// 		return tmp;
// 	}
// 	vector_const_iterator& operator--() { --p;return *this; }
// 	vector_const_iterator operator--(int) {
// 		vector_const_iterator tmp(*this);
// 		operator--();
// 		return tmp;
// 	}
// 	bool operator==(const vector_const_iterator& rhs) const { return p==rhs.p; }
// 	bool operator!=(const vector_const_iterator& rhs) const { return p!=rhs.p; }
// 	reference operator*() const { return *p; }
// 	pointer operator->() const { return p; }

// 	vector_const_iterator& operator+=(difference_type n) { p += n; return *this; };
// 	vector_const_iterator& operator-=(difference_type n) { p -= n; return *this; };

// 	vector_const_iterator operator+(difference_type n) const
// 	{ return vector_const_iterator(p + n); };
// 	vector_const_iterator operator-(difference_type n) const
// 	{ return vector_const_iterator(p - n); };

// 	difference_type operator-(vector_iterator<T> x) const
// 	{ return p - x.base(); };
// 	reference operator[](difference_type n) const { return *(p + n); };

// };

// template<class Iter>
// vector_const_iterator<Iter> operator+(typename vector_const_iterator<Iter>::difference_type n,
// 	const vector_const_iterator<Iter>& rev_it)
// { return vector_const_iterator<Iter>(rev_it.p - n); };

// template<class Iter>
// typename vector_const_iterator<Iter>::difference_type operator-(const vector_const_iterator<Iter>&lhs,
// 	const vector_const_iterator<Iter>& rhs)
// { return lhs.p - rhs.p; };

// // vector's iterator
// template <class T>
// class vector_iterator : public ft::iterator<std::random_access_iterator_tag, T>
// {
// public:
// 	friend class vector_const_iterator<T>;
// 	typedef typename vector_iterator::value_type			value_type;
// 	typedef typename vector_iterator::difference_type		difference_type;
// 	typedef typename vector_iterator::pointer				pointer;
// 	typedef typename vector_iterator::reference				reference;
// 	typedef typename vector_iterator::iterator_category		iterator_category;
// 	typedef pointer											iterator_type;

// 	pointer p;

// 	pointer base() const { return p; }
// 	pointer base() { return p; }

// 	vector_iterator() :p(0) {}
// 	vector_iterator(pointer x) :p(x) {}
// 	vector_iterator(const vector_iterator& mit) : p(mit.p) {}

// 	// const_iter(iter) child A(from B) parent B -> A a,b; a == x B x,y;

// 	vector_iterator& operator++() {++p;return *this;}
// 	vector_iterator operator++(int) {
// 		vector_iterator tmp(*this);
// 		operator++();
// 		return tmp;
// 	}
// 	vector_iterator& operator--() {--p;return *this;}
// 	vector_iterator operator--(int) {
// 		vector_iterator tmp(*this);
// 		operator--();
// 		return tmp;
// 	}
// 	bool operator==(const vector_iterator& rhs) const {return p==rhs.p;}
// 	bool operator!=(const vector_iterator& rhs) const {return p!=rhs.p;}
// 	bool operator==(const vector_const_iterator<T>& rhs) const {return p==rhs.p;}
// 	bool operator!=(const vector_const_iterator<T>& rhs) const {return p!=rhs.p;}
// 	reference operator*() const {return *p;}
// 	pointer operator->() const {return p;}

// 	vector_iterator& operator=(const vector_iterator& other)
// 	{ p = other.base(); return *this; };

// 	vector_iterator& operator+=(difference_type n) { p += n; return *this; };
// 	vector_iterator& operator-=(difference_type n) { p -= n; return *this; };

// 	vector_iterator operator+(difference_type n) const
// 	{ return vector_iterator(p + n); };
// 	vector_iterator operator-(difference_type n) const
// 	{ return vector_iterator(p - n); };
// 	vector_iterator operator-(vector_const_iterator<T> x) const
// 	{ return vector_iterator(p - x); };
// 	reference operator[](difference_type n) const { return *(p + n); };

// };

template <class Pointer>
class v__iterator
{
public:
	typedef typename iterator_traits<Pointer>::value_type			value_type;
	typedef typename iterator_traits<Pointer>::difference_type		difference_type;
	typedef typename iterator_traits<Pointer>::pointer				pointer;
	typedef typename iterator_traits<Pointer>::reference			reference;
	typedef typename iterator_traits<Pointer>::iterator_category	iterator_category;
	typedef pointer													iterator_type;

	pointer p;

	pointer base() const { return p; }
	pointer base() { return p; }

	// 고쳐야함!!
	// Todo : is_convertible 직접구현.
	template <class _Up>
	v__iterator(const v__iterator<_Up>& __u,
		typename ft::enable_if<std::is_convertible<_Up, iterator_type>::value>::type* = 0)
		: p(__u.base()) {}

	v__iterator() :p(0) {}
	v__iterator(pointer x) :p(x) {}
	v__iterator(const v__iterator& mit) : p(mit.p) {}

	v__iterator& operator++() {++p;return *this;}
	v__iterator operator++(int) {
		v__iterator tmp(*this);
		operator++();
		return tmp;
	}
	v__iterator& operator--() {--p;return *this;}
	v__iterator operator--(int) {
		v__iterator tmp(*this);
		operator--();
		return tmp;
	}
	bool operator==(const v__iterator& rhs) const {return p==rhs.p;}
	bool operator!=(const v__iterator& rhs) const {return p!=rhs.p;}
	reference operator*() const {return *p;}
	pointer operator->() const {return p;}

	v__iterator& operator=(const v__iterator& other)
	{ p = other.base(); return *this; };

	v__iterator& operator+=(difference_type n) { p += n; return *this; };
	v__iterator& operator-=(difference_type n) { p -= n; return *this; };

	v__iterator operator+(difference_type n) const
	{ return v__iterator(p + n); };
	// v__iterator operator-(v__iterator<Pointer> x) const
	// { return v__iterator(p - x.p); };
	// for distance
	v__iterator operator-(difference_type n) const
	{ return v__iterator(p - n); };
	reference operator[](difference_type n) const { return *(p + n); };

};
template <class T>
typename v__iterator<T>::difference_type operator-(const v__iterator<T>&lhs,
	const v__iterator<T>& rhs)
{
	return lhs.p - rhs.p;
};


// ================================================================================
// Non-member function overloads
// ================================================================================
// 관계연산

template <class T, class U>  bool operator== (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{ return lhs.p == rhs.p; };
template <class T, class U>  bool operator!= (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{
	return lhs.p != rhs.p;
};
template <class T, class U>  bool operator< (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{ return lhs.p < rhs.p; };
template <class T, class U>  bool operator<= (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{ return lhs.p <= rhs.p; };
template <class T, class U>  bool operator> (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{ return lhs.p > rhs.p; };
template <class T, class U>  bool operator>= (const v__iterator<T>& lhs,
	const v__iterator<U>& rhs)
{ return lhs.p >= rhs.p; };

// it = 1 + it;
template <class Iter>
v__iterator<Iter> operator+(typename v__iterator<Iter>::difference_type n,
	const v__iterator<Iter>& it)
{ return v__iterator<Iter>(it.base() + n); };

// const_it  - it
template <class T, class U>
typename v__iterator<T>::difference_type operator-(const v__iterator<T>&lhs,
	const v__iterator<U>& rhs)
{
	return lhs.base() - rhs.base();
};



}

#endif