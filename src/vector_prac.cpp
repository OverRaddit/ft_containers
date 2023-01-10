#include "vector.hpp"
//#include "map.hpp"
#include "mytree2.hpp"
#include <exception>
#include <iostream>
#include <map>
#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
#define _ratio 10

class ABC {
public:
    char *l;
    int i;
    ABC():l(nullptr), i(1) {};
    ABC(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~ABC() {
        delete this->l;
        this->l = nullptr;
		std::cout << "B destructor!" << std::endl;
    };
};

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
		std::cout << "B destructor!" << std::endl;
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
		std::cout << "A destructor!" << std::endl;
    };
};

void test(A &a)
{
	std::cout << "hello" << std::endl;
};

template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
	std::cout << "1" << std::endl;
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
	std::cout << "2" << std::endl;
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << "3" << std::endl;
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
	std::cout << "4" << std::endl;
    std::vector<A> vv;
    std::vector<B*> v1;
	std::cout << "5" << std::endl;
    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
	std::cout << "6" << std::endl;
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
		std::cout << "-1" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
	std::cout << "0" << std::endl;
    return v;
}

template <typename T>
std::vector<int> insert_test_3(_vector<T> vector) {
    std::vector<int> v;
    _vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
	std::cout << "1" << std::endl;
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
	std::cout << "2" << std::endl;
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << "3" << std::endl;
    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
	std::cout << "4" << std::endl;
    _vector<A> vv;
    _vector<B*> v1;
	std::cout << "5" << std::endl;
    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
	std::cout << "6" << std::endl;
	std::cout << "sizeof A" << sizeof(A) << std::endl;
	std::cout << "sizeof B*" << sizeof(B*) << std::endl;
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
		std::cout << "-1" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
	std::cout << "0" << std::endl;
    return v;
}

template <typename T>
std::vector<int> swap_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    std::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    std::swap(vector, tmp4);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    return v;
}

template <typename T>
std::vector<int> swap_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * _ratio, 11);
    _vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    vector.swap(tmp);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    vector.swap(tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    std::swap(vector, tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    std::swap(vector, tmp4);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cout << vector[2] << std::endl;
	std::cout << vector.size() << std::endl;
	std::cout << vector.capacity() << std::endl;
    return v;
}

// int main()
// {
// 	std::cout << "START" << std::endl;
// 	// //test();
// 	// //exit(run_vector_unit_test<int>("constructor", constructor_test, constructor_test));

// 	// ft::vector<int> v(20, 42);
// 	// ft::vector<int> v2(5, 777);

// 	// std::cout << v.size() << "/ " << v.capacity() << std::endl;
// 	// for(int i=0;i<20;i++)
// 	// {

// 	// 	//std::cout << i << " : " << v[i] << std::endl;
// 	// 	std::cout << i << " : " << v.at(i) << std::endl;
// 	// }

// 	// v.push_back(4242);
// 	// v.push_back(4242);
// 	// v.push_back(4242);

// 	// for(int i=0;i<v.size();i++)
// 	// 	std::cout << i << " : " << v.at(i) << std::endl;

// 	// std::cout << v.size() << "/ " << v.capacity() << std::endl;

// 	// std::cout << "LEAK TESTING..." << std::endl;
// 	// // leaks
// 	// while(1)
// 	// ;

// 	// std::vector<int> v;
// 	// std::vector<int> v1;
// 	// ft::vector<int> v2;

// 	// std::vector<int> v3;

// 	// v1 = insert_test_3(v);

// 	// std::cout << "========\n";

// 	// v3 = insert_test_3(v2);

// 	// while(1)
// 	// ;

// 	// // map
// 	//   std::map<char,int> mymap;

// 	// mymap['x']=1001;
// 	// mymap['y']=2002;
// 	// mymap['z']=3003;

// 	// std::cout << "mymap contains:\n";

// 	// std::pair<char,int> highest = *mymap.rbegin();          // last element

// 	// std::map<char,int>::iterator it = mymap.begin();
// 	// do {
// 	// 	std::cout << it->first << " => " << it->second << '\n';
// 	// } while ( mymap.value_comp()(*it++, highest) );

// 	// return 0;

// 	// ABC abc;
// 	// ABC * ptr = new ABC();

// 	int n = 0;
// 	A *p;

// 	// c==========
// 	A x;
// 	A* x_ptr = new A();

// 	B* y = new B();

// 	x = x_ptr;
// 	x = y;
// 	//x = ptr;
// 	// ===========
// 	// insert(x,y);  // x,y iter n,value

// 	// test(&A);
// 	// test(y);
// 	// test(*y);

// 	// abc = y;
// 	// abc = x;
// }

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

int main()
{
	std::map<int, int> one;
	ft::map<int, int> two;

	// copy_constructor_test(one);
	// copy_constructor_test(two);

	one[1] = 1;
	one[2] = 2;
	one[3] = 3;

	// constructor
	ft::map<int, int> copy(one.begin(), one.end());
	std::cout << "size: " << copy.size() << std::endl;

}

// int main()
// {
// 	//_map<int, int>::iterator it;
// 	std::map<int, int>::iterator it;

//     it->first = 1;

//     return (0);
// }