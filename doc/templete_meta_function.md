# 템플릿 메타 함수

템플릿 메타 함수란, 함수처럼 동작하는 템플릿 클래스들을 말한다.
보통 함수는 값에 대해 연산을 수행하지만, 메타 함수는 타입에 대해 연산을 수행한다.

```C++
if (is_negative(x)) {
  // Do something...
}

// 어떤 타입 T 가 있어서
if (is_void<T>::value) {
  // Do something
}
```