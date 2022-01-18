/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core.hpp.h
*/
#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "Ldl.hpp"
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iterator>

#include "Menu.hpp"

namespace core {
    class Core {
        public:
        Core();

        ~Core() = default;

        void run(char *av);

        static int selectGame;

        static int selectGraph;

        struct Core_t {
            graph::IGraphic *graph;
            game::IGame *game;
        };

        private:
        static void _exitCore(graph::IGraphic *graph, game::IGame *game);

        game::IGame *_findFirstGame();

        graph::IGraphic *_findFirstGraph(char *av);

        std::size_t _gameLoop(graph::IGraphic *graph, game::IGame *game);

        std::size_t _menuLoop(Core_t *core, game::Menu *menu);

        bool _getLibGameSetMenu(Core_t *core, game::IGame *menu);

        void _nextGame(Core_t *core);

        void _prevGame(Core_t *core);

        void _nextGraph(Core_t *core);

        void _prevGraph(Core_t *core);

        void _restart();

        void _toMenu(Core_t *core);

        void _loadLibs();

        void _updLibs(graph::IGraphic *graph, game::IGame *game);

        [[nodiscard]] double _getDeltaTime() const noexcept;

        static std::size_t currNbrFile;

        static const std::array<std::string, 2> arrFn;

        static const std::array<std::string, 3> arrGraph;

        static const std::array<std::string, 2> arrGame;

        void _setDeltaTime();

        [[nodiscard]] std::string _getPlayer() const noexcept;

        void _getPlayerName(std::string &playerName);

        void _getPlayerStatus(game::Menu *game);

        double _deltaTime;

        std::string _playerName;
        std::string _playerScore;
        std::string _playerLib;
        std::string _playerGame;

        template<class T>
        struct Ldl_t {
            arcade::Ldl load;
            T (*createLib)();
        };

        std::unordered_map<std::string, Ldl_t<graph::IGraphic *>> _graphLibArr;

        std::unordered_map<std::string, Ldl_t<game::IGame *>> _gameLibArr;
    };
}

#endif //ARCADE_CORE_HPP
