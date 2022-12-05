# ENABLE_IF

## SFINAE

함수를 호출할때, 해당 이름을 가진 여러 함수가 있을 때 적합한 함수를 어떻게 판단하지?

일반함수를 호출하려했지만, 템플릿함수가 인스턴스화될 수 있다.

C++ 11 표준의 14.8.2 조항
- 템플릿 인자 치환에 실패할 경우 (위 같은 경우) 컴파일러는 이 오류를 무시하고, 그냥 오버로딩 후보에서 제외하면 된다


## 선수지식

- https://koreanfoodie.me/958
- 템플릿 메타 함수
  - 보통 함수는 값을 전달하지만 메타함수는 타입을 전달한다.
  - 실제 함수가 아니기때문에,,, ()대신 <>를 통해 템플릿인자를 전달한다.
  - 실제로는 클래스이다.

```C++
#include <iostream>
#include <type_traits>
template<typename T>
void tell_type()
{
	if (std::is_void<T>::value)
		std::cout << "T 는 void! \n";
	else
		std::cout << "T 는 void 가 아니다. \n";
}
int main()
{
	tell_type<int>(); // T 는 void 가 아니다.
	tell_type<void>(); // T 는 void!
}

// is_void
template <typename T>
struct is_void
{
	static constexpr bool value = false;
};

template <>
struct is_void<void>
{
	static constexpr bool value = true;
};

```

if문 대신

## SFINAE를 가능하게 하는 enable-if 구문


## enable-if?

- 조건식을 만족하면, 해당 타입이 정의된다.
- SFINAE 를 잘 활용하는 툴들 중 가장 널리 쓰이는 것이 바로 enable_if 입니다.

```C++
// 1.
template <bool, typename T = void>
struct enable_if {};

// 2.
template <typename T>
struct enable_if<true, T> {
  typedef T type;
};


template <class T, typename std::enable_if<std::is_integral<T>::value,
                                           T>::type* = nullptr>
void do_stuff(T& t) {
  std::cout << "do_stuff integral\n";
  // 정수 타입들을 받는 함수 (int, char, unsigned, etc.)
}

template <class T,
          typename std::enable_if<std::is_class<T>::value, T>::type* = nullptr>
void do_stuff(T& t) {
  // 일반적인 클래스들을 받음
}
```

- IF(조건) X타입을 정의.


출처
- https://modoocode.com/255