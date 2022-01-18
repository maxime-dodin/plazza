/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** pac_man.hpp.h
*/

#ifndef ARCADE_PACMAN_HPP
#define ARCADE_PACMAN_HPP

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
    class PacMan final : public game::AGame {
        public:
        PacMan();

        ~PacMan() final = default;

        void init() final;

        void update(std::size_t input, double deltaTime) final;

        void end() final;

        [[nodiscard]] objVector dumpObjects() final;

        private:

        std::vector<game::AGameObject> _objVecGame;

        std::vector<std::shared_ptr<graph::Object>> arr;

        static void _enemyAI();

        void _makeMap(std::size_t maxHeight, std::size_t maxWidth);
    };
}

#endif //ARCADE_PACMAN_HPP