##
## EPITECH PROJECT, 2021
## B-OOP-400-PAR-4-1-arcade-arthur.fouquet
## File description:
## Makefile
##

## USEFUL DEF ########################

CC			=	g++
CCL			=	clang
RM			=	-rm -rf
BIN			=	arcade
TEST_BIN	=	unit_tests
EXT			=	.cpp

#######################################


## Dir  ###############################

GRAPH_DIR		=	../graphic

GAME_DIR		=	../game

ERROR_DIR		=	../error

MENU_DIR		=	$(GAME_DIR)/menu

#######################################


## Files ##############################

SRC				=	../Main.cpp								\
					./Core.cpp								\
					./Ldl.cpp								\
					$(addsuffix $(EXT), $(MENU_DIR)/Menu)	\
					$(ERROR_DIR)/Error.cpp

SRC_TEST		=	tests/unit_tests.cpp	\

#######################################

## OBJ ################################

OBJ			=	$(SRC:.cpp=.o)

#######################################


## FLAGS ##############################

CXXFLAGS	=	-Wall -Wextra -std=c++17

CPPFLAGS	=	-I$(GRAPH_DIR) -I$(GAME_DIR) -I$(ERROR_DIR) -I$(GAME_DIR)/menu -I.

LDFLAGS		=	-rdynamic -ldl

#######################################


## RULES ##############################

%.o:    %.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

all:	$(BIN)

$(BIN): $(OBJ)
	$(CC) -o $(BIN) $(OBJ) $(LDFLAGS)
	$(RM) ../error/Error.o
	$(CC) -shared -Wall -Wextra -std=c++17 -fPIC -c -o ../error/Error.o ../error/Error.cpp
	mv $(BIN) ..

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../$(BIN)

re:	fclean all

tests_run:	CXXFLAGS += --coverage
tests_run:	LDFLAGS += -lcriterion
tests_run:
	$(CXX) -o $(NAME_TEST) $(SRC_TEST) $(SRC_SFML) $(CXXFLAGS) $(LDFLAGS)
	./$(NAME_TEST)

cover:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

.PHONY:	all clean fclean tests_run cover