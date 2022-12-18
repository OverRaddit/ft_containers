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
template <typename T>
std::vector<int> insert_test_2(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    vector.insert(vector.end() - 50, 4200 * _ratio , 2);
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}

template <typename T>
std::vector<int> insert_test_2(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    vector.insert(vector.end() - 50, 4200 * _ratio , 2);
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    return v;
}


class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

template <typename T>
std::vector<int> insert_test_3(_vector<T> vector) {
    std::vector<int> v;
    _vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    _vector<A> vv;
    _vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

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

	v1 = insert_test_3(v);

	v3 = insert_test_3(v2);

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
