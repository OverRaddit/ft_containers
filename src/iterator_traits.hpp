#ifndef FT_ITERATOR_TRAITS
#define FT_ITERATOR_TRAITS

# include "iterator_category.hpp"

template<class Iter>
class iterator_traits {
public:
	typedef typename Iter::iterator_category	iterator_category;	// 반복자의 종류
	typedef typename Iter::value_type			value_type;			// 반복자가 가리키는 대상타입
	typedef typename Iter::difference_type		difference_type;	// 반복자끼리의 거리를 표현하는 타입
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
};

template <class T>
struct iterator_traits<T*>
{
public:
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef T*							pointer;
	typedef T&							reference;
};

template <class T>
class iterator_traits<const T*>
{
public:
	typedef random_access_iterator_tag	iterator_category;
	typedef T 							value_type;
	typedef ptrdiff_t					difference_type;
	typedef const T*					pointer;
	typedef const T&					reference;
};

#endif
