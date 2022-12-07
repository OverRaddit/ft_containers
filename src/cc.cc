#include <iterator>
#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>

int main()
{
	std::vector<int> ivec;
	std::stringstream ss("0 1 2 3 42");
	std::istream_iterator<int> begin(ss), end;

	std::cout << "distance: " << std::distance(begin, end) << std::endl;
	for (std::istream_iterator<int> it = begin; it != end; ++it)
	{
		std::cout << "value: " << *it << std::endl;
	}
	begin.operator++();

	return 0;
}