# 12장 창발성

## 창발적 설계로 깔끔한 코드를 구현하자.

창발성이라는 말이 조금은 생소할 수 있다. 창발성이란, 복잡한 시스템이나 구조의 특성이 간단한 구성 요소들의 상호작용을 통해 나타나는 현상을 말한다. 다시 말해, 간단한 부분들의 조합으로 인해 전체적인 시스템이나 패턴이 생겨나는 것을 의미한다.

아래 네가지 규칙을 준수한다면 소프트웨어 설계 품질은 크게 높아진다.

- 모든 테스트를 실행한다.
- 중복을 없앤다.
- 프로그래머 의도를 표현한다.
- 클래스와 메서드 수를 최소로 줄인다.

## 단순한 설계 규칙 1 : 모든 테스트를 실행하라

테스트가 불가능한 시스템은 검증이 불가능하다.

그리고 검증이 불가능한 시스템은 절대 출시하면 안된다.

결합도가 높으면 테스트 케이스를 작성하기 어려우므로, **DIP**와 같은 원칙을 적용하고, **의존성 주입, 인터페이스,**

**추상화** 같은 도구들을 사용해 결합도를 낮춰 설계 품질을 높이자.

테스트 케이스를 만들고 돌리기만해도, 시스템은 낮은 결합도와 높은 응집력이라는, 객체 지향 방법론이 지향하는

목표를 저절로 달성한다.

## 단순한 설계 규칙 2 : 중복을 없애라

중복을 없애는 것은 리팩터링의 가장 주요한 첫 번째 단계이다.

예를 들어, 다음 예시를 보자.

```java
public class Example {
    private int[] data;

    public int size() {
        if (data != null) {
            return data.length;
        } else {
            return 0;
        }
    }

    public boolean isEmpty() {
   	    if (data != null) {
            return false;
        } else {
            return true;
        }
    }
}
```

해당 클래스의 두 함수 size(), isEmpty()는 각각 개수를 반환하는 역할과 개수를 확인 후 부울값을 반환하는 역할을 한다.

두 함수를 봤을때, isEmpty에서도 size와 비슷한 역할을 수행하는 것을 볼 수 있다. 따라서 다음과 같이 구현하여

중복을 제거해줄 수 있다.

```java
public class Example {
    private int[] data;

    public int size() {
        if (data != null) {
            return data.length;
        } else {
            return 0;
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }
}
```

### Template Method 패턴 기법을 사용하라.

Template Method 패턴은 고차원 중복을 제거할 목적으로 자주 사용하는 기법이다.

다음 예시를 살펴보자.

```java
public class VacationPolicy {
	public void accureUSDDivisionVacation() {

    // 지금까지 근무한 시간을 바탕으로 휴가 일수를 계산하는 코드
    // ...
    // 휴가 일수가 미국 최소 법정 일수를 만족하는지 확인하는 코드
    // ...
    // 휴가 일수를 급여대장에 적용하는 코드
    // ...
    }

    public void accureKRWDivisionVacation() {

    // 지금까지 근무한 시간을 바탕으로 휴가 일수를 계산하는 코드
    // ...
    // 휴가 일수가 한국 최소 법정 일수를 만족하는지 확인하는 코드
    // ...
    // 휴가 일수를 급여대장에 적용하는 코드
    // ...
    }

}
```

위 코드에서 최소 법정 일수를 계산하는 코드만 제외한다면, 두 메서드는 거의 동일하다.

최소 법정 일수를 계산하는 알고리즘만 살짝씩 변하게 되는데,

이때 다음과 같이 Templeat Method 패턴을 적용하면 눈에 들어오는 중복을 제거할 수 있다.

```java
abstract public class VacationPolicy {
	public void accureVacation() {
    	calculateBaseVacationHours();
        alterForLegalMinimums();
        applyToPayroll();
    }

    private void calculateBaseVacationHours(){
    	//지금까지 근무한 시간을 바탕으로 휴가 일수를 계산하는 코드
    }
    abstract protected void alterForLegalMinimums(); //하위 클래스에서 구현
    private void applyToPayroll(){
        //휴가 일수를 급여대장에 적용하는 코드
    }
}

public class USVacationPolicy extends VacationPolicy {
    @Override protected void alterForLegalMinimums(){
        //미국 최소 법정 일수를 사용한다.
    }
}

public class KRVacationPolicy extends VacationPolicy {
    @Override protected void alterForLegalMinimums(){
        //한국 최소 법정 일수를 사용한다.
    }
}
```

## 단순한 설계 규칙 3 : 표현하라

내가 짠 코드를 타인이 보고 유지보수를할 때에는 코드를 짜는 사람만큼 이해하기 힘들다.

이후 코드를 이해하기 쉽게 하기 위해서는 **개발자의 의도**를 분명히 표현해야 한다.

따라서 몇가지 규칙을 준수하자.

1.  좋은 이름을 선택한다. 이름과 기능이 일치하도록 하자.
2.  함수와 클래스 크기를 가능한 줄인다. SRP 원칙을 준수하여 이름짓기, 구현하기, 이해하기 쉽게 한다.
3.  표준 명칭을 사용한다. 클래스가 COMMAND나 VISITOR 같은 표준 패턴을 사용해 구현된다면        클래스 이름에 패턴 이름을 넣어주자.
4.  단위 테스트 케이스를 꼼꼼히 작성한다. 잘 만든 테스트 케이스를 읽어보기만 해도, 클래스 기능이 한눈에 들어온다.

나중에 코드를 읽을 사람은 바로 자신일 가능성이 가장 높다는 사실을 명심하자.

훗날의 나를 위해서라도 코드를 꼼꼼히, 깔끔하게 작성하는 노력을 조금 더 들여보자.

## 단순한 설계 규칙 4 : 클래스와 메서드 수를 최소로 줄여라

중복을 제거하고 SRP를 준수하다보면 조그만 클래스와 메서드가 수없이 늘어날 수밖에 없다.

그런데 이제와서 클래스와 메서드 수를 줄이라니 모순적이게 느껴질 수도 있다.

물론 함수와 클래스 크기를 작게 유지하는 것이 가장 중요하고 앞선 규칙들에 비해 우선 순위가 가장 낮지만,

시스템 크기를 작게 유지하는 것 또한 중요하다는 것을 늘 명심하자.

## 단순한 설계 규칙 2~4 : 리팩터링

코드를 추가할 때마다 설계를 조감하는 것이 좋다.

이때에는 매번 테스트 케이스를 돌려 기존 시스템이 깨지는지 확인하자.

지금까지 배웠던 모든 기법

- 응집도를 높이고
- 결합도를 낮추고
- 관심사를 분리하고
- 시스템 관심사를 모듈로 나누고
- 함수와 클래스 크기를 줄이고
- 더 나은 이름을 선택하고

등, 다양한 기법들을 총동원하여 리팩터링을 진행한다.

즉, 단순한 설계 규칙 2~4에 해당하는 내용들을 리팩터링 단계에서 진행한다.

## 결론

앞서 설명한 단순한 설계 규칙들을 따른다면, 오랜 경험 후에나 익힐 우수한 기법과 원칙을 활용할 수 있다.
