#!/bin/sh

if [ ! -e "/run/mysqld/mysqld.sock" ]; then # MariaDB 소켓 파일이 존재하지 않는 경우

    mariadb-install-db --user=mysql --datadir=/var/lib/mysql --skip-test-db > /dev/null 2>&1

    mkdir -p /run/mysqld
    chown -R mysql:mysql /run/mysqld

    # MariaDB 서버를 백그라운드에서 실행
    mysqld &

    # MariaDB 서버 실행 대기, 30초 후 실행되지 않으면 종료
    mysqladmin --silent --wait=30 ping || exit 1 
    pid="$!"

    # 데이터베이스 및 사용자 생성
    mysql -uroot <<-EOSQL
        CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
        GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
        FLUSH PRIVILEGES;
EOSQL
    
    # 서버 종료
    mysqladmin -uroot -p"${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$pid"
fi

exec mysqld

####################################################################################################################
# MariaDB 초기 설정 과정

# 1. 데이터베이스 디렉토리 확인
# '/var/lib/mysql/mysql' 디렉토리가 존재하지 않는 경우, MariaDB 데이터베이스가 초기화되지 않은 것으로 판단

# 2. MariaDB 데이터베이스 초기화
# 'mysql_install_db --user=mysql --datadir=/var/lib/mysql' 명령어를 통해 MariaDB 데이터베이스 파일을 초기화
# 데이터 베이스의 시스템 테이블을 설정한다.
# --user 옵션은 명령어를 실행할 사용자를 지정하는 것으로, 'mysql' 사용자로 실행함으로써 보안을 강화한다.
# 즉, MYSQL_USER 와는 관련 없는 호스트 시스템의 사용자 계정을 의미한다.

# 3. 임시 MariaDB 서버 시작
# 'mysqld --user=mysql --skip-networking --socket=/var/lib/mysql/mysql.sock &'
# '--skip-networking' 옵션은 네트워크 연결을 거부하고, 로컬 소켓을 통해 연결을 수락한다.
# '--socket' 옵션은 소켓 파일의 경로를 지정하는 것으로, '/var/lib/mysql/mysql.sock' 파일을 사용한다.
# '&'는 백그라운드에서 실행하겠다는 의미로, 명령어를 실행한 후 즉시 프롬프트로 돌아온다.
# 초기 설정을 위해 임시로 서버를 실행하고 필요한 데이터베이스 및 사용자를 생성하는 것은 일반적인 방법이다.

# 4. MariaDB 서버가 실행되기를 대기
# 'mysqladmin --silent --wait=30 ping || exit 1' 명령어를 통해 MariaDB 서버가 정상적으로 실행될 때까지 대기한다.

# 5. 기본 데이터베이스와 사용자 생성
# 'mysql -uroot <<-EOSQL ... EOSQL' 명령어를 통해 MariaDB 서버에 접속한다.
# <<-EOSQL은 이후의 명령어를 표준 입력으로 받는다는 의미로, EOF(End Of File)와 같은 역할을 한다.

# 6. MariaDB 서버 종료
# 'mysqladmin shutdown' 명령어를 통해 초기 설정이 끝나면 MariaDB 서버를 종료한다.
# 'wait "$pid"' 명령어를 통해 MariaDB 서버의 프로세스가 완전히 종료될 때까지 대기한다.

# 7. MariaDB 서버 시작
# 'exec "$@"' 명령어를 통해 MariaDB 서버를 시작한다.

# 스크립트 문법
# #!(shebang) : 셸 스크립트를 실행할 인터프리터를 지정한다.
# if [ 조건 ]; then 명령; fi : 조건문을 사용하여 특정 조건에 따라 명령을 실행한다.
# '-d' : 디렉토리 존재 여부 확인
# '-e' : 파일 존재 여부 확인
# '-r', '-w', '-x' : 파일 읽기, 쓰기, 실행 권한 확인
# '&' : 백그라운드 실행
# '$!' : 마지막으로 백그라운드에서 실행된 프로세스의 PID를 의미하는 특수 변수('$'는 변수를 참조할 때 쓰는 기본적인 기호).
# '$@' : 스크립트에 전달된 모든 인자를 의미하는 특수 변수
# '<<-EOSQL ... EOSQL' : 여러 줄의 명령어를 표준 입력으로 받는다.
# 'eq', 'ne', 'lt', 'le', 'gt', 'ge' : 숫자 비교 연산자, 각각 'equal', 'not equal', 'less than', 'less than or equal', 'greater than', 'greater than or equal'을 의미한다.

