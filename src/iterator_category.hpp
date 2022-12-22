#ifndef FT_ITERATOR_CATEGORY
#define FT_ITERATOR_CATEGORY

namespace ft
{


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

// template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
// struct __has_iterator_category_convertible_to
//     : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
// {};

// template <class _Tp, class _Up>
// struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

// template <class _Tp>
// struct __is_cpp17_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

// template <class _Tp>
// struct __is_cpp17_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

// template <class _Tp>
// struct __is_cpp17_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

// template <class _Tp>
// struct __is_cpp17_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};


}
#endif
