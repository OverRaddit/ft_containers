#ifndef IS_CONST
#define IS_CONST
#include <type_traits>
namespace ft
{

template <class T>
struct is_const : public false_type {};
template <class T>
struct is_const<T const> : public true_type {};

}

#endif


template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const            : public false_type {};
template <class _Tp> struct _LIBCPP_TEMPLATE_VIS is_const<_Tp const> : public true_type {};

#if _LIBCPP_STD_VER > 14 && !defined(_LIBCPP_HAS_NO_VARIABLE_TEMPLATES)
template <class _Tp>
_LIBCPP_INLINE_VAR _LIBCPP_CONSTEXPR bool is_const_v
    = is_const<_Tp>::value;
#endif