##
## EPITECH PROJECT, 2021
## B-OOP-400-PAR-4-1-arcade-arthur.fouquet
## File description:
## Makefile
##

## USEFUL DEF ########################

CC			=	g++
CCL			=	clang++
RM			=	-rm -rf
TEST_BIN	=	unit_tests
EXT			=	.cpp
NCURSES_BIN	=	arcade_ncurses.so
SDL2_BIN	=	arcade_sdl2.so
SFML_BIN	=	arcade_sfml.so

#######################################


## Dir  ###############################

NCURSES_DIR		=	./ncurses

SDL2_DIR		=	./sdl2

SFML_DIR		=	./sfml

CORE_DIR		=	../core

ERROR_DIR		=	../error

#######################################


## Files ##############################

SRC				=	$(addsuffix $(EXT), ./ADisplay)			\
					$(addsuffix $(EXT), $(ERROR_DIR)/Error)

NCURSES_FILE	=	$(addsuffix $(EXT), $(NCURSES_DIR)/NcursesEncapsulation)

SDL2_FILE		=	$(addsuffix $(EXT), $(SDL2_DIR)/Sdl2Encapsulation)

SFML_FILE		=	$(addsuffix $(EXT), $(SFML_DIR)/SfmlEncapsulation)

SRC_TEST		=	$(addsuffix $(EXT), tests/unit_tests)

#######################################

## OBJ ################################

OBJ				=	$(SRC:.cpp=.o)

OBJ_NCURSES		=	$(NCURSES_FILE:.cpp=.o)

OBJ_SDL2		=	$(SDL2_FILE:.cpp=.o)

OBJ_SFML		=	$(SFML_FILE:.cpp=.o)

#######################################


## FLAGS ##############################

CXXFLAGS	=	-Wall -Wextra -fPIC -std=c++17

CPPFLAGS	=	-I$(CORE_DIR) -I$(ERROR_DIR) -I.

LDFLAGS		=	-shared

#######################################


## RULES ##############################

all:	$(OBJ) $(NCURSES_BIN) $(SDL2_BIN) $(SFML_BIN)

$(NCURSES_BIN):	LDFLAGS += -lncurses
$(NCURSES_BIN): CPPFLAGS += -I$(NCURSES_DIR)
$(NCURSES_BIN): $(OBJ_NCURSES)
	$(CC) -o $(NCURSES_BIN) $(OBJ) $(OBJ_NCURSES) $(LDFLAGS)
	mv $(NCURSES_BIN) ../lib

$(SDL2_BIN): LDFLAGS += -lSDL2 -lSDL2_ttf -lSDL2_image
$(SDL2_BIN): CPPFLAGS += -I$(SDL2_DIR)
$(SDL2_BIN): $(OBJ_SDL2)
	$(CC) -o $(SDL2_BIN) $(OBJ) $(OBJ_SDL2) $(LDFLAGS)
	mv $(SDL2_BIN) ../lib

$(SFML_BIN): LDFLAGS += -lsfml-graphics -lsfml-window -lsfml-system
$(SFML_BIN): CPPFLAGS += -I$(SFML_DIR)
$(SFML_BIN): $(OBJ_SFML)
	$(CC) -o $(SFML_BIN) $(OBJ) $(OBJ_SFML) $(LDFLAGS)
	mv $(SFML_BIN) ../lib

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_NCURSES)
	$(RM) $(OBJ_SDL2)
	$(RM) $(OBJ_SFML)

fclean:	clean
	$(RM) ../lib/$(NCURSES_BIN)
	$(RM) ../lib/$(SDL2_BIN)
	$(RM) ../lib/$(SFML_BIN)

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