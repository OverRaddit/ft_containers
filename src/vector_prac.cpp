#include "vector.hpp"
#include <iostream>

#define _vector ft::vector
#define _ratio 10

// void fill()
// {
// 	std::cout << "=====FILL=====" << std::endl;
// 	ft::vector<int> v2(10,7);
// 	for(int i=0;i<v2.size();i++)
// 		std::cout << v2[i] << std::endl;
// 	std::cout << "=====FILL=====" << std::endl;
// 	std::cout << std::endl;
// }

// void range(ft::vector<int> &v)
// {
// 	std::cout << "=====RANGE=====" << std::endl;
// 	ft::vector<int> v1(v.begin(), v.end());
// 	for(int i=0;i<v1.size();i++)
// 		std::cout << v1[i] << std::endl;
// 	std::cout << "=====RANGE=====" << std::endl;
// 	std::cout << std::endl;
// }

// void copy(ft::vector<int> &v)
// {
// 	std::cout << "=====COPY=====" << std::endl;
// 	ft::vector<int> v1(v);
// 	for(int i=0;i<v1.size();i++)
// 		std::cout << v1[i] << std::endl;
// 	std::cout << std::endl;

// 	// DEEP COPY CHECK
// 	v1[0] = 4242;
// 	std::cout << "v1[0] : " << v1[0] << ", v[0]" << v[0] << std::endl;
// 	std::cout << "=====COPY=====" << std::endl;
// }

// void assign(ft::vector<int> &v)
// {
// 	std::cout << "=====ASSIGN=====" << std::endl;
// 		ft::vector<int> v1;
// 		v1 = v;
// 		for(int i=0;i<v1.size();i++)
// 			std::cout << v1[i] << std::endl;
// 	std::cout << "=====ASSIGN=====" << std::endl;
// }

// void test()
// {
// 	ft::vector<int> v(10, 0);
// 	for(int i=0;i<10;i++)
// 		v[i] = i + 1;

// 	fill();
// 	range(v);
// 	copy(v);
// 	assign(v);

// }

// #include "../system/system_methods.ipp"
// #include "__service.ipp"

// template <typename T>
// std::vector<int> constructor_test(std::vector<T> vector) {
//     std::vector<int> v;
//     std::vector<int> tmp0(vector);
//     std::vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
//     tmp = tmp2;
//     std::vector<int> tmp3(tmp);
//     std::vector<int> tmp4(tmp.begin(), tmp.end());
//     v.push_back(tmp4.size());
//     v.push_back(tmp4.capacity());
//     v.push_back(tmp[2]);
//     v.push_back(tmp3[2]);
//     v.push_back(tmp4[2]);
//     try { std::vector<int> tmp5(-1, -1); }
//     catch (std::exception &e) { v.push_back(1); }
//     return v;
// }

// template <typename T>
// std::vector<int> constructor_test(_vector<T> vector) {
//     std::vector<int> v;
// 	_vector<int> tmp0(vector);
//     _vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
//     tmp = tmp2;
//     _vector<int> tmp3(tmp);
//     _vector<int> tmp4(tmp.begin(), tmp.end());
//     v.push_back(tmp4.size());
//     v.push_back(tmp4.capacity());
//     v.push_back(tmp[2]);
//     v.push_back(tmp3[2]);
//     v.push_back(tmp4[2]);
//     try { _vector<int> tmp5(-1, -1); }
//     catch (std::exception &e) { v.push_back(1); }
//     return v;
// }


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
	std::cout << "1" << std::endl;
    std::vector<int> v;
	_vector<int> tmp0(vector);
    _vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
	std::cout << "2" << std::endl;
    _vector<int> tmp3(tmp);
    _vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
	std::cout << "3" << std::endl;
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { _vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}


int main()
{
	// //test();
	// //exit(run_vector_unit_test<int>("constructor", constructor_test, constructor_test));

	// ft::vector<int> v(20, 42);
	// ft::vector<int> v2(5, 777);

	// std::cout << v.size() << "/ " << v.capacity() << std::endl;
	// for(int i=0;i<20;i++)
	// {

	// 	//std::cout << i << " : " << v[i] << std::endl;
	// 	std::cout << i << " : " << v.at(i) << std::endl;
	// }

	// v.push_back(4242);
	// v.push_back(4242);
	// v.push_back(4242);

	// for(int i=0;i<v.size();i++)
	// 	std::cout << i << " : " << v.at(i) << std::endl;

	// std::cout << v.size() << "/ " << v.capacity() << std::endl;

	// std::cout << "LEAK TESTING..." << std::endl;
	// // leaks
	// while(1)
	// ;

	std::vector<int> v;
	std::vector<int> v1;
	ft::vector<int> v2;

	std::vector<int> v3;

	v1 = constructor_test(v);

	v3 = constructor_test(v2);

	// std::cout << v1.size() << std::endl;
	// std::cout << v1.capacity() << std::endl;

	// for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
	// 	std::cout << *it <<  " " ;
	// std::cout << std::endl << std::endl;


	// std::cout << v3.size() << std::endl;
	// std::cout << v3.capacity() << std::endl;

	// for (std::vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
	// 	std::cout << *it <<  " " ;
	// std::cout << std::endl;
}
