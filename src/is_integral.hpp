#ifndef IS_INTEGRAL
#define IS_INTEGRAL
#include <type_traits>
namespace ft
{

template <class T, T _value>
struct myintregral_constant
{
	const static T value = _value;
	T operator()() { return value; };
	operator T() { return value; };
};


template <class T>
struct is_integral : myintregral_constant<bool, false> {};

template <>
struct is_integral<bool> : myintregral_constant<bool, true> {};
template <>
struct is_integral<char> : myintregral_constant<bool, true> {};
template <>
struct is_integral<char16_t> : myintregral_constant<bool, true> {};
template <>
struct is_integral<char32_t> : myintregral_constant<bool, true> {};
template <>
struct is_integral<signed char> : myintregral_constant<bool, true> {};
template <>
struct is_integral<short int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<long int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<long long int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<unsigned char> : myintregral_constant<bool, true> {};
template <>
struct is_integral<unsigned short int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<unsigned int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<unsigned long int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<unsigned long long int> : myintregral_constant<bool, true> {};
template <>
struct is_integral<wchar_t> : myintregral_constant<bool, true> {};

}

#endif