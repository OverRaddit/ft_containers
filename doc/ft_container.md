# ㄱㅐ녀ㅁ모음.

- cpp c 차이.

- STL
  - 기본개념
    - container
    - iterator
      - *iter
      - ++iter, --iter
      - iter란?
      - reverse_iterator
      - const_iterator
    - 템플릿
    - malloc? allocator<int> a!
      - destroy
      - dealloc
      - alloc(5)
      - construct
  - 심화개념
    - SFINAE
      - 컴파일 타임, 런 타임

- vector
  - sequence container
  - linear 메모리구조 + "재할당"
- stack
  - adapter container
    - sequence container를 감싸고 있는 형태
- map / set
  - associative container
  - red-black tree

int add(int a, int b) return a+b;
int add(double a, double b) return a+b;
int add(float a, float b) return a+b;

template<class X, class Y>
add(X, Y) return x+b;

vector<int> v;
vector<float> v;


# 궁금s

vector의 이터레이터는 vector가 재할당을 하게되면 유효하지 않게된다.
그러면 현재 vector의 이터레이터가 유효한지 아닌지 어떻게 판단할까?
기존의 begin, end사이에 현재 이터레이터가 참조하는 주소가 있는지의 여부로 판단하면 될듯하다.