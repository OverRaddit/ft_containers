#ifndef FT_VECTOR_ITERATOR
#define FT_VECTOR_ITERATOR

# include <iterator>

namespace ft
{

//vector_iterator::iterator_category

// vector's iterator
template <class T>
struct vector_iterator //: public std::iterator<std::random_access_iterator_tag, T>
{
typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type value_type;
typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
typedef typename std::iterator<std::random_access_iterator_tag, T>::pointer pointer;
typedef typename std::iterator<std::random_access_iterator_tag, T>::reference reference;
typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category;

pointer p;

pointer base() const { return p; }
//pointer base() { return p; }

vector_iterator() :p(0) {}
vector_iterator(pointer x) :p(x) {}
vector_iterator(const vector_iterator& mit) : p(mit.p) {}

vector_iterator& operator++() {++p;return *this;}
vector_iterator operator++(int) {
	vector_iterator tmp(*this);
	operator++();
	return tmp;
}
vector_iterator& operator--() {--p;return *this;}
vector_iterator operator--(int) {
	vector_iterator tmp(*this);
	operator--();
	return tmp;
}
bool operator==(const vector_iterator& rhs) const {return p==rhs.p;}
bool operator!=(const vector_iterator& rhs) const {return p!=rhs.p;}
reference operator*() {return *p;}
pointer operator->() {return p;}

vector_iterator& operator=(const vector_iterator& other)
{ p = other.base(); return *this; };

vector_iterator& operator+=(difference_type n) { p += n; return *this; };
vector_iterator& operator-=(difference_type n) { p -= n; return *this; };

vector_iterator operator+(difference_type n) const
{ return vector_iterator(p + n); };
vector_iterator operator-(difference_type n) const
{ return vector_iterator(p - n); };
reference operator[](difference_type n) const { return *p; };

};

// ================================================================================
// Non-member function overloads
// ================================================================================
// 관계연산
template <class T>  bool operator== (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{return lhs.p == rhs.p;};
template <class T>  bool operator!= (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{
	return lhs.p != rhs.p;
};
template <class T>  bool operator< (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{return lhs.p < rhs.p;};
template <class T>  bool operator<= (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{return lhs.p <= rhs.p;};
template <class T>  bool operator> (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{return lhs.p > rhs.p;};
template <class T>  bool operator>= (const vector_iterator<T>& lhs,
	const vector_iterator<T>& rhs)
{return lhs.p >= rhs.p;};


template<class Iter>
vector_iterator<Iter> operator+(typename vector_iterator<Iter>::difference_type n,
	const vector_iterator<Iter>& rev_it)
{ return rev_it.p - n; };

template<class Iter>
typename vector_iterator<Iter>::difference_type operator-(const vector_iterator<Iter>&lhs,
	const vector_iterator<Iter>& rhs)
{ return lhs.p - rhs.p; };

}

#endif