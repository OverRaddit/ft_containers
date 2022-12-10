

#include "container.hpp"

// using namespace std;
int a=1;

void test(std::string msg)
{
	std::cout << msg << std::endl;
}

int main()
{
    std::vector<int> s(10, 5);

	std::cout << "START1" << std::endl;
	test("Hello World!");
	std::cout << "START2" << std::endl;
	std::cout << "START3" << std::endl;


    // s.reserve(11);
    // std::cout << s.size() << ' '  << s.capacity() << '\n';
    // unsigned long length = s.max_size();
    // std::cout << length << '\n';
    // s.resize(18406744073709551615UL);

    // s.resize(5);
    // std::cout << s.size() << ' '  << s.capacity();
    // s.resize(10);
    // for (std::vector<int>::iterator it = s.begin();
    //     it != s.end() ;
    //     ++it)
    //     std::cout << *it << '\n';

}