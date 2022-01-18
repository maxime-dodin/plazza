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
NIBBLER_BIN	=	arcade_nibbler.so
PACMAN_BIN	=	arcade_pacman.so

#######################################


## Dir  ###############################

NIBBLER_DIR		=	./nibbler

PACMAN_DIR		=	./pacman

GAME_OBJ_DIR	=	./game_object

ERROR_DIR		=	../error

GRAPHIC_DIR		=	../graphic

CORE_DIR		=	../core

MOV_OBJ_DIR		=	movable_object

STAT_OBJ_DIR	=	static_object

ALIVE_OBJ_DIR	=	alive_movable_object

ENE_OBJ_DIR		=	enemy_movable_object

INCLUDES		=	.																\
					$(ERROR_DIR)													\
					$(CORE_DIR)														\
					$(GRAPHIC_DIR)													\
					$(NIBBLER_DIR)													\
					$(PACMAN_DIR)													\
					$(GAME_OBJ_DIR)													\
					$(GAME_OBJ_DIR)/$(MOV_OBJ_DIR)									\
					$(GAME_OBJ_DIR)/$(STAT_OBJ_DIR)									\
					$(GAME_OBJ_DIR)/$(MOV_OBJ_DIR)/$(ALIVE_OBJ_DIR)					\
					$(GAME_OBJ_DIR)/$(MOV_OBJ_DIR)/$(ALIVE_OBJ_DIR)/$(ENE_OBJ_DIR)

#######################################


## Files ##############################

GAME_OBJECT_FILES	=	./AGameObject															\
						$(MOV_OBJ_DIR)/MovableObject											\
						$(STAT_OBJ_DIR)/StaticObject											\
						$(MOV_OBJ_DIR)/$(ALIVE_OBJ_DIR)/AliveMovableObject						\
						$(MOV_OBJ_DIR)/$(ALIVE_OBJ_DIR)/$(ENE_OBJ_DIR)/EnemyMovableObject		\

SRC					=	$(addsuffix $(EXT), ./AGame)												\
                    	$(addsuffix $(EXT), $(addprefix $(GAME_OBJ_DIR)/, $(GAME_OBJECT_FILES)))	\
		#				$(addsuffix $(EXT), $(addprefix $(GRAPH_DIR)/, $(GRAPH_FILES)))				\

NIBBLER				=	$(addsuffix $(EXT), $(NIBBLER_DIR)/Nibbler)

PACMAN				=	$(addsuffix $(EXT), $(PACMAN_DIR)/PacMan)

SRC_TEST			=	$(addsuffix $(EXT), tests/unit_tests)

#######################################

## OBJ ################################

OBJ				=	$(SRC:.cpp=.o)

OBJ_NIBBLER		=	$(NIBBLER:.cpp=.o)

OBJ_PACMAN		=	$(PACMAN:.cpp=.o)

#######################################


## FLAGS ##############################

CXXFLAGS	=	-Wall -Wextra -fPIC -std=c++17

CPPFLAGS	=	$(foreach dir, $(INCLUDES), -I$(dir))

LDFLAGS		=	-shared

#######################################


## RULES ##############################

all:	$(OBJ) $(NIBBLER_BIN) $(PACMAN_BIN)

$(NIBBLER_BIN): $(OBJ_NIBBLER)
$(NIBBLER_BIN):
	$(CXX) $(LDFLAGS) -o $(NIBBLER_BIN) $(OBJ) $(OBJ_NIBBLER)
	mv $(NIBBLER_BIN) ../lib

$(PACMAN_BIN): $(OBJ_PACMAN)
$(PACMAN_BIN):
	$(CXX) $(LDFLAGS) -o $(PACMAN_BIN) $(OBJ) $(OBJ_PACMAN)
	mv $(PACMAN_BIN) ../lib

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_NIBBLER)
	$(RM) $(OBJ_PACMAN)
	$(RM) $(OBJ_MENU)

fclean:	clean
	$(RM) ../lib/$(NIBBLER_BIN)
	$(RM) ../lib/$(PACMAN_BIN)

re:	fclean all

tests_run:	CXXFLAGS += --coverage
tests_run:	LDFLAGS += -lcriterion
tests_run:
	$(CXX) -o $(NAME_TEST) $(SRC_TEST) $(SRC_GAME) $(CXXFLAGS) $(LDFLAGS)
	./$(NAME_TEST)

cover:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

.PHONY:	all clean fclean tests_run cover $(NAME)