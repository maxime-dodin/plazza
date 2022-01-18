/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Text Object
*/

#pragma once

#include "Object.hpp"

namespace graph {
    struct Text : public Object {
        Text(const std::string &uid, const std::string &text = "", const std::string &fontPath = "", std::size_t size = 13, core::Color color = core::Color::INVISIBLE, const Coords &pos = Coords(0, 0), const Coords &offset = Coords(0, 0))
            : Object(uid, core::ObjectType::TEXT, color, pos, offset), text(text), fontPath(fontPath), size(size)
        {}

        ~Text() = default;

        std::string text;
        std::string fontPath;
        size_t size;
        std::string uid;
    };
}