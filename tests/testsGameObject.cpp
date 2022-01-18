/*
** EPITECH PROJECT, 2024
** B_OOP_400_PAR_4_1_tekspice_paul_beaudet
** File description:
** tests_components.cpp.c
*/

#include "Error.hpp"
#include "IGame.hpp"
#include "Object.hpp"
#include "IGraphic.hpp"
#include "Nibbler.hpp"
#include "NcursesEncapsulation.hpp"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(posGameObj, setterAndGetter)
{
    auto core = std::make_unique<graph::NcursesEncapsulation>();
    auto snake = std::make_shared<object::Text>(game::AGame::mapAsset.at(game::AGame::MAIN_MENU));
    std::size_t x = 5;
    std::size_t y = 6;
    auto test = std::make_pair(x, y);

    snake->setPos(x, y);
    cr_expect(test == snake->getPos());
}

Test(libNameGraphic, setterAndGetter)
{
    auto core = std::make_unique<graph::NcursesEncapsulation>();

    cr_expect_str_eq("ncurses", core->getLibName().c_str());
}