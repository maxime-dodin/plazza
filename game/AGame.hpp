/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGame.hpp.h
*/
#ifndef ARCADE_AGAME_HPP
#define ARCADE_AGAME_HPP

#include "IGame.hpp"
#include <vector>
#include <iostream>
#include <map>

namespace game {
    std::string createUID();
    class AGame : public game::IGame {
        public:

        explicit AGame(std::string gameName);

        ~AGame() override = default;

        [[nodiscard]] const std::string &getGameName() const noexcept override;

        protected:
        std::string _gameName;
    };
}

#endif //ARCADE_AGAME_HPP
