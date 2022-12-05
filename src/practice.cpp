#include <iostream>
#include <iterator>
#include <typeinfo>

#include "ft_containers.hpp"

int iterator_traits(void)
{
	typedef std::iterator_traits<int*> traits;
	if (typeid(traits::iterator_category) == typeid(std::random_access_iterator_tag))
		std::cout << "int* is a rad access iter" << std::endl;

	typedef ft::iterator_traits<int*> ft_traits;
	if (typeid(ft_traits::iterator_category) == typeid(ft::random_access_iterator_tag))
		std::cout << "int* is a rad access iter" << std::endl;

	return 0;
}

class MyIterator : public std::iterator<std::input_iterator_tag, int>
{
  int* p;
public:
  MyIterator(int* x) :p(x) {}
  MyIterator(const MyIterator& mit) : p(mit.p) {}
  MyIterator& operator++() {++p;return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) const {return p==rhs.p;}
  bool operator!=(const MyIterator& rhs) const {return p!=rhs.p;}
  int& operator*() {return *p;}
};

int main () {
  int numbers[]={10,20,30,40,50};
  MyIterator from(numbers);
  MyIterator until(numbers+5);
  for (MyIterator it=from; it!=until; it++)
    std::cout << *it << ' ';
  std::cout << '\n';

  return 0;
}
