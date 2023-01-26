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

int main()
{
	//gshim_iter_test();

	std::map<int,int> stdmap;
	ft::map<int,int> mymap;

	std::vector<int> ret1 = copy_constructor_test(stdmap);
	std::vector<int> ret2 = copy_constructor_test(mymap);

	std::vector<int> ret3 = assign_overload_test(stdmap);
	std::vector<int> ret4 = assign_overload_test(mymap);

    stdmap.insert(std::make_pair(1,1));
    stdmap.insert(std::make_pair(1,1));
    stdmap.insert(std::make_pair(1,1));

    std::cout << stdmap.size() << std::endl;

	// for(int i=0;i<ret2.size();i++)
	// 	std::cout << ret2[i] << std::endl;

}
