#include "vector.hpp"
#include "mytree2.hpp"
#include "map.hpp"
#include "set.hpp"
#include <map>
#include <set>
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include <typeinfo>

#define _vector ft::vector
#define _map ft::map
#define _set ft::set
#define _make_pair ft::make_pair
#define _pair ft::pair
#define _is_integral ft::is_integral
#define _ratio 10
using namespace std;

bool is_integral_test_() {
	std::vector<int> v;
	bool res = 1;
	(_is_integral<float>() == std::is_integral<float>()) ? 0 : res = 0;
	(_is_integral<int>() == std::is_integral<int>()) ? 0 : res = 0;
	(_is_integral<bool>() == std::is_integral<bool>()) ? 0 : res = 0;
	(_is_integral<char>() == std::is_integral<char>()) ? 0 : res = 0;
	(_is_integral<signed char>() == std::is_integral<signed char>()) ? 0 : res = 0;
	(_is_integral<unsigned char>() == std::is_integral<unsigned char>()) ? 0 : res = 0;
	(_is_integral<wchar_t>() == std::is_integral<wchar_t>()) ? 0 : res = 0;
	(_is_integral<char16_t>() == std::is_integral<char16_t>()) ? 0 : res = 0;
	(_is_integral<short>() == std::is_integral<short>()) ? 0 : res = 0;
	(_is_integral<unsigned short>() == std::is_integral<unsigned short>()) ? 0 : res = 0;
	(_is_integral<unsigned int>() == std::is_integral<unsigned int>()) ? 0 : res = 0;
	(_is_integral<long>() == std::is_integral<long>()) ? 0 : res = 0;
	(_is_integral<unsigned long>() == std::is_integral<unsigned long>()) ? 0 : res = 0;
	(_is_integral<long long>() == std::is_integral<long long>()) ? 0 : res = 0;
	(_is_integral<unsigned long long>() == std::is_integral<unsigned long long>()) ? 0 : res = 0;
	return res;
}

template <class T>
std::vector<int> find_test(std::set<T> st) {
    std::vector<int> v;
    for (int i = -75 * _ratio; i < 75 * _ratio; ++i) {
        st.insert(i);
    }
    typename std::set<T>::iterator it = st.find(34 * _ratio);
    v.push_back(*it);

    it = st.find(-34 * _ratio);
    v.push_back(*it);

    it = st.find(-987654321);
    if (it == st.end())
        v.push_back(1);
    return v;
}

template <class T>
std::vector<int> find_test(_set<T> st) {
    std::vector<int> v;
    for (int i = -75 * _ratio; i < 75 * _ratio; ++i) {
        st.insert(i);
    }
    typename _set<T>::iterator it = st.find(34 * _ratio);
    v.push_back(*it);

    it = st.find(-34 * _ratio);
    v.push_back(*it);

    it = st.find(-987654321);
    if (it == st.end())
        v.push_back(1);
    return v;
}

int main()
{
	set<int> s1;
	_set<int> s2;

	std::vector<int> v1 = find_test(s1);
	std::vector<int> v2 = find_test(s2);

	for(int i=0;i<v1.size();i++)
 		std::cout << v1[i] << std::endl;

	std::cout << std::endl << std::endl;

	for(int i=0;i<v2.size();i++)
		std::cout << v2[i] << std::endl;

    return 0;
}
