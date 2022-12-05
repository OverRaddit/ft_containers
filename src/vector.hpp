#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
#include <vector>

template<class T, class Alloc = std::allocator<T>>
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


typedef typename iterator_traits<iterator>::difference_type		difference_type;
// ?
typedef typename iterator_traits<iterator>::difference_type		size_type; // non-negative value of difference_type



// Member functions
	vector(/* args */);
	~vector();
};

#endif
