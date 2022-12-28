- vector
	- [O]allocator
		- [subject]You must use std::allocator.
	- iterator
		- iterator_traits : 반복자가 가리키는 요소에 대한 특성이 담긴 클래스.
		- iterator -> 아근데 구현목록이 아니네. std를 그대로 쓰자.
		- vector의 iterator를 구현해줘야함...
		- [X]const_iterator도 구현해줘야 할 것 같음
		- reverse_iterator
			- 사실상 base iterator를 거꾸로 접근하는 인터페이스만 만들면 된다?
			- base iterator는 std 것을 쓰면 되겠지?
	- enable_if
    	- SFINAE
    	- Substition Failure Is Not An Error
    	- 템플릿인자추론 실패시, 컴파일에러가 아닌 것으로 처리한다.
    	- 오버로드결과물에서 해당 인스턴스화한 것을 지운다.
    	- 원형이 이해가 안되어서 이것저것 찾아보다가 <템플릿메타함수> 개념을 알게됨.
    	- 템플릿메타함수중에 is_integral이 있다.
  	- is_integral
	- 일단 vector의 멤버함수의 원형을 모두 긁어왔다.
		- 멤버 함수를 구현하려면 멤버 변수를 알아야 한다.
		- 왜 doc에 멤버변수는 없지?
		- STL을 뜯어보자...
			- __vector_base에 public/protected로 구분되어 타입이 선언되어 있다. 둘을 왜 구분해둔거지?
	- 멤버함수 구현중!!!
		- 반복되는 내용은 나만의 멤버함수로 정의하자.
		- 모르는 인자값이나 내부적인 행위들을 최대한 파악하자!

- stack
  	- 내부컨테이너를 2번째 템플릿 인자로. 기본값은 내가 구현한 벡터
	- 구현이 매우 간단해보임.

- map
  - 어디서부터 구현해야 하지?
  - 보너스를 구현한다.
  - tree
    - size()
    - begin(), end()
    - constructor, destructor
    - max_size()
    - swap()
    - clear()
    - find(), count()
    - lower_bound(), upper_bound()
    - equal_range()

- namespace ft
- friend?

- 아직 못구현한 것
  - equal
  - lexicographical_compare
    - 구구현현은 했했는는데  노노이이해해.
  - pair
  - make_pair
-> 얘네들을 어디에 사용하는지 모르겠다. vector, stack에서는 전혀 안쓰는 것 같은데..

- 생각해볼것
  - 각 클래스별 접근지시어를 어떻게 구분할지?

