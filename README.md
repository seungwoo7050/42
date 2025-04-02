# Projects Repository
이 저장소는 공부할 때 진행한 여러 프로젝트들이 포함된 저장소입니다. 필요한 프로젝트만 선택적으로 클론하고 싶다면 아래의 절차를 참고하세요.

## Selective Cloning with Git `Sparse Checkout`
전체 저장소를 클론하지 않고, 필요한 프로젝트만 클론하려면 Git의 `Sparse Checkout` 기능을 활용할 수 있습니다.
예를 들어, 이 저장소에서 `MyLibc` 디렉터리에 위치한 프로젝트들만 클론하고 싶다면 다음의 절차를 따르세요:

### 1. Git 저장소 초기화 (클론 시 전체 파일은 다운로드하지 않음)
```bash
git clone --filter=blob:none --no-checkout https://github.com/seungwoo7050/42
cd 42
```
- `--filter=blob:none`: 파일의 내용을 최소화하여 히스토리 파일 다운로드를 줄입니다.
- `--no-checkout`: 바로 체크아웃하지 않고 `sparse checkout`을 위한 설정 준비를 합니다.

### 2. `Sparse Checkout` 활성화
```bash
git sparse-checkout init --cone
```
- `--cone` 옵션: 단일 디렉터리 기반 구조를 빠르게 지정할 수 있도록 해줍니다.

### 3. 필요한 디렉터리 선택
```bash
git sparse-checkout set c/MyLibc
```
위 명령어는 `MyLibc/` 디렉터리만 다운로드합니다. 필요에 따라 다른 디렉터리도 추가할 수 있습니다.

### 4. 파일 다운로드 및 프로젝트 준비
```bash
git checkout main
```
이제 선택한 디렉터리만 로컬에 클론되어, 용량 절약 및 빠른 작업 환경을 구축할 수 있습니다.

## 라이선스
이 프로젝트는 MIT 라이선스를 따르며, 자유롭게 사용, 수정, 배포할 수 있습니다.

## 문의 및 지원
이 프로젝트와 관련된 문의는 `seungwoo7050 [at] gmail [dot] com` 또는 GitHub Issues를 통해 문의해주세요.