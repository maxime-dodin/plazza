/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** nibbler.hpp.h
*/
#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "AGame.hpp"
#include "ADisplay.hpp"
#include "AGameObject.hpp"

#include "Text.hpp"

#include "StaticObject.hpp"
#include "EnumCore.hpp"
#include "EnemyMovableObject.hpp"
#include <memory>
#include <vector>
#include <fstream>

namespace game {
    class Nibbler final : public game::AGame {
        public:
        Nibbler();

        ~Nibbler() final = default;

        void init() final;

        void update(std::size_t input, double deltaTime) final;

        void end() final;

        [[nodiscard]] objVector dumpObjects() final;

        private:
        std::vector<game::AGameObject> _objVecGame;

        std::vector<std::shared_ptr<graph::Object>> arr;

        static void _enemyAI();

        void _makeMap(std::size_t maxHeight, std::size_t maxWidth);

        std::pair<std::size_t, std::size_t> _setBonusPos(std::size_t maxHeight, std::size_t maxWidth);

        void _putBonus(std::size_t maxHeight, std::size_t maxWidth);

        void _changeDirection(game::AliveMovableObject &obj, std::size_t input);

        void _giveNewDirection(std::size_t input);
    };
}

#endif //ARCADE_NIBBLER_HPP
