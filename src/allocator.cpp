#include <iostream>

int main()
{
	std::allocator<int> alloc;


	std::iterator<int> iter =  alloc.allocate(3);
	alloc.construct(iter, 42);
	alloc.construct(iter + 1, 42);
	alloc.construct(iter + 2, 42);

	// print
	for(int i=0;i<3;i++)
		std::cout << *(iter + i) << std::endl;
	std::endl;

	std::allocator<int> alloc2(alloc);
	*(iter) = -42;

	// print
	for(int i=0;i<3;i++)
		std::cout << *(iter + i) << std::endl;
	std::endl;

}