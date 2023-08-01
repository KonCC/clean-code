# 10장 클래스
## 클래스 체계
- 표준 자바 관례에 따른 내부 체계 순서
  1. static public 상수
  2. static private 변수
  3. private instance 변수
  4. public 함수
  	- private 함수는 자신을 호출하는 public 함수 직후에 선언

<br>

### 캡슐화
- 변수와 유틸리티 함수는 가능한 숨기는 것이 좋지만, 반드시 그래야 하는 것은 아님
- 테스트를 위해 protected로 선언하기도 한다.
- 하지만 캡슐화를 풀어주는 결정은 언제나 최후의 수단

## 클래스는 작아야 한다!
- 클래스를 설계할 때도 (함수와 마찬가지로) '작게'가 기본 규칙이다.
- '작다'의 기준은 클래스가 맡은 책임의 수이다.
- 클래스 이름은 해당 클래스 책임을 기술해야 한다.
  - 클래스 이름이 모호하거나 간결한 이름이 떠오르지 않는다면, 클래스의 책임이 많아서 그렇다.
  - 예를 들어, Processor, Manager, Super 등과 같은 모호한 단어가 있는 경우
- 클래스 설명은 if, and, or, but을 사용하지 않고 25단어 내외로 가능해야 한다.
  - 예를 들어, "~는 컴포넌트에 접근하는 방법을 제공**하며**, 버전을 추적하는 메커니즘을 제공한다"
  - 위의 경우 클래스의 책임이 너무 많다는 증거이다.

<br>

### 단일 책임 원칙(SRP)
> 클래스나 모듈을 변경할 이유가 단 하나뿐이어야 한다.

- SRP는 OOP에서 중요하고 지키기 수월한 개념이지만, 많은 설계자가 무시한다.
- '깨끗하고 체계적인 소프트웨어'보다 '돌아가는 소프트웨어'에 초점이 맞춰서 그렇다.
- 자잘한 단일 책임 클래스가 많아지면 큰 그림을 이해하기 어려워진다고 우려한다.
- 규모가 어느 수준에 이르는 시스템은 논리가 많고 복잡하므로 체계적인 정리가 필수다.

<br>

### 응집도
- 클래스는 인스턴스 변수 수가 작아야 한다.
- 각 클래스 메서드는 클래스 인스턴스 변수를 하나 이상 사용해야 한다.
  - 일반적으로 메서드가 변수를 많이 사용할수록 메서드와 클래스는 응집도가 더 높다.
- 일반적으로 응집도가 높은 클래스를 선호한다.
  - 클래스가 논리적인 단위로 묶인다는 의미이기 때문이다.
- 함수를 작게, 매개변수 목록을 짧게 유지하다 보면, 응집도가 낮아지게 된다.
  - 새로운 클래스로 쪼개야 한다는 신호이다.

```java
// Stack을 구현한 코드
// 응집도가 높다. (size()를 제외하곤 모든 메서드가 모든 변수를 사용한다.)

public class Stack {
    private int topOfStack = 0;
	List<Integer> elements = new LinkedList<Integer>();

	public int size() { 
		return topOfStack;
	}

	public void push(int element) { 
		topOfStack++; 
		elements.add(element);
	}

	public int pop() throws PoppedWhenEmpty { 
		if (topOfStack == 0)
			throw new PoppedWhenEmpty();
		int element = elements.get(--topOfStack); 
		elements.remove(topOfStack);
		return element;
	}
}
```

### 응집도를 유지하면 작은 클래스 여럿이 나온다.
- 큰 함수를 작은 함수 여럿으로 나누기만 해도 클래스 수가 많아진다.
- 예를 들어,
  - 큰 함수 일부를 작은 함수 하나로 빼고 싶다.
  - 근데 빼내려는 코드가 큰 함수에 정의된 변수 4개를 사용한다.
  - 그럼 작은 함수의 인수를 4개로 넣어줘야 할까?
  - 클래스로 분리하고, 4개의 변수를 인스턴스 변수로 승격하면 된다!


## 변경하기 쉬운 클래스
- 대다수 시스템은 지속적인 변경이 가해진다.
- 깨끗한 시스템은 클래스를 체계적으로 관리해 변경에 따르는 위험을 최대한 낮춘다.
- 새 기능을 추가할 때 시스템을 확장할 뿐 기존 코드를 변경하면 안된다.(OCP)

### 변경으로부터 격리
- 상세한 구현 클래스에 의존하는 클라이언트는 구현이 바뀌면 위험에 빠진다.
  - 인터페이스와 추상 클래스를 사용해 구현이 미치는 영향을 격리한다.
- 상세한 구현에 의존하는 코드는 테스트하기 어렵다.
  - 예를 들어, 5분마다 값이 달라지는 API를 직접 의존하는 클래스는 테스트하기 어렵다.
  - 대신 인터페이스를 만들어서 여기에 의존하자.
- 결합도를 줄이면 DIP 원칙을 따르게 된다.(구현이 아니라, 인터페이스에 의존해야 한다는 원칙)

```java
// 인터페이스 구현 클래스에 외부 API를 호출
public interface StockExchange { 
	Money currentPrice(String symbol);
}
```

```java
// 외부 API를 의존하던 것을 인터페이스에 의존하도록 변경
public Portfolio {
	private StockExchange exchange;
	public Portfolio(StockExchange exchange) {
		this.exchange = exchange; 
	}
...
```

```java
// 테스트 코드를 작성하기 쉬워졌다. (외부 API를 Mocking 가능하므로)

public class PortfolioTest {
	private FixedStockExchangeStub exchange;
	private Portfolio portfolio;

	@Before
	protected void setUp() throws Exception {
		// Mocking을 만들어서 portfolio에 주입
		exchange = new FixedStockExchangeStub(); 
		exchange.fix("MSFT", 100);
		portfolio = new Portfolio(exchange);
	}

	@Test
	public void GivenFiveMSFTTotalShouldBe500() throws Exception {
		portfolio.add(5, "MSFT");
		Assert.assertEquals(500, portfolio.value()); 
	}
}
```

