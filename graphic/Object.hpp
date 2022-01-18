/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Iobject.hpp.h
*/

#ifndef ARCADE_IGRAPHOBJECT_HPP
#define ARCADE_IGRAPHOBJECT_HPP


#include "EnumCore.hpp"

namespace graph {
    using Coords = std::pair<std::size_t, std::size_t>;

    struct Object {
        explicit Object(const std::string &uid, core::ObjectType type, core::Color color = core::Color::INVISIBLE, const Coords &pos = Coords(0, 0), const Coords &offset = Coords(0, 0))
            : uid(uid), type(type), color(color), pos(pos), offset(offset)
        {}

        ~Object() = default;

        std::string uid;
        const core::ObjectType type;
        core::Color color;
        Coords pos;
        Coords offset;
    };
}

#endif //ARCADE_IGRAPHOBJECT_HPP