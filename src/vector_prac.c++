#include "vector.hpp"
#include <iostream>

void fill()
{
	std::cout << "=====FILL=====" << std::endl;
	ft::vector<int> v2(10,7);
	for(int i=0;i<v2.size();i++)
		std::cout << v2[i] << std::endl;
	std::cout << "=====FILL=====" << std::endl;
	std::cout << std::endl;
}

void range(ft::vector<int> &v)
{
	std::cout << "=====RANGE=====" << std::endl;
	ft::vector<int> v1(v.begin(), v.end());
	for(int i=0;i<v1.size();i++)
		std::cout << v1[i] << std::endl;
	std::cout << "=====RANGE=====" << std::endl;
	std::cout << std::endl;
}

void copy(ft::vector<int> &v)
{
	std::cout << "=====COPY=====" << std::endl;
	ft::vector<int> v1(v);
	for(int i=0;i<v1.size();i++)
		std::cout << v1[i] << std::endl;
	std::cout << std::endl;

	// DEEP COPY CHECK
	v1[0] = 4242;
	std::cout << "v1[0] : " << v1[0] << ", v[0]" << v[0] << std::endl;
	std::cout << "=====COPY=====" << std::endl;
}

void assign(ft::vector<int> &v)
{
	std::cout << "=====ASSIGN=====" << std::endl;
		ft::vector<int> v1;
		v1 = v;
		for(int i=0;i<v1.size();i++)
			std::cout << v1[i] << std::endl;
	std::cout << "=====ASSIGN=====" << std::endl;
}

void test()
{
	ft::vector<int> v(10, 0);
	for(int i=0;i<10;i++)
		v[i] = i + 1;

	fill();
	range(v);
	copy(v);
	assign(v);

}

int main()
{
	test();

	std::cout << "LEAK TESTING..." << std::endl;
	// leaks
	while(1)
	;
}
