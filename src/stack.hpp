#ifndef FT_STACK
#define FT_STACK

# include "vector.hpp"

namespace ft
{
template <class T, class Con = ft::vector<T> >
struct stack
{
	typedef T value_type;
	typedef Con container_type;
	typedef typename container_type::allocator_type::size_type size_type;

protected:
	container_type container;

public:
	explicit stack(const container_type &ctnr = container_type())
		: container(ctnr) {};

	bool empty() const { return container.empty(); };
	size_type size() const { return container.size(); };
	value_type &top() { return *(container.end() - 1); };
	const value_type &top() const { return *(container.end()); };

	void push(const value_type &val) { container.push_back(val); };
	void pop() { container.pop_back(); };

	container_type base() const { return container; };
};

// non-member func
template <class T, class Con>
bool operator==(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() == rhs.base();
};
template <class T, class Con>
bool operator!=(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() != rhs.base();
};
template <class T, class Con>
bool operator<(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() < rhs.base();
};
template <class T, class Con>
bool operator<=(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() <= rhs.base();
};
template <class T, class Con>
bool operator>(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() > rhs.base();
};
template <class T, class Con>
bool operator>=(const stack<T, Con> &lhs, const stack<T, Con> &rhs)
{
	return lhs.base() >= rhs.base();
};

}
#endif
