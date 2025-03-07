SHELL := /bin/sh
NAME := ircserv

INC := $(addprefix src/inc/,\
	   $(addsuffix .hpp,\
	   Channel\
	   Connection\
	   debug\
	   Executor\
	   KQueueManager\
	   macros\
	   Message\
	   Parser\
	   Server\
	   utils\
	   ))
SRC := $(addprefix src/,\
	   $(addsuffix .cpp,\
	   Channel\
	   Connection\
	   debug\
	   Executor\
	   execute_join\
	   KQueueManager\
	   main\
	   Message\
	   Parser\
	   Server\
	   utils\
	   ))
OBJ := $(SRC:.cpp=.o)
DEP := $(OBJ:.o=.d)


CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP
ifneq ($(MAKECMDGOALS),debug)
ifneq ($(MAKECMDGOALS),)
	CXXFLAGS += -D NDEBUG
endif
endif
# Append -D NDEBUG (not debug) for deployment
# Don't append -D NDEBUG for debugging
# For now, default make runs in debugging mode.

.PHONY: debug
debug : all

.PHONY: all
all : $(NAME)

.PHONY: clean
clean :
	$(RM) $(OBJ) $(DEP)

.PHONY: fclean
fclean : clean
	$(RM) $(NAME)

.PHONY: re
re : fclean all

$(NAME) : $(OBJ)
	$(CXX) -o $@ $^

%.o : %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $<

-include $(DEP)
