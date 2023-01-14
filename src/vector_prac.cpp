#include "vector.hpp"
//#include "map.hpp"
#include "mytree2.hpp"
#include "map.hpp"
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <map>
#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
#define _ratio 10




template <class T, class V>
std::vector<int> copy_constructor_test(std::map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
        //mp.insert(_make_pair(i, j));
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

// int main() {
//     ft::map<int, int>::iterator it;

//     it->first = 1;

//     return (0);
// }

int main()
{
	std::map<int, int> one;
	ft::map<int, int> two;

    copy_constructor_test(one);
    copy_constructor_test(two);

    // ft::map<int,int>::iterator iter;
    // iter = two.begin();
    // iter = two.end();

}
