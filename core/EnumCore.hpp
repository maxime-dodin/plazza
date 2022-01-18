/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** EnumCore
*/

#ifndef ENUMCORE_HPP_
#define ENUMCORE_HPP_

#include <iostream>
#include <map>
#include <ctime>
#include <string>
#include <algorithm>

namespace core {
    enum ObjectType {
        IMAGE,
        TEXT,
        BOX_UI
    };

    enum Color {
        BLACK,
        WHITE,
        BLUE,
        GREEN,
        PURPLE,
        DARK_BLUE,
        RED,
        INVISIBLE
    };

    static const std::map<std::string, core::Color> mapOfColor = {{"black", core::Color::BLACK}, {"white", core::Color::WHITE}, {"blue", core::Color::BLUE},
        {"green", core::Color::GREEN}, {"purple", core::Color::PURPLE}, {"dark_blue", core::Color::DARK_BLUE}, {"red", core::Color::RED},
        {"invisible", core::Color::INVISIBLE}};

    static const std::array<char, 6> keymap = {'m', 'q', 'a', 'e', 'x', 'c'};

    enum KeyBoard {
        PAUSE,
        MENU = 'm',
        RESTART,
        PREV_LIB = 'a',
        NEXT_LIB = 'e',
        PREV_GAME = 'x',
        NEXT_GAME = 'c',
        ASCII_END = 127,
        ARROW_UP = 128,
        ARROW_DOWN = 129,
        ARROW_LEFT = 130,
        ARROW_RIGHT = 131,
        SELECT = 12,
        DELETE = 132,
        ESCAPE = 133,
        NONE = -1,
        EXIT = -2,
    };
}

#endif /* !ENUMCORE_HPP_ */
