#ifndef FT_VECTOR
#define FT_VECTOR

// 눈팅용
#include <vector>
#include <stack>
#include <iostream>

#include "vector.hpp"

namespace ft
{

	template <class T, class Con = vector<T>>
	class stack
	{
		typedef T value_type;
		typedef Con container_type;
		typedef typename container_type::allocator_type::size_type size_type;

		// member variable ? or inherit container???
	protected:
		container_type container;

	public:
		// member func
		explicit stack(const container_type &ctnr = container_type())
			: container(ctnr){};

		bool empty() const { return container.empty(); };
		size_type size() const { return container.size(); };
		value_type &top() { return *(container.end() - 1); };
		const value_type &top() const { return *(container.end()); };

		// 내부 컨테이너가 list, vector일때 호출하는 함수가 다른데....?
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
