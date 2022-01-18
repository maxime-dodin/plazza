/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** enemy_movable_object.cpp.cc
*/
#include "EnemyMovableObject.hpp"

#include <utility>

game::EnemyMovableObject::EnemyMovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, std::size_t speed, Direction direction, bool life,
    std::function<void()> ia, bool eatable) : game::AliveMovableObject(pos, uid, texturePath, textureChar, speed, direction, life), _ia(std::move(ia)), _eatable(eatable)
{
    type = game::Type::ENEMY_MOVABLE_OBJECT;
}
