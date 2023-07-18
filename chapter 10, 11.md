# Chpater 10
## 클래스 체계
- 표준 자바 관례에 따른 내부 체계 순서
  1. static public 상수
  2. static private 변수
  3. private instance 변수
  4. public 함수
    - private 함수는 자신을 호출하는 public 함수 직후에 선언

**캡슐화**
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

**단일 책임 원칙(SRP)**
> 클래스나 모듈을 변경할 이유가 단 하나뿐이어야 한다.

- SRP는 OOP에서 중요하고 지키기 수월한 개념이지만, 많은 설계자가 무시한다.
  - '깨끗하고 체계적인 소프트웨어'보다 '돌아가는 소프트웨어'에 초점이 맞춰서 그렇다.
  - 자잘한 단일 책임 클래스가 많아지면 큰 그림을 이해하기 어려워진다고 우려한다.
    - 규모가 어느 수준에 이르는 시스템은 논리가 많고 복잡하므로 체계적인 정리가 필수다.

**응집도**
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

**응집도를 유지하면 작은 클래스 여럿이 나온다.**
- 큰 함수를 작은 함수 여럿으로 나누기만 해도 클래스 수가 많아진다.
- 예를 들어,
  - 큰 함수 일부를 작은 함수 하나로 빼고 싶다.
  - 근데 빼내려는 코드가 큰 함수에 정의된 변수 4개를 사용한다.
  - 그럼 작은 함수의 인수를 4개로 넣어줘야 할까?
  - 클래스로 분리하고, 4개의 변수를 인스턴스 변수로 승격하면 된다!

```java
// Bad
public class PrintPrimes {
	public static void main(String[] args) {
		final int M = 1000; 
		final int RR = 50;
		final int CC = 4;
		final int WW = 10;
		final int ORDMAX = 30; 
		int P[] = new int[M + 1]; 
		int PAGENUMBER;
		int PAGEOFFSET; 
		int ROWOFFSET; 
		int C;
		int J;
		int K;
		boolean JPRIME;
		int ORD;
		int SQUARE;
		int N;
		int MULT[] = new int[ORDMAX + 1];
		
		J = 1;
		K = 1; 
		P[1] = 2; 
		ORD = 2; 
		SQUARE = 9;
	
		while (K < M) { 
			do {
				J = J + 2;
				if (J == SQUARE) {
					ORD = ORD + 1;
					SQUARE = P[ORD] * P[ORD]; 
					MULT[ORD - 1] = J;
				}
				N = 2;
				JPRIME = true;
				while (N < ORD && JPRIME) {
					while (MULT[N] < J)
						MULT[N] = MULT[N] + P[N] + P[N];
					if (MULT[N] == J) 
						JPRIME = false;
					N = N + 1; 
				}
			} while (!JPRIME); 
			K = K + 1;
			P[K] = J;
		} 
		{
			PAGENUMBER = 1; 
			PAGEOFFSET = 1;
			while (PAGEOFFSET <= M) {
				System.out.println("The First " + M + " Prime Numbers --- Page " + PAGENUMBER);
				System.out.println("");
				for (ROWOFFSET = PAGEOFFSET; ROWOFFSET < PAGEOFFSET + RR; ROWOFFSET++) {
					for (C = 0; C < CC;C++)
						if (ROWOFFSET + C * RR <= M)
							System.out.format("%10d", P[ROWOFFSET + C * RR]); 
					System.out.println("");
				}
				System.out.println("\f"); PAGENUMBER = PAGENUMBER + 1; PAGEOFFSET = PAGEOFFSET + RR * CC;
			}
		}
	}
}
```

위 코드를 리팩토링하자.

```java
package literatePrimes;

public class PrimePrinter {
	public static void main(String[] args) {
		final int NUMBER_OF_PRIMES = 1000;
		int[] primes = PrimeGenerator.generate(NUMBER_OF_PRIMES);
		
		final int ROWS_PER_PAGE = 50; 
		final int COLUMNS_PER_PAGE = 4; 
		RowColumnPagePrinter tablePrinter = 
			new RowColumnPagePrinter(ROWS_PER_PAGE, 
						COLUMNS_PER_PAGE, 
						"The First " + NUMBER_OF_PRIMES + " Prime Numbers");
		tablePrinter.print(primes); 
	}
}
```

