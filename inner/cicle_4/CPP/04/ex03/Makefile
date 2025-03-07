# PROGRAM_NAME
NAME		= game

# COMPILE_OPTION
CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++98

# SRCFILE
FILES		= AMateria Character Cure Ice MateriaSource ICharacter IMateriaSource
SRCS		= $(FILES:=.cpp) main.cpp
OBJDIR	= .OBJ
OBJS		= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))
HEADER	= $(FILES:=.hpp)

# ANSI COLOR CODE
GREEN		= \e[92;5;118m
YELLOW	= \e[93;5;226m
RESET		= \e[0m

# SHELL SCRIPT
RM			= rm -rf
PRINT		= printf
MAKEDIR	= mkdir -p	
# -p : 디렉터리의 재귀적 생성 및 이미 생성하려하는 디렉터리가 존재하는 경우 명령어 생략
# dir: 파일 경로의 디렉터리 부분을 추출하는데 사용('상대 경로 생성' 또는 '파일 위치 조작'에 유용)
#		사용법: $(dir (디렉터리 경로를 추출할 파일 명))

# MAKEFILE SYMBOL
CUR_TAR	= $@
CUR_OBJ = $<

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):	$(OBJS)	$(HEADER)
	@$(CC)	$(OBJS)	-o $(NAME)
	@$(PRINT) "$(GREEN)- 컴파일 완료.\n$(RESET)"

$(OBJDIR)/%.o: %.cpp $(HEADER)
	@$(MAKEDIR) $(dir $(CUR_TAR))
	@$(CC)	$(FLAGS)	-c $(CUR_OBJ) -o $(CUR_TAR)

clean:
	@$(RM) $(OBJDIR) $(OBJS)
	@$(PRINT) "$(YELLOW)- 오브젝트파일 삭제 완료.$(RESET)\n"

fclean:	clean
	@$(RM) $(NAME)
	@$(PRINT) "$(YELLOW)- 실행파일 삭제 완료.$(RESET)\n"

re: fclean all

# General Rules
# 컴파일 플래그:
# 	-Wall -Wextra -Werror -std=c++98
# 디렉토리 명명규칙:
# 	ex00, ex01, ex02 ...
# 클래스 명명규칙:
# 	UpperCamelCase 형식
# 파일명 명명규칙:
# 	담고있는 클래스의 이름과 동일
# 출력방식:
# 	별다른 명시가 없는 경우, 표준 출력으로 출력 + 개행문자로 종료
# 코드 작성 방식:
# 	최대한 C 보다는 C++ 스타일로 작성
# 	외부 라이브러리 사용 금지(= C++11과 Boost 라이브러리 금지)
# 	printf, alloc free 함수 사용 금지
# 	namespace, friend 키워드 사용 금지
# 	Module02 - Module08 명시된 경우를 제외하고 Orthdox Canonical Form 으로 설계
# 	Module08 만 STL의 사용가능(= 컨테이너와 알고리즘헤더가 포함된 모든것 들의 사용 금지)
# 	엄격한 메모리 관리(누수 X)
# 	헤더파일에 선언되지 않은 함수 사용 금지
# 	각 헤더를 다른 헤더와 독립적으로 사용 가능(= 필요한 모든 종속성을 포홈해야 한다. 단, 헤더가드를 사용해 이중으로 포함된느 것은 피해야만 한다.)
# 	필요하다면(코드의 분할 등) 필수 제출파일 이외의 파일 추가 가능
# 과제의 가이드라인이 짧은경우, 명시적으로 작성되지 않은 부분들은 example을 통해 확인할 수 있다.
# Orthodox Canonical Class Form(OCCF): 아래 요소를 '명시적'으로 선언할 것
#	기본 생성자:
#		입력받는 인수가 없는 생성자(명시하지 않으면 컴파일러가 알아서 만들지만, OCCF를 따르려면 명시적으로 선언해줘야한다.)
#	복사 생성자:
#		형태: ClassName(const ClassName &copy);
#		생성과 동시에 복사할 때 사용된다.
#		인수를 참조형으로 받지 않으면, 임시 객체를 무한으로 생성하는 루프에 빠지게된다.
#		역시 명시하지 않으면 컴파일러가 알아서 만들지만, 이 경우 얕은 복사 밖에 안된다.
#	대입연산자 오버로딩:
#		형태: (반환형) operator=(const ClassName&)
#		생성후 대입연산자를 통해 객체를 복사할 때 사용된다.
#		반환형은 대게 클래스의 참조형을 사용하며 그 이유는 'a = b = c'와 같은 연산을 위해서.
#	소멸자:
#		개체가 범위를 벗어나거나 delete 에 의해 명시적으로 제거될때 호출된다.
#		사용한 리소스를 소멸자를 통해 잘 반환해주는것이 핵심이다.