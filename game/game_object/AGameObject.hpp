/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AObject.hpp.h
*/
#ifndef ARCADE_AObject_HPP
#define ARCADE_AObject_HPP

#include "Image.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <memory>

namespace game {
    typedef enum {
        STATIC_OBJECT,
        MOVABLE_OBJECT,
        ALIVE_MOVABLE_OBJECT,
        ENEMY_MOVABLE_OBJECT
    } Type;
    struct AGameObject {
        explicit AGameObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar);

        ~AGameObject() = default;

        std::shared_ptr<graph::Image> obj;

        Type type;
    };
}

#endif //ARCADE_AObject_HPP
