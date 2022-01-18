/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGame.hpp.h
*/
#ifndef ARCADE_IGAME_HPP
#define ARCADE_IGAME_HPP

#include "IGraphic.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace game {
    using sObjPointer = std::shared_ptr<graph::Object>;
    using objVector = std::vector<sObjPointer>;

    class IGame {
        public:
        virtual ~IGame() = default;

        virtual void init() = 0;

        virtual void update(std::size_t input, double deltaTime) = 0;

        virtual void end() = 0;

        [[nodiscard]] virtual objVector dumpObjects() = 0;

        [[nodiscard]] virtual const std::string &getGameName() const noexcept = 0;
    };

    typedef graph::IGraphic *createGameLib_t(std::string (*createUID_fp)());
    typedef void destroyGameLib_t(graph::IGraphic *t_lib);

}

#endif //ARCADE_IGAME_HPP