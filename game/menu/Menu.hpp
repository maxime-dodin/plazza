/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "IGame.hpp"

#include "Text.hpp"
#include "UiBox.hpp"
#include "Image.hpp"

#include "EnumCore.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <memory>
#include <algorithm>

namespace game {
    class Menu final : public game::IGame {
        public:
        Menu();

        ~Menu() = default;

        void init() final;

        void update(std::size_t input, double deltaTime) final;

        void end() final;

        [[nodiscard]] const std::string &getGameName() const noexcept final;

        [[nodiscard]] objVector dumpObjects() final;

        [[nodiscard]] std::string getScore() const;

        [[nodiscard]] std::string getPlayerName() const;

        [[nodiscard]] std::string getGame() const;

        [[nodiscard]] std::string getLib() const;

        protected:
        private:
        std::string _gameName;
        std::size_t _state;
        std::vector<std::shared_ptr<graph::Object>> _obj;
        std::vector<std::string> _lib;
        std::vector<std::string> _game;

        int _line;
        int _collLib;
        int _collGame;

        void _setPlayerName(std::size_t input);

        void _setGameAndLib();

        void _selectGameAndLib(std::size_t input);

        std::string _playerScore;
        std::string _playerName;
        std::string _libLoad;
        std::string _gameLoad;

        bool _endMenu = false;

        std::pair<std::size_t, std::size_t> _PlayerBox;
    };
}
#endif /* !MENU_HPP_ */