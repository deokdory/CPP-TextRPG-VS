# CPP-TextRPG-VS

## 작성 중 생긴 문제 및 몰랐던 사항, 실수 등
### 1. 부모 클래스의 static 멤버 변수 접근
부모 클래스인 `Character` 의 `private: static int num_of_charcter`에 접근 불가능
- **이유** - `static` 으로 선언된 경우 `private` 여도 자식 클래스에선 접근 가능할 줄 알았으나 불가능  
_(생각해보니 당연한 것..)_
- **해결** - `protected: static int num_of_character`

### 2. std::cout 에서 실수의 자리수 지정
> 참고 사이트1 : [learn.microsoft - 출력 스트림](https://learn.microsoft.com/ko-kr/cpp/standard-library/ios-functions?view=msvc-170#fixed)  
참고 사이트2 : [learn.microsoft - < iomanip >](https://learn.microsoft.com/ko-kr/cpp/standard-library/iomanip?view=msvc-170)  
참고 사이트3 : [모두의 코드 - C++레퍼런스 > iostream](https://modoocode.com/143)  
참고 사이트4 : [티스토리 : 즐거운 인생(미련없이 하자)](https://doitnow-man.tistory.com/234)

부동 소수점 표기법은 고정 표기법(fixed)과 과학적 표기법(scientific)이 있다.  
부동 소수점 전체 자릿수의 기본값은 6이다.

`#include <iomanip>` : Input Output Manipulatiors

추출/삽입 연산자들과 사용되어 플래그들과 서식 옵션들을 수정하는데 쓰이는 표준 조작자와 그것의 인자들을 정의한다.

`std::cout << setiosflags(std::ios::fixed)` 로 과학적 표기법을 제거할 수 있다.  
`std::cout << std::setprecision(2)` 부동소수점 숫자를  두 자리 숫자로 표시한다  
`fixed 와 setprecision(정수)` 를 같이 사용할 경우 부동소수점 숫자의 자리수를 지정할 수 있다.

< iomanip > 에는 이 외에도 필드의 너비 지정, 정렬 등 유용한 기능이 많아보이니 자주 찾아보고 익히게 될 것 같다.

지금은 여기까지만 알아두고 나머지를 진행하면서 찾아보자

- 추가
    - `std::cout << setiosflags(std::ios::fixed) << std::setprecision(2) <<...` 로 표기법과 부동소수점 전체 자리수를 지정한 후에는 이 표기법이 실수의 기본 표기법이 되어버려 다른 변수들도 영향을 받았다.
    - 따라서 형식을 지정해준 뒤에 `resetiosflags(std::ios::fixed)`나 `std::cout.copyfmt(std::iods(NULL))`과 같은 방법으로 형식을 해제해주는 작업이 필요해졌다
    - #define 으로 자주 쓰는 형식과 형식 리셋을 선언해두고 사용하였다.
    ```cpp
    #define SET_FORMAT_2PREC std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2) // 소수점 2자리 포맷
    #define RESET_FORMAT std::cout.copyfmt(std::ios(NULL)) // 포맷 리셋

    //사용 예
    void Character::PrintHp() const {
        std::cout << "HP : " << hp << "/" << max_hp << " (";
        SET_FORMAT_2PREC; // 포맷 변경
        std::cout << GetHpRemain() << "%)";
        RESET_FORMAT; // 포맷 리셋 
    }
    ```

### 3. 문자열 #include 했는데도 불러오지 못하는 이슈
미리 컴파일된 헤더에 `#include <string>`을 선언했는데도 string 관련 메소드들이 전부 먹통이 되는 현상 발생  
빌드 시 간헐적으로 먹통이 되다가 아얘 먹통이 되어버려서 원인 찾는 중  
> 23.02.17 추가 [참고사이트 1](https://dh8607.tistory.com/191), [참고사이트 2](http://stackoverflow.com/questions/3695174/visual-studio-2010s-strange-warning-lnk4042)

- 성공적으로 컴파일 시 LNK4042 경고가 발생해서 검색해봤다.
- project 파일에서 *.cpp 파일과 *.h 파일이 둘 다 source 파일로 설정되어 컴파일되고 있을 때 발생할 수 있다고 한다.
- 실제로 프로젝트를 언로드 후 열어보고 같은 상황인 것을 확인했다.

**비주얼 스튜디오에서 새 항목 추가 시에 실수로 파일 유형을 잘못 골라서 생성한 뒤 직접 확장자명을 바꾸어서 사용한 게 문제였다**

항목 추가 시엔 항상 신중하게 선택하고 혹시 잘못 선택했다면 삭제한 뒤 다시 새 항목 추가를 하도록 하자..

- 추가
    - 저렇게 작업을 했는데도 아직 해결이 안 되었다..

- 추가(23.02.20)
    - 문제가 생기는 파일들에 직접 <string>을 포함하니 다른 오류가 나타나서 타고 들어가다보니
    Hero 클래스 내부의 static 멤버 변수가 문제였다는 것을 확인했다.

    static 멤버 변수를 선언해두고 초기화를 안 해서 생기는 문제로 보인다.

    static 멤버 변수가 Hero 클래스 내부에 있을 이유가 딱히 없어서 전역 변수로 따로 빼내어 주었더니 문제가 모두 해결되었다.


### 4. 출력과 출력 사이 딜레이를 주고 싶다
```cpp
#include <iostream>
#include <windows.h>

std::cout << "DELAY1" << endl;
Sleep(1500); // windows.h의 함수 : 1.5초 딜레이( 1500ms )
std::cout << "DELAY2" << endl;
Slee(1500);
```
windows.h 를 포함했는데 나중엔 다른 기능을 찾아보도록 하자


### 5. new[] 후엔 꼭 delete[]를!!!!
```cpp
Enemy * enemy = new Enemy[3];
Skill * skills = new Skill[3];
...
delete enemy
delete skills
```
이런 실수를 해서 비주얼 스튜디오에서 아래와 같은 곳에 중단점을 트리거했다.
```cpp
//delete_scaler.cpp 
...
_CRT_SECURITYCRITICAL_ATTRIBUTE
void __CRTDECL operator delete(void* const block) noexcept
{
    #ifdef _DEBUG
    _free_dbg(block, _UNKNOWN_BLOCK); // <- 중단점 트리거
    #else 
    free(block);
    #endif
}
```
**new[] 후엔 꼭 delete[]를..!!!**


### 6. 아무데서나 변수를 선언할 수 있다지만..
  ```cpp
  if (int slot = GetNumOfPlayableHeroes(_Player) < PARTY_MAX) {
    //...
    }
```
이렇게 써놓고 작동되길 바랐던 나..ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ

slot 에 GetNumOfPlaybleHeroes(_Player)의 값이 할당될 줄 알았던 나였지만

**당연히** int slot 에는 뒤의 조건이 만족했는지에 따라 1과 0이 할당되었다.