```java
package literatePrimes;

import java.io.PrintStream;

public class RowColumnPagePrinter { 
	private int rowsPerPage;
	private int columnsPerPage; 
	private int numbersPerPage; 
	private String pageHeader; 
	private PrintStream printStream;
	
	public RowColumnPagePrinter(int rowsPerPage, int columnsPerPage, String pageHeader) { 
		this.rowsPerPage = rowsPerPage;
		this.columnsPerPage = columnsPerPage; 
		this.pageHeader = pageHeader;
		numbersPerPage = rowsPerPage * columnsPerPage; 
		printStream = System.out;
	}
	
	public void print(int data[]) { 
		int pageNumber = 1;
		for (int firstIndexOnPage = 0 ; 
			firstIndexOnPage < data.length ; 
			firstIndexOnPage += numbersPerPage) { 
			int lastIndexOnPage =  Math.min(firstIndexOnPage + numbersPerPage - 1, data.length - 1);
			printPageHeader(pageHeader, pageNumber); 
			printPage(firstIndexOnPage, lastIndexOnPage, data); 
			printStream.println("\f");
			pageNumber++;
		} 
	}
	
	private void printPage(int firstIndexOnPage, int lastIndexOnPage, int[] data) { 
		int firstIndexOfLastRowOnPage =
		firstIndexOnPage + rowsPerPage - 1;
		for (int firstIndexInRow = firstIndexOnPage ; 
			firstIndexInRow <= firstIndexOfLastRowOnPage ;
			firstIndexInRow++) { 
			printRow(firstIndexInRow, lastIndexOnPage, data); 
			printStream.println("");
		} 
	}
	
	private void printRow(int firstIndexInRow, int lastIndexOnPage, int[] data) {
		for (int column = 0; column < columnsPerPage; column++) {
			int index = firstIndexInRow + column * rowsPerPage; 
			if (index <= lastIndexOnPage)
				printStream.format("%10d", data[index]); 
		}
	}

	private void printPageHeader(String pageHeader, int pageNumber) {
		printStream.println(pageHeader + " --- Page " + pageNumber);
		printStream.println(""); 
	}
		
	public void setOutput(PrintStream printStream) { 
		this.printStream = printStream;
	} 
}
```

```java
// 인스턴스화 하는 크래스가 아님을 주목
package literatePrimes;

import java.util.ArrayList;

public class PrimeGenerator {
	private static int[] primes;
	private static ArrayList<Integer> multiplesOfPrimeFactors;

	protected static int[] generate(int n) {
		primes = new int[n];
		multiplesOfPrimeFactors = new ArrayList<Integer>(); 
		set2AsFirstPrime(); 
		checkOddNumbersForSubsequentPrimes();
		return primes; 
	}

	private static void set2AsFirstPrime() { 
		primes[0] = 2; 
		multiplesOfPrimeFactors.add(2);
	}
	
	private static void checkOddNumbersForSubsequentPrimes() { 
		int primeIndex = 1;
		for (int candidate = 3 ; primeIndex < primes.length ; candidate += 2) { 
			if (isPrime(candidate))
				primes[primeIndex++] = candidate; 
		}
	}

	private static boolean isPrime(int candidate) {
		if (isLeastRelevantMultipleOfNextLargerPrimeFactor(candidate)) {
			multiplesOfPrimeFactors.add(candidate);
			return false; 
		}
		return isNotMultipleOfAnyPreviousPrimeFactor(candidate); 
	}

	private static boolean isLeastRelevantMultipleOfNextLargerPrimeFactor(int candidate) {
		int nextLargerPrimeFactor = primes[multiplesOfPrimeFactors.size()];
		int leastRelevantMultiple = nextLargerPrimeFactor * nextLargerPrimeFactor; 
		return candidate == leastRelevantMultiple;
	}
	
	private static boolean isNotMultipleOfAnyPreviousPrimeFactor(int candidate) {
		for (int n = 1; n < multiplesOfPrimeFactors.size(); n++) {
			if (isMultipleOfNthPrimeFactor(candidate, n)) 
				return false;
		}
		return true; 
	}
	
	private static boolean isMultipleOfNthPrimeFactor(int candidate, int n) {
		return candidate == smallestOddNthMultipleNotLessThanCandidate(candidate, n);
	}
	
	private static int smallestOddNthMultipleNotLessThanCandidate(int candidate, int n) {
		int multiple = multiplesOfPrimeFactors.get(n); 
		while (multiple < candidate)
			multiple += 2 * primes[n]; 
		multiplesOfPrimeFactors.set(n, multiple); 
		return multiple;
	} 
}
```

