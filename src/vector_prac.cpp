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

template <typename T>
std::vector<int> constructor_test(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp0(vector);
    std::vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    std::vector<int> tmp3(tmp);
    std::vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { std::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<int> constructor_test(_vector<T> vector) {
    std::vector<int> v;
	_vector<int> tmp0(vector);
    _vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    _vector<int> tmp3(tmp);
    _vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { _vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

int main()
{
	std::vector<int> v1;
	ft::vector<int> v2;

	ft::vector<std::string> vct(10);

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = std::string((vct.size() - i), i + 65);

	vct.erase(vct.begin() + 2);

	vct.erase(vct.begin());
	vct.erase(vct.end() - 1);

	vct.erase(vct.begin(), vct.begin() + 3);
	vct.erase(vct.end() - 3, vct.end() - 1);

	vct.push_back("Hello");
	vct.push_back("Hi there");
	vct.erase(vct.end() - 3, vct.end());

	vct.push_back("ONE");
	vct.push_back("TWO");
	vct.push_back("THREE");
	vct.push_back("FOUR");
	vct.erase(vct.begin(), vct.end());

	std::cout << "end" << std::endl;

	return 0;
}
