#include "vector.hpp"
//#include "map.hpp"
#include "mytree2.hpp"
#include "map.hpp"
#include <map>
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <string>
#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
#define _pair ft::pair
#define _ratio 10
using namespace std;

template <class T, class V>
std::vector<int> insert_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::pair<std::map<int, int>::iterator , bool> pair = mp.insert(std::make_pair(7, 7));
    std::map<int, int>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second);
    mp.insert(std::make_pair(9, 9));
    std::pair<std::map<int, int>::iterator , bool> pair2 = mp.insert(std::make_pair(9, 9));
    std::map<int, int>::iterator it2 = pair.first;
    v.push_back(it2->first);
    v.push_back(it2->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second);
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    typename std::map<T, V>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    v.push_back(mp.size());
    return v;
}

template <class T, class V>
std::vector<int> insert_test(_map<T, V> mp) {
    std::vector<int> v;
    _pair<_map<int, int>::iterator , bool> pair = mp.insert(_make_pair(7, 7));
    _map<int, int>::iterator it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second);
    mp.insert(_make_pair(9, 9));
    _pair<_map<int, int>::iterator , bool> pair2 = mp.insert(_make_pair(9, 9));
    _map<int, int>::iterator it2 = pair.first;
    v.push_back(it2->first);
    v.push_back(it2->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second);
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    typename _map<T, V>::iterator it3 = mp.begin();
    for (; it3 != mp.end(); ++it3) {
        v.push_back(it3->first);
        v.push_back(it3->second);
    }
    v.push_back(mp.size());
    return v;
}

template <class T, class V>
std::vector<int> insert_test_3(std::map<T, V> mp) {
    std::vector<int> v;
    typename std::map<T, V>::iterator it = mp.end();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(it, std::make_pair(i, j));
    }
    typename std::map<T, V>::iterator it2 = mp.begin();
    for (; it2 != mp.end(); ++it2) {
        v.push_back(it2->first);
        v.push_back(it2->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> insert_test_3(_map<T, V> mp) {
    std::vector<int> v;
    typename _map<T, V>::iterator it = mp.end();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(it, _make_pair(i, j));
    }
    typename _map<T, V>::iterator it2 = mp.begin();
    for (; it2 != mp.end(); ++it2) {
        v.push_back(it2->first);
        v.push_back(it2->second);
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
        std::cout << it->first << ", " << it->second << std::endl;
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
        std::cout << it->first << ", " << it->second << std::endl;
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}


int main()
{
	std::map<int, int> one;
	ft::map<int, int> two;
	ft::map<int, int> three = two;
	vector<int> v1;
	vector<int> v2;

	// std::cout << "one" << std::endl;
	// v1 = insert_test(one);
	// for(int i=0;i<v1.size();i++)
	//     std::cout << v1[i] << std::endl;
	// std::cout << "two" << std::endl;
	// v2 = insert_test(two);
	// for(int i=0;i<v2.size();i++)
	//     std::cout << v2[i] << std::endl;

	std::map<int, int> mp;
	std::map<int, int, std::plus<int> >::iterator mpiter = mp.end();
	_map<int, int> mp3;
	_map<int, int, std::plus<int> >::iterator mp3iter = mp3.end();
	// _map<int, int>::iterator justiter = mp3.end();
	// vector<int> v;
	// for (typename _map<int, int>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }

	// _map<int, int>::iterator iter;
	// std::cout << (*(--iter)).first << std::endl;

}
