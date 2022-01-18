/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** static_object.hpp.h
*/
#ifndef ARCADE_STATICOBJECT_HPP
#define ARCADE_STATICOBJECT_HPP

#include "AGameObject.hpp"
#include "EnumCore.hpp"

namespace game {
    struct StaticObject : public game::AGameObject {
        public:
        explicit StaticObject(graph::Coords pos, const std::string &uid, const std::string &texturePath, char textureChar, bool isCollisonable);

        ~StaticObject() = default;

        bool _isCollisonable;


    };
}

#endif //ARCADE_STATICOBJECT_HPP
