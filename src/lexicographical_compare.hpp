#ifndef LEXICOGRAPHICAL_COMPARE
#define LEXICOGRAPHICAL_COMPARE
namespace ft
{

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
{
	while (first1!=last1)
	{
		if (first2==last2 || *first2 < *first1)
			return false;
		else if (*first1 != *first2)
			return (*first1 < *first2);
		++first1; ++first2;
	}
	return (first2!=last2);
};

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2,
								Compare comp)
{
	while (first1!=last1)
	{
		if (first2==last2)
			return false;
		else if (*first1 != *first2)
			return comp(*first1, *first2);
		++first1; ++first2;
	}
	return (first2!=last2);
};

}
#endif
