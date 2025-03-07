# ft_transcendence

[![license MIT](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/animasyn/ft_transcendence/blob/master/LICENSE.txt)

> - [x] **Use a Framework as backend.** ✅
>   - [x] **Use a front-end framework or toolkit.** ✅
>   - [x] **Use a database for the backend.** ✅
> - [x] **Standard user management, authentication, users across tournaments.** ✅
> - [x] **Implementing a remote authentication.** ✅
> - [ ] Remote players.
> - [x] **Introduce an AI Opponent.** ✅
> - [ ] Implement WAF/ModSecurity with Hardened Configuration and HashiCorp Vault for Secrets Management.
> - [x] Implement Two-Factor Authentication (2FA) and JWT. ✅
> - [x] Use of advanced 3D techniques. ✅
>   - [ ] Multiple language supports.
>
> ---
>
> ✅ ✖️️ **(7)** ➕ 🤔 ✖️ **(0)** 🟰 **(7)** ≥ 7

## TABLE OF CONTENTS

- [Installation](#installation)
- [Build backend](#build-backend)
- [Build frontend](#build-frontend)
- [Dev setup](#dev-setup)
- [Team workflow](#team-workflow)

## INSTALLATION

Before cloning the repository, it's recommended to set up a Python virtual environment.

```bash
python3 -m pip install -U pip
python3 -m venv /path_to_new_virtual_environment
```

Clone this repository inside your virtual environment, for example:

```bash
cd /path_to_new_virtual_environment
git clone https://github.com/animasyn/ft_transcendence.git path_to_transcendence
```

Activate the virtual environment.

```bash
source /path_to_new_virtual_environment/bin/activate
```

Navigate to the repository's root directory and install the required dependencies. Be sure not to use the system-wide `pip`.

```bash
cd /path_to_new_virtual_environment/path_to_transcendence
python3 -m pip install -r requirements.txt
```

To deactivate the virtual environment:

```bash
deactivate
```

## BUILD

TODO: Containerize Django backend.

---

### BUILD BACKEND

현재, 개발 환경에 Docker가 접목되었기 때문에 빌드 시 로컬에서 Docker를 사용할 수 있어야 한다. 본인 개발 환경에서 Docker와 Docker Compose를 사용할 수 있다면 다음 섹션 [Build frontend ↗](#build-frontend)으로 건너뛰어도 좋다.

Homebrew로 Docker 설치 시 `--cask` 옵션을 주지 않을 경우 Docker Client만 설치하고, 옵션을 줄 경우 Docker Engine과 Desktop까지 함께 설치한다. 간단한 셋업을 원한다면 `cask`로 설치하고, Docker Desktop을 원하지 않는다면 `cask` 없이 설치하면 된다.

```bash
brew install docker
# alternatively: brew install --cask docker
```

`cask` 없이 설치했을 경우, Docker Engine을 대체할 runtime이 필요하다. 가볍고 미니멀한 세팅으로 [Colima](https://github.com/abiosoft/colima)를 추천한다.

```bash
brew install colima
```

앞으로 Docker를 사용할 때마다 Colima를 구동하면 된다. Colima가 자동으로 Docker Client가 사용할 engine의 context를 설정해준다.

```bash
# run this before you use Docker
colima start
```

Docker Compose는 Docker Client의 extension으로, 별도 설치가 필요하다.

```bash
brew install docker-compose
```

Homebrew로 Docker Compose를 설치할 경우 심볼릭 링크 문제로 Docker Client가 이를 인식하지 못한다. 다음과 같이 심볼릭 링크를 생성해 준다:

```bash
mkdir -p ~/.docker/cli-plugins
ln -sfn $HOMEBREW_PREFIX/opt/docker-compose/bin/docker-compose ~/.docker/cli-plugins/docker-compose
```

만약 이전 버전의 README 지침에 따라 로컬 PostgreSQL 서버를 설치했다면 이를 중지시키고 부팅 시 자동 시작 옵션을 꺼주어야 한다.

```bash
brew services stop postgresql@17
```

이제 `make`로 PostgreSQL과 Redis 컨테이너를 생성하고 Django dev server를 구동할 수 있다.

```bash
make
```

---

### BUILD FRONTEND

This project uses Yarn as its package manager. The recommended way to manage Yarn is to install it "per project" and through [Corepack](https://yarnpkg.com/corepack). To get started, install [nvm](https://github.com/nvm-sh/nvm) to manage Node.js versions.

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.1/install.sh | bash
```

Install the latest Node.js version.

```bash
nvm install node  # "node" is an alias for the latest version
```

Set the shell to use this version.

```bash
nvm use node
```

Verify Node.js is installed locally via nvm.

```bash
which node  # output should resemble ~/.nvm/versions/node/...
```

Corepack is shipped with Node.js. Enable it to add Yarn to your PATH.

```bash
corepack enable
```

Finally, run Yarn to install dependencies.

```bash
yarn  # run this at the repository root
```

---

NOTE: After finalizing the packages, we plan to use Yarn’s [Zero-installs](https://yarnpkg.com/features/caching#zero-installs) to avoid running `yarn` every time we switch branches.

---

### DEV SETUP

#### Vite Background

자바스크립트 빌더로는 [Vite](https://vite.dev/guide/)를 사용한다. 위 [Build frontend ↗](#build-frontend) 섹션에서 `yarn` 커맨드를 입력하면 React 패키지들과 함께 Vite.js도 설치된다. Vite는 prod 모드 (ie. Django의 `settings.DEBUG == False`) 때엔 여타 빌더처럼 [번들러](https://dev.to/sayanide/the-what-why-and-how-of-javascript-bundlers-4po9)를 이용하지만, dev 모드 (ie. `settings.DEBUG == True`) 중엔 [ES Module](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules)을 이용하여 브라우저가 패키지를 필요할 때 동적으로 import를 하도록 하므로, 개발 중에 `.js` 파일을 편집할 때 [수정 사항이 반영되어 브라우저에 렌더링(HMR)](https://webpack.js.org/concepts/hot-module-replacement/)되는 시간이 상대적으로 짧다는 장점이 있다. 단, 이 때 `.js` 파일 편집 사항이 발생했을 때 ('event') 이를 감지하고 브라우저에게 통지하는 메커니즘이 필요하다. 브라우저의 요청 없어도 통지가 가능해야하므로 이 메커니즘은 HTTP가 아니라 Websocket 프로토콜을 통해 실현되어야 한다. 이 역할을 하는 것이 Vite의 dev server이다. (이 역할 외에 많은 일도 한다.) 즉, 우리 개발 환경에 Django dev server와 Vite dev server, 두 가지 서버가 필요하다는 뜻이다.

#### Dev Server Setup

개발 서버를 셋업하기 위해 필요한 작업은 다음과 같다: 가장 먼저 다음 커맨드로 Vite dev server를 구동한다. (팁: 코드 에디터의 터미널 사용을 추천)

```bash
yarn run dev
```

그 다음, 터미널을 새로 열어서 `make`로 Django dev server를 구동한다.

```bash
make
```

참고로 Django가 Postgres와 제대로 통신하려면 Vite dev server가 먼저 구동되고 있어야 한다. (_ijo: Django 자체의 오류인지 세팅이 잘못된건지 왜 그런지 모르겠음._)

#### Development Server Workflow

브라우저가 8000번 포트로 접속하면, Django dev server가 `index/templates/index.html` 파일을 서브한다. 이 `index.html` 파일은 Vite dev server가 8002번 포트에서 서브하는 `main.jsx` 파일을 소스로 하는 `<script>` 태그를 포함한다. 또한, 이 `.html` 파일은 브라우저와 Vite dev server 사이의 Websocket 연결을 도와줄 Vite client 자바스크립트 모듈과 React HMR을 담당할 자바스크립트 모듈도 포함하고 있다. 이 두 모듈 역시 Vite dev server가 서브한다.

- Native ES Module: 브라우저가 `main.jsx` 로직에 따라 어떤 작업을 실행할 때 자바스크립트 모듈을 import한다면 Vite dev server가 해당 모듈을 찾을 수 있게 도와준다. (비록 import는 공식 ES2015 문법이지만 브라우저가 읽는 코드에 `import React from "react";` 이런 식으로 URL 없이 모듈을 import하면 브라우저가 해당 모듈을 찾을 수 없어서 에러를 던진다. 여타 프로그래밍 언어처럼 bare module을 찾을 수 있는 건 브라우저 엔진이 아니라 Node.js의 엔진이다. Vite server는 `.js` 파일을 서브할 때 코드 안의 bare module들을 찾아서 이를 해당하는 URL로 바꿔준다.)
- Hot module replacement(HMR): `.js` 파일에 편집 사항이 있으면 `yarn run dev` 스크립트 과정에서 생성되는 별도의 보조 프로세스가 이를 감지하고 Vite dev server에 이를 통보한다. Vite 서버는 어떤 모듈들을 로드해야할지 계산한 후 이를 Websocket을 통해 브라우저에 통보한다. 브라우저는 해당 모듈들을 React HMR 모듈을 통해 리렌더링한다.

## TEAM WORKFLOW

### GIT COMMIT CONVENTION

커밋 메시지 컨벤션은 [Conventional Commits 1.0.0](https://conventionalcommits.org)을 따른다.

- `<type>[optional scope]: <description>`은 한줄로 쓴다. 잘못된 예시: `fix: 이거 바꿈 \n fix: 이거도 바꿈 ㅋ`
- `<type>`은 다음 중 하나로 한다: `fix:`, `feat:`, `build:`, `chore:`, `docs:`, `refactor:`, `test:`
- 가급적 메시지 `[body]`를 상세하게 써주면 좋다: `fix: 이거 바꿈\n\n이거를 어떻게 바꿨냐면 하하하하`
- API가 바뀌었을 경우 가급적 BREAKING CHANGE `[footer]`를 달아준다. 이때 `<type>[optional scope]` 뒤에 느낌표도 달아주면 좋다. 예시: `fix(auth)!: 어쩌고 저쩌고 고침\n\n이렇게 저렇게 고침\n\nBREAKING CHANGE: 어디 어디 함수 시그너처 이렇게 저렇게 변경`
- 가급적 커밋은 기능 단위로 한다.

### FIGMA

화이트보딩은 Figma를 사용한다. [여기](https://www.figma.com/team_invite/redeem/NnI4B3PN5uRsMAF8N0gEy1)에서 액세스를 요청하라.

- UI 디자인은 [여기](https://www.figma.com/design/nus03sWaOMuYEg9bJCiAIr/design?m=auto&t=tK7LqY3Nl71oj5Fd-6)에서
- 앱 로직 플로우차트는 [여기](https://www.figma.com/board/WuRka80SB768WhqIfzgRxP/logic?t=tK7LqY3Nl71oj5Fd-6)에서

### STYLE ENFORCEMENT

TODO: 파이썬 린터는 [Ruff](https://docs.astral.sh/ruff)를 사용?

### API DOCUMENTATION

Web API는 HTTP API와 (WebSocket을 사용할 경우) WS API로 나뉜다.

- 팀원간 소통을 위해

  - HTTP API는 [OpenAPI v3.0.3](https://spec.openapis.org/oas/v3.0.3.html) 규격에 따라 [docs/openapi.yaml](https://github.com/animasyn/ft_transcendence/blob/master/docs/openapi.yaml) 파일에
  - WebSocket API는 [AsyncAPI v3](https://www.asyncapi.com/docs/reference/specification/v3.0.0) 규격에 따라 [docs/asyncapi.yaml](https://github.com/animasyn/ft_transcendence/blob/master/docs/asyncapi.yaml) 파일에

  각각 문서화한다. API를 추가하거나 변경할 경우 해당 문서에도 반영을 한다. 참고: [커밋 메시지 컨벤션 ↗](#git-commit-convention).

- 루트 디렉토리에서 `make api` 커맨드를 실행하면 Swagger UI를 이용해 `docs/openapi.yaml` 파일을 웹문서로 시각화할 수 있다. 선행 요건: [Build frontend ↗](#build-frontend)

  ```bash
  make api  # will open a web browser
  ```

- 참고:

  - [OpenAPI 3.0 Tutorial](https://support.smartbear.com/swaggerhub/docs/en/get-started/openapi-3-0-tutorial.html)
  - [OpenAPI 3.0 Docs](https://swagger.io/docs/specification/v3_0/about/)
  - [AsyncAPI 3.0 Tutorial](https://www.asyncapi.com/docs/tutorials)
