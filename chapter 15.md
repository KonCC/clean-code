# 15장 JUnit 들여다보기

- ComparisonCompactor 모듈 테스트코드
- ABCDE와 ABXDE가 들어오면 AB[X]DE를 반환하는 모듈
- 테스트 케이스를 돌려본 후 모듈에 대한 코드 커버리지가 높을수록 모듈이 올바르게 동작한다
    - 커버리지가 100프로라는 것은 테스트 케이스가 모듈의 모든 If,for문을 수행한다는 의미

<br>

# 코드 개선하기

## 접두어 제거
f는 아마 function이었을지 않을까..
```kotlin
// Bad
private val fContextLength: Int
private val fExpected: String
private val fActual: String
private lateinit var fPrefix: Int
private lateinit var fSuffix: Int 
```

```kotlin
// Good
private val contextLength: Int
private val expected: String
private val actual: String
private lateinit var prefix: Int
private lateinit var suffix: Int 
```

## 캡슐화되지 않은 조건문 & 명확하지 않은 이름
- 부정문은 이해하기 어렵기 때문에 긍정문으로 변경한다.
- this.expected와 expected는 서로 의미하는 바가 다른데 동일한 이름을 사용하여 this.이 붙었다.
	- 명확한 이름으로 지역변수 이름을 수정

```kotlin
// Bad
fun compact(message: String) {
	if(expected == null || 
		actual ==null || 
			areStringsEqual()){
		return Assert.format(message,expected,actual)
	}
	
	val expected = compactString(this.expected)
	val actual = compactString(this.actual)
} 
```

```kotlin
// Good
fun compact(message: String) {
	if(canBeCompacted()){
		findCommonPrefix()
		findCommonSuffix()
		val compactExpected = compactString(expected)
		val compactActual = compactString(actual)
		return Assert.format(message,compactExpected,compactActual)
		
	}
	return Assert.format(message,expected,actual)
} 

fun canBeCompacted(): Boolean{
	return expected != null &&
		actual != null && 
			areStringsEqual().not()
}
```

## 함수 분리
- compact라고 이름 붙였지만 canBeCompacted가 false인 경우는 압축되지 않음
- 형식적인 문자열을 리턴한다는 의미도 없음
- formatCompactedComparison()으로 변경
- 그리고 압축을 해야 하는 경우는 따로 함수로 분리
	- 따로 분리를 하면서 지역변수가 멤버변수로 변경됨

```kotlin
// Bad
fun compact(message: String) {
	if(canBeCompacted()){
		findCommonPrefix()
		findCommonSuffix()
		val compactExpected = compactString(expected)
		val compactActual = compactString(actual)
		return Assert.format(message,compactExpected,compactActual)
		
	}
	return Assert.format(message,expected,actual)
	
} 

fun canBeCompacted(): Boolean{
	return expected != null &&
		actual != null && 
			areStringsEqual().not()
}
```

```kotlin
// Good
private var compactExpected = ""
private var compactActual = ""

fun formatCompactedComparison(message: String) {
	if(canBeCompacted()){
		compactExpecteedAndActual()
		return Assert.format(message,compactExpected,compactActual)
		
	}
	return Assert.format(message,expected,actual)
	
} 

fun canBeCompacted(): Boolean{
	return expected != null &&
		actual != null && 
			areStringsEqual().not()
}
```

## 함수의 일관성
- compactExpectedAndActual에서 위 두 함수는 반환값이 없는데 아래 두 함수는 반환값이 있다.
- 일관성이 없으므로 반환값 없는 함수를 접두어, 접미어 인덱스를 반환하도록 변경
- 근데 findCommonPrefix가 findCommonSuffix보다 먼저 호출되어야 하는 시간적 결합이 존재
	- findCommonPrefixAndSuffix 내 findCommonPrefix를 호출

```kotlin
// Bad
private var compactExpected = ""
private var compactActual = ""

fun compactExpectedAndActual() {
	findCommonPrefix()
	findCommonSuffix()
	compactExpected = compactString(expected)
	compactActual = compactString(actual)
}
```

```kotlin
// Good
private var compactExpected = ""
private var compactActual = ""

fun compactExpectedAndActual() {
	findCommonPrefixAndSuffix()
	compactExpected = compactString(expected)
	compactActual = compactString(actual)
}

fun findCommonPrefixAndSuffix() {
	findCommonPrefix()
	//suffix 계산
}
```

## 명확한 이름
- suffixIndex가 사실은 suffixLength에 더 가까움
- 0부터 시작하는 것도 아니기 때문에 suffixLength로 변경
- 그리고 index는 0부터 시작이지만 length는 1부터 시작이기 때문에 +1을 했던 걸 지우고 +1이 없던 걸 -1을 해주는 등 수정

##  불필요한 if문 제거
- 코드를 리팩터링하면서 if문이 의미가 없어지는 경우 존재
- if를 지우고 구조를 다듬어서 더 깔끔하게 만들기
- if(suffixLength>0) 같은 거

## 결론
- 리팩터링은 코드가 어느 수준에 이를 때까지 시행착오를 반복하는 작업
    - 원래 코드로 다시 되돌아가는 경우도 흔하다
- 리팩터링이 불필요한 모듈은 없다.
    - 코드를 항상 깨끗하게 유지하는 책임은 모두에게 있다.