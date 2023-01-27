#include "vector.hpp"
#include "mytree2.hpp"
#include "map.hpp"
#include <map>
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <string>

#include <typeinfo>

#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
#define _pair ft::pair
#define _ratio 10
using namespace std;


template <class T, class V>
std::vector<int> copy_constructor_test(std::map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    std::map<int, int> mp2(mp.begin(), mp.end());
    std::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> copy_constructor_test(_map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    _map<int, int> mp2(mp.begin(), mp.end());
    _map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    std::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    mp2 = mp;
    typename std::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    _map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    mp2 = mp;
    typename _map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

// void gshim_iter_test()
// {
// 	ft::map<int,int> m;
// 	const ft::map<int,int> cm;

// 	// begin(), end() 호출
// 	m.begin(); m.end();

// 	// const 객체로 호출시 const_iter타입으로 반환.
// 	cm.begin(); cm.end();


// 	// iter를 const_iter로 초기화
// 	ft::map<int,int>::const_iterator m_citer;
// 	ft::map<int,int>::iterator m_iter(m_citer);

// 	// compare가 다른 두 맵의 이터레이터끼리 변환.
// 	ft::map<int,int, greater<int> >::iterator g_iter = m.begin();

// 	// 원소 순회하며 출력하기
// 	m.insert(_make_pair(1,1));
// 	m.insert(_make_pair(2,2));
// 	m.insert(_make_pair(3,3));
// 	for(ft::map<int,int>::iterator it = m.begin(); it != m.end(); ++it)
// 		std::cout << it->first << std::endl;

// 	const ft::map<int,int> copy(m.begin(), m.end());
// 	for(ft::map<int,int>::iterator it = copy.begin(); it != copy.end(); ++it)
// 		std::cout << it->first << std::endl;
// }

template <class T, class V>
std::vector<int>    reverse_iterators_test_std(std::map<T, V> mp) {
    std::vector<int> v;

    mp.insert(std::make_pair(5, 5));
    mp.insert(std::make_pair(3, 3));
    mp.insert(std::make_pair(7, 7));
    typename std::map<T, V>::reverse_iterator rit = mp.rbegin();
    typename std::map<T, V>::reverse_iterator rit2 = mp.rend();
    v.push_back(rit->first); // 7
    rit++;
    rit2--;
    v.push_back(rit->first); // 5
    v.push_back(rit2->first); // 3
    rit++;
    v.push_back(*rit == *rit2); // 1
    rit2--;
    v.push_back(rit->first); // 3
    v.push_back(rit2->first); // 5
    v.push_back(*rit2 > *rit); // 1
    v.push_back(*rit2 < *rit); // 0
    v.push_back((--rit)->first); // 5
    v.push_back((++rit2)->first); // 3
    v.push_back((rit--)->first); // 5
    v.push_back((rit2++)->first); // 3
    return v;
}

template <class T, class V>
std::vector<int> reverse_iterators_test_ft(_map<T, V> mp) {

    std::vector<int> v;

    mp.insert(_make_pair(5, 5));
    mp.insert(_make_pair(3, 3));
    mp.insert(_make_pair(7, 7));
    typename _map<T, V>::reverse_iterator rit = mp.rbegin();
    typename _map<T, V>::reverse_iterator rit2 = mp.rend();
    v.push_back(rit->first);
    rit++;
    rit2--;
    v.push_back(rit->first);
    v.push_back(rit2->first);
    rit++;
    v.push_back(*rit == *rit2);
    rit2--;
    v.push_back(rit->first);
    v.push_back(rit2->first);
    v.push_back(*rit2 > *rit);
    v.push_back(*rit2 < *rit);
    v.push_back((--rit)->first);
    v.push_back((++rit2)->first);
    v.push_back((rit--)->first);
    v.push_back((rit2++)->first);
    return v;
}

template <class T, class V>
std::vector<int> equal_range_test(std::map<T, V> mp) {
    std::vector<int> v;
    mp.insert(std::make_pair(10, 10));
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
    return v;
}

template <class T, class V>
std::vector<int> equal_range_test(_map<T, V> mp) {
    std::vector<int> v;
    mp.insert(_make_pair(10, 10));
    mp.insert(_make_pair(20, 20));
    mp.insert(_make_pair(30, 30));
    mp.insert(_make_pair(40, 40));
    mp.insert(_make_pair(50, 50));
    mp.insert(_make_pair(60, 60));
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
    return v;
}

template <class T, class V>
std::vector<int> erase_test_1(std::map<T, V> mp) {
    std::vector<int> v;
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    typename std::map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());
    v.push_back(mp.erase(0));
    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    typename std::map<T, V>::iterator it4 = mp.begin();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
    v.push_back(mp.erase(30 * _ratio - 1));
    v.push_back(mp.size());
    std::map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    typename std::map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> erase_test_1(_map<T, V> mp) {
    std::vector<int> v;
    v.push_back(mp.erase(3));
    for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    typename _map<T, V>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(mp.erase(-5));
    v.push_back(mp.size());

	for(typename _map<T,V>::iterator a = mp.begin(); a != mp.end() ; a++)
		std::cout << (*a).first << ", " << (*a).second << std::endl;

    v.push_back(mp.erase(0));

	for(typename _map<T,V>::iterator a = mp.begin(); a != mp.end() ; a++)
		std::cout << (*a).first << ", " << (*a).second << std::endl;

    v.push_back(mp.size());
    it = mp.begin();
    v.push_back(it->first);
    typename _map<T, V>::iterator it4 = mp.begin();
    for (; it4 != mp.end(); it4 = mp.begin())
        mp.erase(it4->first);
    v.push_back(mp.erase(30 * _ratio - 1));
    v.push_back(mp.size());
    _map<int, int> mp2;
    for (int i = 0, j = 0; i < 10 ; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    mp2.erase(2);
    mp2.erase(7);
    typename _map<T, V>::iterator it3 = mp2.begin();
    for (; it3 != mp2.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    return v;
}

int main()
{
	//gshim_iter_test();

	std::map<int,int> stdmap;
	ft::map<int,int> mymap;

	std::vector<int> ret1 = copy_constructor_test(stdmap);
	std::vector<int> ret2 = copy_constructor_test(mymap);

	std::vector<int> ret3 = assign_overload_test(stdmap);
	std::vector<int> ret4 = assign_overload_test(mymap);

	std::vector<int> ret5 = reverse_iterators_test_std(stdmap);
	std::vector<int> ret6 = reverse_iterators_test_ft(mymap);

	std::vector<int> ret7 = equal_range_test(stdmap);
	std::vector<int> ret8 = equal_range_test(mymap);

	std::vector<int> ret9 = erase_test_1(stdmap);
	std::vector<int> ret10 = erase_test_1(mymap);

    // stdmap.insert(std::make_pair(1,1));
    // stdmap.insert(std::make_pair(2,2));
    // stdmap.insert(std::make_pair(3,3));

    // stdmap[1] = 777;

    // mymap.insert(_make_pair(1,1));
    // mymap.insert(_make_pair(2,2));
    // mymap.insert(_make_pair(3,3));
    // mymap.equal_range(1);

    return 0;
}
