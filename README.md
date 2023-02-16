# CPP-TextRPG-VS

## 작성 중 생긴 문제 및 몰랐던 사항들
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
[이것이 원인인 듯](https://dh8607.tistory.com/191)
