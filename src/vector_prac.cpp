#include "vector.hpp"
#include "mytree2.hpp"
#include "map.hpp"
#include <map>
#include "utility.hpp"
#include <exception>
#include <iostream>
#include <string>

#include <typeinfo>

#define _vector ft::vector
//#define _map ft::map
#define _make_pair ft::make_pair
#define _pair ft::pair
#define _ratio 10
using namespace std;

// template <class T>
// struct gshim : public false_type {};

// template <class T>
// struct gshim<T const> : public true_type {};

void gshim_iter_test()
{
	ft::map<int,int> m;
	const ft::map<int,int> cm;

	// begin(), end() 호출
	m.begin(); m.end();

	// const 객체로 호출시 const_iter타입으로 반환.
	cm.begin(); cm.end();


	// iter를 const_iter로 초기화
	ft::map<int,int>::const_iterator m_citer;
	ft::map<int,int>::iterator m_iter(m_citer);

	// compare가 다른 두 맵의 이터레이터끼리 변환.
	ft::map<int,int, greater<int> >::iterator g_iter = m.begin();
}

int main()
{
	//gshim_iter_test();

	ft::map<int,int> m;
	m.insert(_make_pair(1,1));
	m.insert(_make_pair(2,2));
	m.insert(_make_pair(3,3));

	for(ft::map<int,int>::iterator it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << std::endl;

}
