#ifndef IS_PAIR
#define IS_PAIR

# include <type_traits>

namespace ft
{

template <typename T>
struct is_pair : public std::false_type {};

template <typename T, typename U>
struct is_pair<ft::pair<T, U> > : public std::true_type {};

}

#endif