#ifndef REMOVE_CONST
#define REMOVE_CONST
#include <type_traits>
namespace ft
{
template <typename T>
struct remove_const {};

template <typename T>
struct remove_const<const T>
{
	typedef T	type;
};
}
#endif