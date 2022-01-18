/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** UI Box Object
*/

#pragma once

#include "Object.hpp"

namespace graph {

    using Size = std::pair<double, double>;
    struct UIBox : public Object {
        UIBox(const std::string &uid, const Size &size, core::Color color = core::Color::INVISIBLE, const Coords &pos = Coords(0, 0), const Coords &offset = Coords(0, 0))
        : Object(uid, core::ObjectType::BOX_UI, color, pos, offset), size(size)
        {}
        Size size;
    };
}
