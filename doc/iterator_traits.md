# Iterator_traits

## 개요

알고리즘, 반복자, 컨테이너 3요소를 떠올려 보자.
알고리즘은 컨테이너에 상관없이 반복자를 통해 데이터에 접근한다.
근데 반복자가 가리키는 데이터에 대해 어떻게 알 수 있을까? 가리키는 데이터는 int? string? 객체?

STL은 반복자의 특징을 표현하기 위해 iterator_traits 클래스와 이 클래스를 보조하는 여러 가지 타입 정보를 정의한다.

```C++
template<class Iter>
struct iterator_traits {
	typedef typename Iter::iterator_category iterator_category;	// 반복자의 종류
	typedef typename Iter::value_type value_type;				// 반복자가 가리키는 대상타입
	typedef typename Iter::difference_type difference_type;		// 반복자끼리의 거리를 표현하는 타입
	typedef typename Iter::pointer pointer;
	typedef typename Iter::reference reference;
};
```

## 반복자의 종류
```C++
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
```
이들은 모두 멤버를 가지지 않는 빈 구조체이다.
그러면서도 일종의 상속계층을 구성하고 있다.
다만, 이는 개념적인 상속관계를 말하는 것이지 실제로 반복자들이 상속계층을 구성하는 것은 아니다.


출처
http://www.soen.kr/lecture/ccpp/cpp4/39-2-6.htm
