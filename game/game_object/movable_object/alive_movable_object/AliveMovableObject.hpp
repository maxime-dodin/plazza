/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** alive_movable_object.hpp.h
*/
#ifndef ARCADE_ALIVEMOVABLEOBJECT_HPP
#define ARCADE_ALIVEMOVABLEOBJECT_HPP

#include "MovableObject.hpp"

namespace game {
    struct AliveMovableObject : public game::MovableObject {
        AliveMovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, std::size_t speed, game::Direction direction, bool life);

        ~AliveMovableObject() = default;

        bool _life;
    };
}

#endif //ARCADE_ALIVEMOVABLEOBJECT_HPP
