#include "vector.hpp"
//#include "map.hpp"
#include "mytree2.hpp"
#include "mymap.hpp"
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <map>
#define _vector ft::vector
#define _map ft::map
#define _make_pair ft::make_pair
#define _ratio 10


int main()
{
	std::map<int, int> one;
	ft::map<int, int> two;

	// copy_constructor_test(one);
	// copy_constructor_test(two);

	one[1] = 1;
	one[2] = 2;
	one[3] = 3;

	two.insert(_make_pair(1,1));
	two.insert(_make_pair(2,2));
	two.insert(_make_pair(3,3));
	// two[1] = 1;
	// two[2] = 2;
	// two[3] = 3;


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