## 변경하기 쉬운 클래스
- 대다수 시스템은 지속적인 변경이 가해진다.
- 깨끗한 시스템은 클래스를 체계적으로 관리해 변경에 따르는 위험을 최대한 낮춘다.
- 새 기능을 추가할 때 시스템을 확장할 뿐 기존 코드를 변경하면 안된다.(OCP)

**변경으로부터 격리**
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
    // ... 
  }
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



# Chapter 11

## 시스템 제작과 시스템 사용을 분리하라
> 소프트웨어 시스템은 (애플리케이션 객체를 제작하고 의존성을 서로 '연결'하는) 준비 과정과 (준비 과정 이후에 이어지는) 런타임 로직을 분리해야 한다.

```java
public Service getService() {
  if (service == null)
    service = new MyServiceImpl(...);
  return service;
}
```

- 위의 코드를 초기화 지연(Lazy Initialization) 혹은 계산 지연(Lazy Evaluation)이라는 기법이다.
  - 장점
    - 실제로 필요할 때까지 객체를 생성하지 않으므로 불필요한 부하가 걸리지 않는다.
    - 어떤 경우에도 null 포인터를 반환하지 않는다.
  - 단점
    - `MyServiceImpl`의 생성자에 명시적으로 의존한다.(실제 런타임 시 사용하지 않더라도 의존성 해결이 안되면 컴파일이 안된다.)
    - `service`가 null인 경우와 아닌 경우, 두 방식을 모두 테스트해야한다.
    - `MyServiceImpl`이 모든 상황에 적합한 객체인지 모른다.

**Main 분리**
- 생성과 관련한 코드는 모두 main이나 main이 호출하는 모듈로 옮기고, 나머지 시스템은 모든 객체가 생성되었고 모든 의존성이 연결되었다고 가정한다.

![figure11-1](/images/chapter10,11/figure11-1.png)

- 의존성 화살표 방향에 주목하자. 모든 화살표가 main 쪽에서 애플리케이션 쪽을 향한다.
- 즉, 애플리케이션은 main이나 객체가 생성되는 과정을 전혀 모른다는 뜻이다.
- 단지 모든 객체가 적절히 생성되었다고 가정한다.

**팩토리 기법**
- 때로는 객체가 생성되는 시점을 애플리케이션이 결정할 필요도 생긴다.
- 예를 들어, (아래 이미지에서는) LineItem을 생성하는 시점은 `OrderProcessing`가 결정하지만, 구체적인 코드는 알 수 없다.
- 마찬가지로 의존성 화살표 방향이 main에서 애플리케이션 쪽으로 향한다.

![figure11-2](/images/chapter10,11/figure11-2.png)

**의존성 주입(DI)**
- 의존성 주입은 제어 역전(IoC) 기법을 의존성 관리에 적용한 메커니즘이다.
- 객체는 의존성 자체를 인스턴스로 만드는 책임을 지는 대신, main루틴이나 특수 컨테이너에게 맡긴다.
  - 의존성을 주입하는 방법으로 setter 메서드나 생성자 인수를 제공한다.
  - DI 컨테이너는 필요한 객체의 인스턴스를 만든 후 필요한 클래스에게 의존성을 설정한다.

```java
// Spring framwork는 자바 DI 컨테이너를 제공한다.
@Service
@RequiredArgsConstructor
public class AdminPostService {
  
  private final PostRepository postRepository;

  public AdminPostService(PostRepository postRepository) {
    this.postRepository = postRepository; // 의존성 주입
  }
  ...
}
```

