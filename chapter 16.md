# 16장 SerialDate 리팩터링

- JCommon 라이브러리에 존재하는 SerialDate 클래스 리팩터링하기
- SerialDate는 날짜를 표현하는 자바 클래스
    - Date 클래스는 너무 정밀하고 특정 날짜 하루를 표현하고 싶을 때 ex. 2015년 1월 15일 사용하기 위해 만든 클래스

## 1. 돌려보자

- 테스트 케이스를 돌려보자
- SerialDate의 기존 테스트 케이스의 테스트 커버리지는 50프로 정도였고 저자가 직접 정의한 테스트 케이스 중 실패하는 테스트 케이스도 존재
    - 일단 통과하지 않는 테스트 케이스가 돌아가도록 메서드 수정
- 모든 테스트 케이스가 돌아간다면 일단 SerialDate 코드가 제대로 돈다고 믿은 후, 코드를 ‘올바로’ 고쳐야 한다.
    - 테스트 케이스도 안 돌아가는데 리팩터링하면 안됨

## 2. 고쳐보자

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
