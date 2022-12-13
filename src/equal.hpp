#ifndef EQUAL
#define EQUAL
namespace ft
{

// Test whether the elements in two ranges are equal

// equality
template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
{
	while (first1 != last1)
	{
		// first2 == end case how??? -> end is not equal with *first1
		if (*first1++ != *first2++)
			return false;
	}
	return true;
};

// greater<>
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
{
	while (first1 != last1)
	{
		// pred is function pointer
		if (!pred(*first1++, *first2++))
			return false;
	}
	return true;
};

}
#endif