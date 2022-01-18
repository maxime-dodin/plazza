##
## EPITECH PROJECT, 2019
## B_OOP_400_PAR_4_1_tekspice_paul_beaudet
## File description:
## Makefile
##

## USEFUL DEF ########################

CC			=	g++
CCL			=	clang++
RM			=	-rm -rf
BIN			=	arcade
TEST_BIN	=	unit_tests
EXT			=	.cpp

#######################################

## Dir  ##############################

GRAPH_DIR		=	./graphic

GAME_DIR		=	./game

CORE_DIR		=	./core

TESTS_DIR		=	./tests

#######################################

## Files ##############################

TESTS_FILES			=	testsobject

#######################################

## Sources ############################

TESTS		=	$(addsuffix $(EXT), $(addprefix $(TESTS_DIR)/, $(TESTS_FILES)))					\

#######################################

## OBJ ################################

TESTS_OBJ	=	$(TESTS:.cpp=.o)

#######################################

## FLAGS ##############################

CXXFLAGS	=	-W -Wall -Wextra -std=c++17 #-Werror

CPPFLAGS	=

THRFLAGS	=	-j4

CLANGFLAGS	=	-Weverything

#######################################

## RULES ##############################

.PHONY: all
all: graphicals core games

.PHONY: graphicals
graphicals:
	make -C $(GRAPH_DIR)

.PHONY: core
core:
	make -C $(CORE_DIR)

.PHONY: games
games:
	make -C $(GAME_DIR)

.PHONY: clean
clean:
	make -C $(GRAPH_DIR) clean
	make -C $(GAME_DIR) clean
	make -C $(CORE_DIR) clean

.PHONY: fclean
fclean: clean
	@$(RM) **/*.gc*
	@$(RM) *.gc*
	make -C $(GRAPH_DIR) fclean
	make -C $(GAME_DIR) fclean
	make -C $(CORE_DIR) fclean

.PHONY: re
re: fclean clean all

.PHONY: tests_run
tests_run:  CXXFLAGS += --coverage
tests_run:  LDFLAGS += -lcriterion -DUNIT_TEST
tests_run:	$(TESTS_OBJ) $(SRC_OBJ)
	$(CC) -o $(TEST_BIN) $(TESTS_OBJ) $(SRC_OBJ) $(CXXFLAGS) $(LDFLAGS)
	-./$(TEST_BIN)
	gcovr -r . -b --exclude-directories tests -e $(MAIN) $(THRFLAGS)
	gcovr -r . --exclude-directories tests -e $(MAIN) $(THRFLAGS)
	@$(RM) $(TEST_BIN)

#######################################
