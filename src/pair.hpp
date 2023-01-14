#ifndef FT_PAIR
#define FT_PAIR

namespace ft
{

template <class T1, class T2>
class pair
{
public:
	typedef T1 first_type;
	typedef T2 second_type;

	first_type first;
	second_type second;

	// consturctor
	pair() : first(), second(){};
	pair(const pair<T1, T2> &pr)
		: first(pr.first), second(pr.second) {} // 이게 왜 오류인지 모르겠다.
	pair(const first_type &a, const second_type &b)
		: first(a), second(b){};

	// make_pair의 리턴값을 map에 insert하기 위해 필요한 변환
	template <class U, class V>
	pair(const pair<U, V> &pr)
		: first(pr.first), second(pr.second) {}

	// operator=
	pair &operator=(const pair &pr)
	{
		first = pr.first;
		second = pr.second;
	}
};

template <class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; };
template <class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs == rhs); };

template <class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return lhs.first < rhs.first || (!(lhs.first <= rhs.first) && lhs.second < rhs.second); };
template <class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(rhs < lhs); };
template <class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; };
template <class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); };

}

#endif
