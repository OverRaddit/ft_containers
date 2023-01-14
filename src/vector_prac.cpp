#include "vector.hpp"
//#include "map.hpp"
#include "mytree2.hpp"
#include "map.hpp"
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

int main()
{
	std::map<int, int> one;
	std::map<int, int> one3;
	ft::map<int, int> two;
	ft::map<int, int> three = two;

	// insert_test(one);
	// insert_test(two);

	two.insert(two.begin(), _make_pair(1,1));
	two.insert(two.begin(), _make_pair(2,2));
	two.insert(two.begin(), _make_pair(3,3));

	std::cout << two.count(1) << std::endl;
	two.size();
}
