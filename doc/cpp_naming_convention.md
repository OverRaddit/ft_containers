# C++ 이름 규약

- m_memberName : public members
- _memberName : private members

STL을 뜯어보니 변수이름에 죄다 '_'(underscore)를 붙이던데 왜 이런 방법을 고수하는지 모르겠다.

```C++
#define first 1
#include <algorithm>
```
위 코드는 동작한다. 따라서 헤더는 이미 선언한 first라는 변수를 다시 다른 헤더에서 사용할수 없게된다.

즉 어떤 변수가 다른 변수와 이름이 겹치는 것을 피하게 만들기 위해서 언더스코어를 붙이는 것이다.

그래서 이렇게 선언해버리면
```C++
#define _First 1
#include <algorithm>
```
예약된 식별자를 사용할 수 없다는 규칙을 위반했고 프로그램에 정의되지 않은 동작이 있다고 할 것이다.

> 한줄요약:
> 사용자가 지정한 변수랑 겹치지 않게 하려구!

답변출처:
https://www.quora.com/Why-is-variable-and-parameter-in-C-STL-often-named-like-This-What-makes-putting-an-underscore-upfront-really-necessary