## 확장
- 작은 마을이 성장하며 도로를 확장 공사할 때 "왜 처음부터 넓게 만들지 않았지?"하는 생각이 들 수 있다.
  - 성장할지 모른다는 기대로 처음부터 거대하게 공사하는게 올바르다고 정당화할 수 있는가?
- '처음부터 올바르게' 시스템을 만들 수 있다는 믿음은 미신이다.
  - 새로운 스토리가 생기면 거기에 맞춰 시스템을 조정하고 확장하면 된다.
- TDD, 리팩터링, Clean code는 코드 수준에서 시스템을 조정하고 확장하기 쉽게 만든다.

## 프록시
- Client에서 Server을 직접 호출하고, 처리 결과를 직접 받는다. 이것을 **직접 호출**이라 한다.
  - Client -> Server
- Client에서 Server을 직접 호출하는 것이 아니라 어떤 대리자를 통해서 대신 간접적으로 서버에 요청할 수도 있다. 이것을 **간접 호출**이라 한다.
  - 여기서 간접 호출하는 대상을 **프록시(Proxy)**라 한다.
    - Client -> Proxy -> Server

- 프록시는 Client와 Server의 중간에 있기 때문에 여러가지 일을 수행 할 수 있다.
  - 권한에 따른 접근 차단, 캐싱, 지연로딩을 수행하는 **접근 제어**
  - 서버의 기능에 다른 기능까지 추가해주는 **부가 기능 추가** (요청, 응답값을 변형해주거나 로그 기록 등)
  - 대리자가 또 다른 대리자를 호출하는 **프록시 체인**

### 프록시는 대체 가능해야 한다.
- 아무 객체나 프록시가 되는것은 아니다.
- 클라이언트 입장에서는 서버에 요청을 한건지, 프록시에게 요청을 한 것인지 조차 몰라야 한다.
- 즉, 서버와 프록시는 **같은 인터페이스**를 사용해야 하며, 클라이언트의 코드를 하나도 건들이지 않고 **프록시 추가와 런타임 객체 의존 관계 주입**만 변경해서 사용할 수 있어야 한다.
- Client는 ServerInterface를 의존해야 한다. 그리고 ServerInterface의 구현체로 실제 서버와 Proxy가 존재한다.
따라서 DI를 사용해서 대체 가능하다.

> JDK 동적 프록시는 인터페이스를 기반으로 프록시를 동적으로 만들어준다. 따라서 인터페이스가 필수이다.
{: .prompt-warning }

```java
public interface AInterface {
  String call();
}
```

```java
public class AImpl implements AInterface {
  public String call() {
    System.out.println("A 호출");
    return "a";
  }
}
```

```java
public class TimeInvocationHandler implements InvocationHandler {
  private final Object target;

  public TimeInvocationHandler(Object target) {
    this.target = target;
  }

  @Override
  public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
    System.out.println("TimeProxy 실행");
    long startTime = System.currentTimeMillis();

    Object result = method.invoke(target, args);

    long endTime = System.currentTimeMillis();
    long resultTime = endTime - startTime;
    System.out.println("TimeProxy 종료 resultTime = " + resultTime);
    return result;
  }
}
```

```java
public class Main {
  public static void main(String[] args) {
    AInterface target = new AImpl();
    TimeInvocationHandler handler = new TimeInvocationHandler(target);

    AInterface proxy = (AInterface) Proxy.newProxyInstance(AInterface.class.getClassLoader(), new Class[]{AInterface.class}, handler);
    proxy.call();
  }
}
```
```text
// 실행 결과
TimeProxy 실행
A 호출
TimeProxy 종료 resultTime = 0
```

## 테스트 주도 시스템 아키텍처 구축
- 소프트웨어 프로젝트에서는 BDUF(Big Design Up Front)는 해롭기까지 한다.
  - 처음 선택한 아키텍처의 사고 방식 때문에 변경을 쉽사리 수용하지 못하기 때문이다.
- 아주 단순하면서 잘 분리된 아키텍처로 결과물을 빠르게 출신 후, 기반 구조를 추가하며 조금씩 확장해 나가도 괜찮다.
