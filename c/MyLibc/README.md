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

## 3. `git sparse-checkout`을 사용한 선택적 클론 방법
`mylibc` 프로젝트만 클론하고 싶을 경우, Git의 `Sparse Checkout` 기능을 활용하면 전체 저장소를 다운로드하지 않고 특정 디렉토리만 선택적으로 클론할 수 있습니다.

다음은 `mylibc` 관련 디렉토리만 클론하는 절차입니다:

### 3.1. Git 저장소 클론 (초기화만 수행)
```bash
git clone --filter=blob:none --no-checkout https://github.com/seungwoo7050/42
cd 42
```
- `--filter=blob:none`: 히스토리 파일 다운로드 최소화
- `--no-checkout`: 바로 체크아웃하지 않고 sparse 설정 준비

### 3.2. Sparse Checkout 활성화
```bash
git sparse-checkout init --cone
```
- `--cone` 옵션은 단일 디렉토리 기반 구조를 빠르게 지정할 수 있도록 함

### 3.3. 필요한 디렉토리 선택
```bash
git sparse-checkout set src
```
- 이 예시 명령어는 `src/` 디렉토리만 다운로드합니다. 필요시 `include`, `docs` 등 추가 가능

### 3.4. 파일 다운로드 및 프로젝트 준비
```bash
git checkout main
```
이제 지정한 디렉토리만 로컬로 클론되며, 용량 절약 및 빠른 작업이 가능합니다.

## 4. 사용법
### 4.1. 헤더포함
```c
#include "mylibc.h"
```

### 4.2. 링크
컴파일 시 `mylibc.a` 라이브러리를 링크하여 사용합니다.
```bash
cc -Wall -Wextra -Werror your_program.c mylibc.a -o your_program
```

## 5. 라이선스
이 프로젝트는 MIT 라이선스를 따르며, 자유롭게 사용, 수정, 배포할 수 있습니다.

## 6. 문의 및 지원
이 프로젝트와 관련된 문의는 `seungwoo7050 [at] gmail [dot] com` 또는 GitHub Issues를 통해 문의해주세요.