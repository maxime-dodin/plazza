/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** movable_object.hpp.h
*/
#ifndef ARCADE_MOVABLEOBJECT_HPP
#define ARCADE_MOVABLEOBJECT_HPP

#include "AGameObject.hpp"

namespace game {
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    struct MovableObject : public game::AGameObject {
        MovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, std::size_t speed, Direction direction);

        ~MovableObject() = default;

        std::size_t _speed;

        Direction _direction;
    };
}

#endif //ARCADE_MOVABLEOBJECT_HPP
