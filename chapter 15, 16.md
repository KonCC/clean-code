# 15장 JUnit 들여다보기

- ComparisonCompactor 모듈 테스트코드
- ABCDE와 ABXDE가 들어오면 AB[X]DE를 반환하는 모듈
- 테스트 케이스를 돌려본 후 모듈에 대한 코드 커버리지가 높을수록 모듈이 올바르게 동작한다
    - 커버리지가 100프로라는 것은 테스트 케이스가 모듈의 모든 If,for문을 수행한다는 의미

## 코드 개선하기

- f 접두어 제거
    - f는 아마 function이었을지 않을까..

개선전

```kotlin
private val fContextLength: Int
private val fExpected: String
private val fActual: String
private lateinit var fPrefix: Int
private lateinit var fSuffix: Int 
```

개선 후

```kotlin
private val contextLength: Int
private val expected: String
private val actual: String
private lateinit var prefix: Int
private lateinit var suffix: Int 
```

- 캡슐화되지 않은 조건문 & 명확하지 않은 이름
    - 부정문은 이해하기 어렵기 때문에 긍정문으로 변경한다.
    - this.expected와 expected는 서로 의미하는 바가 다른데 동일한 이름을 사용하여 this.이 붙었다.
        - 명확한 이름으로 지역변수 이름을 수정

```kotlin
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

- 함수 분리
    - compact라고 이름 붙였지만 canBeCompacted가 false인 경우는 압축되지 않음
    - 형식적인 문자열을 리턴한다는 의미도 없음
    - formatCompactedComparison()으로 변경
    - 그리고 압축을 해야 하는 경우는 따로 함수로 분리
        - 따로 분리를 하면서 지역변수가 멤버변수로 변경됨

```kotlin
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

- 함수의 일관성
    - compactExpectedAndActual에서 위 두 함수는 반환값이 없는데 아래 두 함수는 반환값이 있다.
    - 일관성이 없으므로 반환값 없는 함수를 접두어, 접미어 인덱스를 반환하도록 변경
    - 근데 findCommonPrefix가 findCommonSuffix보다 먼저 호출되어야 하는 시간적 결합이 존재
        - findCommonPrefixAndSuffix 내 findCommonPrefix를 호출

```kotlin
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

- 명확한 이름
    - suffixIndex가 사실은 suffixLength에 더 가까움
    - 0부터 시작하는 것도 아니기 때문에 suffixLength로 변경
    - 그리고 index는 0부터 시작이지만 length는 1부터 시작이기 때문에 +1을 했던 걸 지우고 +1이 없던 걸 -1을 해주는 등 수정

- 불필요한 if문 제거
    - 코드를 리팩터링하면서 if문이 의미가 없어지는 경우 존재
    - if를 지우고 구조를 다듬어서 더 깔끔하게 만들기
    - if(suffixLength>0) 같은 거

## 결론

- 리팩터링은 코드가 어느 수준에 이를 때까지 시행착오를 반복하는 작업
    - 원래 코드로 다시 되돌아가는 경우도 흔하다
- 리팩터링이 불필요한 모듈은 없다.
    - 코드를 항상 깨끗하게 유지하는 책임은 모두에게 있다.
 
---
# 16장 SerialDate 리팩터링

- JCommon 라이브러리에 존재하는 SerialDate 클래스 리팩터링하기
- SerialDate는 날짜를 표현하는 자바 클래스
    - Date 클래스는 너무 정밀하고 특정 날짜 하루를 표현하고 싶을 때 ex. 2015년 1월 15일 사용하기 위해 만든 클래스

# 1. 돌려보자

- 테스트 케이스를 돌려보자
- SerialDate의 기존 테스트 케이스의 테스트 커버리지는 50프로 정도였고 저자가 직접 정의한 테스트 케이스 중 실패하는 테스트 케이스도 존재
    - 일단 통과하지 않는 테스트 케이스가 돌아가도록 메서드 수정
- 모든 테스트 케이스가 돌아간다면 일단 SerialDate 코드가 제대로 돈다고 믿은 후, 코드를 ‘올바로’ 고쳐야 한다.
    - 테스트 케이스도 안 돌아가는데 리팩터링하면 안됨

# 2. 고쳐보자

- 불필요한 주석 삭제
    - 저작권 주석은 남겨두고 나머지 변경이력, html 주석은 삭제
- 클래스 이름 수정
    - Serial이 뜻하는 바가 일련번호를 사용해서 구현했기 때문
        - 일련번호라는 용어보다는 상대 오프셋이 더 정확
    - Serial Number를 이용해 구현했음을 암시하는데 사실은 추상 클래스라서 추상화 수준이 올바르지 못하다
        - Date or DayDate가 올바름
- enum class
    - static 상수를 모아놓은 클래스를 상속하는 대신 enum class로 빼기
- 변수 이동

```kotlin
final val EARLEST_DATE_ORDINAL = 2
final val LATEST_DATE_ORDINAL = 2958465
```

- EARLEST_DATE_ORDINAL이 이 클래스를 구현하는 SpreadSheetDate클래스의 날짜 표현방식을 위해 2로 표현해놓음
- DayDate와는 상관이 없으므로 SpreadSheetDate로 이동
- 생성 클래스
    - 구체적인 구현 정보에 관한 변수를 가지고 있음
        - 이 정보를 필요로 하는 파생 클래스로 내려야 함
        - 일반적으로 파생 클래스의 인스턴스로부터 구현 정보를 가져옴
        - getDate가 구현 정보를 필요로 하는 함수
            - getDate는 인스턴스를 반환하지만 내부는 인스턴스를 생성하지 않음
                - getXXXDayOfWeek → addDays → createInstance에서 SpreadSheetDate 인스턴스를 생성
    - ABSTRACT FACTORY 패턴을 이용해 DayDateFactory 클래스를 만들고 구체적인 구현 정보에 관한 변수들을 Factory 클래스로 옮김
- 사용하지 않는 변수 삭제
- 테스트 케이스만 호출하는 메서드인 경우 테스트 케이스와 메서드 전부 삭제
- 나머지는 이름 변경하고 안 쓰는 변수 삭제하고 if문 합치기 등등 쪼만쪼만하게 수정하는 것들

## 결론

- 불필요한 주석 삭제
- enum을 독자적인 클래스로
- 정적 변수,메서드 새 클래스(DateUtil)로 옮김
- 일부 추상메서드를 DayDate로 끌어올림
- enum class를 fromInt()나 toInt() 접근자로 index 필드에 접근
- 중복 메서드 삭제
- 숫자 1을 그대로 사용하지 않고 Month.JANUARY, Day.SUNDAY.toInt()처럼 이름을 부여줌
- 알고리즘 수정
