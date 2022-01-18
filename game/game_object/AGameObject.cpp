/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AObject.cpp.cc
*/
#include "AGameObject.hpp"
#include "Text.hpp"
#include "Image.hpp"
#include "UiBox.hpp"

game::AGameObject::AGameObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar)
{
    obj = std::make_shared<graph::Image>(uid, texturePath, textureChar);
    obj->pos = pos;
}
