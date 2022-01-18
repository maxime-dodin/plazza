/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** Image Object
*/

#pragma once

#include "Object.hpp"
#include <string>

namespace graph {
    struct Image : public Object {
        explicit Image(const std::string &uid, const std::string &t_path, const char &t_char, core::Color color = core::Color::RED, const Coords &pos = Coords(0, 0), const Coords &offset = Coords(0, 0))
            : Object(uid, core::ObjectType::IMAGE, color, pos, offset), m_texturePath(t_path), m_defaultChar(t_char)
        {}

        std::string m_texturePath;
        char m_defaultChar;
    };
}
