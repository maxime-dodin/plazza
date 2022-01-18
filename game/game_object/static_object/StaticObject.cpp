/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** static_object.cpp.cc
*/
#include "StaticObject.hpp"

game::StaticObject::StaticObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, bool isCollisonable)
    : game::AGameObject(pos, uid, texturePath, textureChar), _isCollisonable(isCollisonable)
{
    type = game::Type::STATIC_OBJECT;
}

