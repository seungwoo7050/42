# MyLibc
이 프로젝트는 42 과제인 Libft를 기반으로 기존의 제한사항을 무시하고, 모던하고 효율적이게 재설계한 라이브러리입니다. 이 라이브러리는 표준 C 라이브러리의 함수들과 연결 리스트 관련 함수들을 직접 구현하였습니다.

## 1. 프로젝트 개요

- 라이브러리 이름: `mylibc.a`
- 언어: C
- 특징:
    - 일부 libc 함수들을 현대적인 C Style 로 작성
    - 연결 리스트 데이터 구조 구현 및 조작
    - 함수 포인터와 콜백 함수를 활용한 범용 함수 구현

## 2. 빌드 및 실행 방법
### 기본 빌드
```bash
make
```

### 보너스 빌드
```bash
make bonus
```

### 클린 및 재빌드
```bash
# 객체 파일 삭제
make clean

# 라이브러리 및 바이너리 삭제
make fclean

# 재빌드
make re
```

## 3. 사용법
### 3.1. 헤더포함
```c
#include "mylibc.h"
```

### 3.2. 링크
컴파일 시 `mylibc.a` 라이브러리를 링크하여 사용합니다.
```bash
cc -Wall -Wextra -Werror your_program.c mylibc.a -o your_program
```