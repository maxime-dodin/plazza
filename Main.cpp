/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Main.cpp.c
*/

#include "Core.hpp"

static const char *usage = "./arcade [dynamic library]\n"
                          "\tdynamic library is the filepath to a .so (int the dir file)";

void printUsage()
{
    std::cout << usage << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        printUsage();
        return (84);
    }
    try {
        core::Core c;

        c.run(av[1]);
    } catch (const err::ArcadeError &e) {
        std::cout << e.where() << ": " << e.what() << std::endl;
    }
    return (0);
}