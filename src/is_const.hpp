#ifndef IS_CONST
#define IS_CONST
#include <type_traits>
namespace ft
{

template <class T>
struct is_const : public std::false_type {};
template <class T>
struct is_const<T const> : public std::true_type {};

}

#endif
