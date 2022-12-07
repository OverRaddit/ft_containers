// reverse_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>       // std::vector
#include "reverse_iterator.hpp"

int main () {
  std::vector<int> myvector;
  for (int i=10; i<31; i++) myvector.push_back(i);

  typedef std::vector<int>::iterator iter_type;
  std::cout <<*(myvector.begin()) << '\n';
                                                         // ? 9 8 7 6 5 4 3 2 1 0 ?
  iter_type from (myvector.begin());                     //   ^
                                                         //         ------>
  iter_type until (myvector.end());                      //                       ^
                                                         //
  ft::reverse_iterator<iter_type> rev_until (from);     // ^
                                                         //         <------
  ft::reverse_iterator<iter_type> rev_from (until);     //                     ^
  std::reverse_iterator<iter_type> asdf (until);     //                     ^

	std::cout << "*from = " << *from << std::endl;
	std::cout << "*rev_until = " << *rev_until << std::endl;
	std::cout << "*x_rev_until = " << *asdf << std::endl;

  std::cout << "myvector:";
  while (rev_from != rev_until)
  {
	  std::cout << *rev_from << ", " << *rev_until << std::endl;
    std::cout << ' ' << *rev_from++ << std::endl;
  }
  std::cout << '\n';

  return 0;
}