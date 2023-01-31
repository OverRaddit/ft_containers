#ifndef FT_ITERATOR_TRAITS
#define FT_ITERATOR_TRAITS

# include "iterator_category.hpp"
namespace ft
{



template<class Iter>
class iterator_traits {
public:
	typedef typename Iter::iterator_category	iterator_category;	// 반복자의 종류
	typedef typename Iter::value_type			value_type;			// 반복자가 가리키는 대상타입
	typedef typename Iter::difference_type		difference_type;	// 반복자끼리의 거리를 표현하는 타입
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	//typedef pointer								iterator_type;
};

template <class T>
struct iterator_traits <T*>
{
public:
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T*								pointer;
	typedef T&								reference;
	//typedef pointer							iterator_type;
};

// const_iter
template <class T>
struct iterator_traits <const T*>
{
public:
	typedef std::random_access_iterator_tag			iterator_category;
	typedef const T							value_type;
	typedef ptrdiff_t						difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
	//typedef pointer							iterator_type;
};

template<class _Category, class _Tp, class _Distance = ptrdiff_t,
         class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
	typedef _Tp        value_type;
	typedef _Distance  difference_type;
	typedef _Pointer   pointer;
	typedef _Reference reference;
	typedef _Category  iterator_category;
};

}
#endif
