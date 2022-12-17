#include "vector.hpp"
#include <exception>
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
std::vector<int> resize_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(9900 * _ratio, 1);
    vector.resize(5000 * _ratio);
    vector.reserve(5000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.resize(7000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.resize(15300 * _ratio, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
	std::cout << vector[65] << std::endl;


    return v;
}

template <typename T>
std::vector<int> resize_test(_vector<T> vector) {
    std::vector<int> v;
    // vector.assign(9900 * _ratio, 1);
    // vector.resize(5000 * _ratio);
    // vector.reserve(5000 * _ratio);
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    // vector.resize(7000 * _ratio);
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    // vector.resize(15300 * _ratio, T());
    // v.push_back(vector.size());
    // v.push_back(vector.capacity());
    // v.push_back(vector[65]);
	    vector.assign(9900 * _ratio, 1);
    vector.resize(5000 * _ratio);
    vector.reserve(5000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.resize(7000 * _ratio);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.resize(15300 * _ratio, T());
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    v.push_back(vector[65]);
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
	std::cout << vector[65] << std::endl;
    return v;
}


int main()
{
	std::cout << "START" << std::endl;
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

	v1 = resize_test(v);

	v3 = resize_test(v2);

}


//==========================================

// std::iterator example
// #include <iostream>     // std::cout
// #include <iterator>     // std::iterator, std::input_iterator_tag

// class MyIterator : public std::iterator<std::input_iterator_tag, int>
// {
//   int* p;
// public:
//   MyIterator(int* x) :p(x) {}
//   MyIterator(const MyIterator& mit) : p(mit.p) {}
//   MyIterator& operator++() {++p;return *this;}
//   MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
//   bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
//   bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
// //   int& operator*() {return *p;}
// };

// int main () {
//   int numbers[]={10,20,30,40,50};
//   MyIterator from(numbers);
//   MyIterator until(numbers+5);
//   for (MyIterator it=from; it!=until; it++)
//     std::cout << *it << ' ';
//   std::cout << '\n';

//   return 0;
// }