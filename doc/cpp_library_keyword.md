# CPP STL중 모르는 예약어들을 정리한 파일.

## C++11 문법 : default, delete
```C++
class Test
{
public:
	Test() = default;	// 기본생성자를 명시적으로 만듬 -> 컴파일러가 기본생성자를 생성하지 않게된다
	Test(const Test& other) = delete;	// 컴파일러가 만들어주는 복사생성자를 삭제함
	void operator=(const Test& other) = delete;
}
```


## _LIBCPP_INLINE_VISIBILITY

- libc++'s ABI의 일부가 되지 않도록 표시해주는 역할을 한다.

슬랙에서 나온 의견들 정리
https://42born2code.slack.com/archives/CU6MU5TB7/p1619879754249400

```C++
// Just so we can migrate to the new macros gradually.
#define _LIBCPP_INLINE_VISIBILITY _LIBCPP_HIDE_FROM_ABI
...
#define _LIBCPP_HIDE_FROM_ABI _LIBCPP_HIDDEN _LIBCPP_INTERNAL_LINKAGE
...
#    define _LIBCPP_HIDDEN __attribute__ ((__visibility__("hidden")))
...
#if __has_attribute(internal_linkage)
#  define _LIBCPP_INTERNAL_LINKAGE __attribute__ ((internal_linkage))
#else
#  define _LIBCPP_INTERNAL_LINKAGE _LIBCPP_ALWAYS_INLINE
#endif
```

#define _LIBCPP_INLINE_VISIBILITY _LIBCPP_HIDE_FROM_ABI의 의도는?
함수에 표시를 함으로써 동적라이브러리로부터 이 함수를 숨기는 것이다.
보통 함수를 inline으로 만드는 동작이었지만,
지금은 clang attribute인 attribute((internal_linkage))이 사용된다.
참고로 _LIBCPP_HIDE_FROM_ABI가 해당 attribute로 정의되어있다.

### __attribute__ ((__visibility__("hidden")))

__attribute__ ((__visibility__(""))) 매크로를 활용하면 라이브러리내 구현된 함수를 외부에서 호출할 수 있을지 여부를 결정할 수 있다.
visibility에 어떤값을 넣느냐에 따라 달라진다.
default : 해당 함수가 라이브러리 외부에 노출되어 외부에서 호출 가능함.
hidden : 외부에 노출되지 않아 외부에서 호출할 수 없게된다.
- 출처: https://tttsss77.tistory.com/264

### clang attribute : attribute((internal_linkage))?????????

- internal linkage, external linkage의 차이?



## inline

함수 앞에 inline이라는 키워드를 적어 인라인함수로 선언,생성할 수 있다.

> 인라인함수란?
> 인라인 함수 호출시,호출된 곳에 인라인 함수 코드 자체가 안으로 들어간다.
```C++
#include <iostream>
inline void PrintHello() {
	cout << "Hello, World" << endl;
}
int main() {
	PrintHello();
	PrintHello();
	return 0;
}
```

인라인 함수의 장단점
- 프로그램의 실행속도가 빨라진다.
- 메모리의 낭비가 일어난다.
-> 호출이 많이 일어나지 않는 함수 or 실행속도가빠른데 비해 함수의 호출시간이 부담스러울때 주로 사용.