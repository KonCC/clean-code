# 6장 객체와 자료 구조

## 자료 추상화
- 구현을 감추려면 추상화가 필요하다
- 추상 인터페이스를 제공해 사용자가 구현을 모른 채 자료의 핵심을 조작할 수 있어야 진정한 의미의 클래스이다.
- 자료를 세세하게 공개하기보다는 추상적인 개념으로 표현하는 편이 좋다.

<br>

```kotlin
class Point {
  var x : Double
  var y : Double
}
```
구현이 외부로 노출되어, 개별적으로 좌표값을 읽고 설정할 수 있음

<br>

```kotlin
interface Point {
  fun getX() : Double
  fun getY() : Double
  fun setCartesian(x : Double, y : Double)
  fun getR() : Double
  fun getTheta() : Double
  fun setPolar(r : Double, theta : Double)
}
```
좌표를 설정할 때는 두 값을 한번에 설정하고 좌표를 읽을 때는 개별적으로 읽도로 접근 정책을 제한

<br>

```kotlin
interface Vehicle {
  fun getFuelTankCapacityInGallons() : Double
  fun getGallonsOfGasoline() : Double
}
```
단순히 연료상태에 대한 상태를 각 변수를 읽어와서 알려줌
<br>

``` kotlin
interface Vehicle {
	fun getPercentFuelRemaining(): Double
}
```
연료 상태를 백분율이라는 추상적인 개념으로 알려줌<br>
백분율이 어떤 정보를 통해서 오는지 드러나지 않는다.

## 자료/객체 비대칭
- 객체는 추상화 뒤로 자료를 숨긴채 자료를 다루는 함수만 제공
- 자료구조는 자료를 그대로 공개하며 별다른 함수는 제공하지 않음
- 자료구조를 사용하는 절차적인 코드 
  - 기존 자료구조를 변경하지 않으면서 새 함수를 추가하기 쉬움
  - 책에 Gemoetry 코드처럼 새로운 함수는 if문으로 무슨 구조일 때 ~ 나눠서 구현하면 됨
- 객체 지향 코드는
  - 기존 함수를 변경하지 않으면서 새 클래스를 추가하기 쉽다.
  - 위 경우에서 if문들을 각 자료구조 내에 구현하였기 때문에 기존 함수를 수정하면 모든 자료구조들이 구현한 함수를 수정해야 함
  
 
## 디미터 법칙
- 휴리스틱 (경험적인, 직관적 판단에 의하여 문제를 해결하는 방식) 
- 모듈은 자신이 조사하는 객체의 속사정을 몰라야 한다.
- 클래스 C의 메서드 f는 다음과 같은 객체의 메서드만 호출해야 한다.
  - 클래스 C
  - f가 생성한 객체
  - f 인수로 넘어온 객체
  - C 인스턴스 변수에 저장된 객체
  
``` kotlin
val outputDir:String = ctxt.getOptions().getScratchDir().getAbsolutePath()
```
- 메서드가 반환하는 객체의 메서드는 호출하면 안된다.
- 위와 같은 코드를 기차충돌이라고 부르는다. 일반적으로 조잡하다고 여겨지므로 피하는 편이 좋다.
- 반환하는 값들이 전부 자료구조라면 내부구조가 노출되므로 디미터 법칙에 적용되지 않는다.
- 근데 객체라면 디미터 법칙을 어긴 것

## 구조체 감추기
- 잡종 구조
  - 자료구조와 객체가 섞여있는 형태
  - 중요한 기능을 하는 함수와 (객체지향) 공개 조회/설정 함수로 비공개 변수를 노출하는 함수 (자료구조)가 섞여있어 새로운 함수는 물론 새로운 자료 구조도 추가하기 어려움

<br>

``` kotlin
val outputDir: String = ctxt.getOptions().getScratchDir().getAbsolutePath()
```
여기서 ctxt가 진짜 객체라면 내부 구조를 감춰야하기 때문에 줄줄이 늘어놓으면 안 된다.<br>
ctxt에게 뭔가를 하라고 해야지 원하는 자료 구조를 반환하게 하면 안된다.

<br>

``` kotlin
val bos: BufferedOutputStream = ctxt.createScratchFileStream(classFileName)
```
ctxt는 내부 구조를 드러내지 않으면 모듈에서는 자신이 몰라야 하는 객체들을 탐색할 필요가 없어진다.


## 자료 전달 객체
- 공개 변수만 있고 함수가 없는 클래스 
- Data Transfer Object (DTO)라 부른다.
- 데이터베이스와 통신하거나 가공되지 않은 데이터베이스 정보를 애플리케이션코드에서 사용할 객체로 변환하는 단계에서 사용
```kotlin
data class User(
    val nickname: String,
    val uid: String,
    val lastLogin: Long,
    val isGuest: Boolean,
)

data class UserDTO(
    @SerializedName("nickname") val nickname: String,
    @SerializedName("uid") val uid: String,
    @SerializedName("lastLogin") val lastLogin: Long,
    @SerializedName("isGuest") val isGuest: Boolean,
)

fun User.toUserDto(): UserDTO {
    return UserDTO(
        nickname = nickname,
        uid = uid,
        lastLogin = lastLogin,
        isGuest = isGuest
    )
}

```

- 비공개 변수를 조회/설정 함수로 조작하는 좀 더 일반적인 형태의 빈(bean)구조도 있다.


### 활성 레코드
- DTO의 특수한 형태
- 자료구조에서 조회/설정 뿐만 아니라 save, find같은 탐색 함수도 제공
- 활성레코드는 데이터베이스 테이블이나 다른 소스에서 자료를 직접 변환한 결과
- 활성 레코드는 자료구조로 취급한다.
  - 비즈니스 규칙을 담으면서 내부 자료를 숨기는 객체는 따로 생성해야 한다.
  

## 결론
 - 객체
   - 동작을 공개하고 자료를 숨김
   - 새 객체 타입 쉬움
   - 새로운 동작 추가 어려움
 - 자료구조
   - 별다른 동작없이 자료를 노출
   - 새 동작 추가 쉬움
   - 새 자료구조 추가 어려움
 - 시스템 구현 시, 새로운 자료 타입 추가 or 새로운 동작 추가 유연성의 필요에 따라 객체 or 자료구조 선택