# MariaDB 내부 명령어
# 'CREATE DATABASE': 데이터베이스 생성
# 'CREATE USER': 사용자 생성
# 'GRANT': 사용자에게 권한 부여
# 'ALTER USER': 사용자 정보 변경(예: 비밀번호 변경)
# 'FLUSH PRIVILEGES': 변경된 권한을 즉시 적용
# 'IF NOT EXISTS': 데이터베이스나 테이블이 존재하지 않을 때만 명령을 실행, 해당 객체가 이미 존재하면 무시한다.

# 1. 데이터베이스 및 테이블 관리
# 'SHOW DATABASES': 데이터베이스 목록 조회
# 'USE 데이터베이스명': 데이터베이스 선택
# 'SHOW TABLES': 테이블 목록 조회
# 'DESC 테이블명': 테이블 구조 조회
# 'DROP DATABASE 데이터베이스명': 데이터베이스 삭제
# 'DROP TABLE 테이블명': 테이블 삭제

# 2. 데이터 조작(DML: Data Manipulation Language)
# 'SELECT': 데이터 조회
# 'INSERT INTO': 데이터 삽입
# 'UPDATE': 데이터 수정
# 'DELETE': 데이터 삭제

# 3. 트랜잭션 관리
# 'START TRANSACTION': 트랜잭션 시작
# 'COMMIT': 트랜잭션 수행 결과를 DB에 반영
# 'ROLLBACK': 트랜잭션 취소

# 4. 사용자 및 권한 관리
# 'SHOW GRANTS': 사용자 권한 조회
# 'REVOKE 권한 ON 데이터베이스명.* FROM 사용자명': 특정 사용자에게 부여된 권한 취소
# 'DROP USER 사용자명': 사용자 삭제

# 5. 인덱스 및 성능 관리
# 'CREATE INDEX': 인덱스 생성
# 'SHOW INDEX': 인덱스 목록 조회
# 'DROP INDEX': 인덱스 삭제
# 'EXPLAIN': 쿼리 실행 계획 확인, 성능 분석과 최적화에 사용

# 6. 백업 및 복구
# 'mysqldump': 데이터베이스 백업
# 'SOURCE 파일명': SQL 파일을 읽어 데이터베이스에 적용(복구)

# 7. 기호 설명
# 백틱(``): 데이터베이스, 테이블, 컬럼 등의 식별자를 감싸는 기호
# 달러 기호($): 변수를 참조할 때 사용하는 기호, SQL이 아닌 쉘 스크립트에서 사용
# 세미콜론(;): SQL 명령어의 끝을 나타내는 기호
# 역슬래시(\): 이스케이프 문자
# 단일/이중 인용부호('', ""): 문자열 리터럴
# 백슬래시(/): 특수 문자를 이스케이프할 때 사용하는 기호
# __: 한 줄 주석을 의미하는 기호
# /* */: 여러 줄 주석을 의미하는 기호
# IF NOT EXISTS: 데이터베이스나 테이블이 존재하지 않을 때만 명령을 실행, 해당 객체가 이미 존재하면 무시한다.

# '@': 사용자가 접속할 수 있는 호스트를 지정할 때 사용하는 기호
# 'username'@'host' 형태로 사용자와 호스트를 지정할 수 있으며, 'user'@'%'는 모든 호스트를 의미한다.
# 'username'@'localhost'는 로컬에서만 접속 가능한 사용자를 의미한다.

# '*'는 모든 데이터베이스를 의미한다.
# 'database.*'는 특정 데이터베이스의 모든 테이블을 의미한다.
# 'GRANT ALL PRIVILEGES ON database.* TO 'user'@'host';'는 특정 사용자에게 특정 데이터베이스의 모든 권한을 부여한다.

### 디버깅용 서버 준비 대기 스크립트
#for i in {30..0}; do # 30초 대기
#    if mysqladmin ping > /dev/null 2>&1; then # MariaDB 서버 실행 여부 확인
#        break # MariaDB 서버 실행되면 종료
#    fi
#    echo 'MariaDB 서버 준비 중...'
#    sleep 1 # 1초 대기
#done
#if [ "$i" = 0 ]; then # 30초 대기 후 MariaDB 서버 실행되지 않으면 종료
#    echo 'MariaDB 서버 준비 실패'
#    exit 1
#fi