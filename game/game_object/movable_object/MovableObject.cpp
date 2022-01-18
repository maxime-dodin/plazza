/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** movable_object.cpp.cc
*/
#include "MovableObject.hpp"

game::MovableObject::MovableObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, std::size_t speed, game::Direction direction)
    : game::AGameObject(pos, uid, texturePath, textureChar), _speed(speed), _direction(direction)
{
    type = game::Type::MOVABLE_OBJECT;
}
