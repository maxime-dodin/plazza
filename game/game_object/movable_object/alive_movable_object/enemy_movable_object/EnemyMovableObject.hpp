/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** enemy_movable_object.hpp.h
*/
#ifndef ARCADE_ENEMYMOVABLEOBJECT_HPP
#define ARCADE_ENEMYMOVABLEOBJECT_HPP

#include "AliveMovableObject.hpp"
#include <functional>

namespace game {
    struct EnemyMovableObject : public game::AliveMovableObject {
        EnemyMovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar,  std::size_t speed, Direction direction, bool life, std::function<void()> ia, bool eatable);

        ~EnemyMovableObject() = default;

        std::function<void()> _ia;

        bool _eatable;
    };
}

#endif //ARCADE_ENEMYMOVABLEOBJECT_HPP
