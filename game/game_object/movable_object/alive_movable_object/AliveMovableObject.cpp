/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** alive_movable_object.cpp.cc
*/
#include "AliveMovableObject.hpp"

#include <utility>

game::AliveMovableObject::AliveMovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, std::size_t speed,
    game::Direction direction, bool life) : MovableObject(pos, uid, texturePath, textureChar, speed, direction), _life(life)
{
    type = game::Type::ALIVE_MOVABLE_OBJECT;
}
