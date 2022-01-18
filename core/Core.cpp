/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Core.cpp.cc
*/
#include "Core.hpp"
#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>


const std::array<std::string, 2> core::Core::arrFn = {"getLibType", "createGraphicLib"};

const std::array<std::string, 3> core::Core::arrGraph = {"./lib/arcade_sdl2.so", "./lib/arcade_ncurses.so", "./lib/arcade_sfml.so"};

const std::array<std::string, 2> core::Core::arrGame = {"./lib/arcade_nibbler.so", "./lib/arcade_pacman.so"};

int core::Core::selectGame = 0;

int core::Core::selectGraph = -1;

std::size_t core::Core::currNbrFile = 0;

template<typename T>
void destroyGraphicLib(T graph)
{
    delete (graph);
}

void core::Core::_loadLibs()
{
    static const int FIRST_CHAR_OF_FILE = 6;
    static const std::string path = "./lib";
    std::size_t nbrFile = 0;

    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        try {
            if (entry.path().c_str()[FIRST_CHAR_OF_FILE] == '.')
                continue;
            else if (entry.path() == arrGame[0] || entry.path() == arrGame[1])
                _gameLibArr.at(entry.path());
            else
                _graphLibArr.at(entry.path());
            ++nbrFile;
            continue;
        } catch (const std::out_of_range &e) {
            ++nbrFile;
            arcade::Ldl l(entry.path());
            auto *getLibType = l.loadSymbol<arcade::LIB_TYPE (*)()>(arrFn[0]);
            if (arcade::GRAPHIC == getLibType()) {
                std::cout << "add a graphic lib:\t" << entry.path() << std::endl;

                auto *cr = l.loadSymbol<graph::AComp *(*)()>(arrFn[1]);

                _graphLibArr.emplace(entry.path(), (core::Core::Ldl_t<graph::IGraphic *>{.load = std::move(l), .createLib = cr}));
            } else if (arcade::GAME == getLibType()) {
                std::cout << "add a game lib:\t\t" << entry.path() << std::endl;
                auto *cr = l.loadSymbol<game::IGame *(*)()>(arrFn[1]);
                _gameLibArr.emplace(entry.path(), (core::Core::Ldl_t<game::IGame *>{.load = std::move(l), .createLib = cr}));
            } else
                throw (err::LoaderException("A file in lib is nor a game or a graphic lib."));
        }
    }
    currNbrFile = nbrFile;
}

void core::Core::_updLibs(graph::IGraphic *graph, game::IGame *game)
{
    static const std::string path = "./lib";
    std::vector<std::string> toErase;

    if (_graphLibArr.size() + _gameLibArr.size() <= currNbrFile)
        return;
    for (auto &[x, y] : _graphLibArr) {
        std::ifstream f(x.c_str());
        if (!f.good() && graph->getLibName() != x)
            toErase.push_back(x);
    }
    for (auto it = _graphLibArr.begin(); it != _graphLibArr.end();)
        if (std::find_if(toErase.begin(), toErase.end(), [it](const std::string &e) {
            return (e == it->first);
        }) != toErase.end()) {
            it = _graphLibArr.erase(it);
        } else
            ++it;
    for (auto &[x, y] : _gameLibArr) {
        std::ifstream f(x.c_str());
        if (!f.good() && game->getGameName() != x)
            toErase.push_back(x);
    }
    for (auto it = _gameLibArr.begin(); it != _gameLibArr.end();)
        if (std::find_if(toErase.begin(), toErase.end(), [it](const std::string &e) {
            return (e == it->first);
        }) != toErase.end()) {
            it = _gameLibArr.erase(it);
        } else
            ++it;
}

core::Core::Core() : _deltaTime(0)
{
    _loadLibs();
}

graph::IGraphic *core::Core::_findFirstGraph(char *av)
{
    std::string lib = av;

    try {
        std::cout << "searching: " << lib << std::endl;
        return (_graphLibArr.at(lib).createLib());
    } catch (const std::out_of_range &e) {
        std::cout << "load other lib" << std::endl;
        return (_graphLibArr.begin()->second.createLib());
    }
}

game::IGame *core::Core::_findFirstGame()
{
    try {
        return (_gameLibArr.at(arrGame[0]).createLib());
    } catch (const std::out_of_range &e) {
        return (_gameLibArr.begin()->second.createLib());
    }
}

void core::Core::_getPlayerStatus(game::Menu *menu)
{
    if (selectGame != -1)
        return;
    if (_playerName.empty())
        _playerName = menu->getPlayerName();
    _playerScore = menu->getScore();
}

bool core::Core::_getLibGameSetMenu(Core_t *core, game::IGame *menu)
{
    auto *obj = (game::Menu *)(menu);
    if (obj->getGame().empty() || obj->getLib().empty())
        return false;
    std::cout << "Changing lib and game" << "\n";
    std::string tmp1 = "./lib/" + obj->getGame();
    std::cout << "game = " << tmp1 << "\n";
    auto itr = std::find(std::begin(arrGame), std::end(arrGame), tmp1);
    if (itr != end(arrGame)) {
        selectGame = std::distance(arrGame.begin(), itr);
        core->game->end();
        core->game = _gameLibArr.at(arrGame[selectGame]).createLib();
        core->game->init();
    }
    std::string tmp = "./lib/" + obj->getLib();
    std::cout << "lib = " << tmp << "\n";
    auto atr = std::find(std::begin(arrGraph), std::end(arrGraph), tmp);
    if (atr != end(arrGraph)) {
        selectGraph = std::distance(arrGraph.begin(), atr);
        if (core->graph->getLibName() == arrGraph.at(selectGraph))
            return true;
        std::cout << "curr lib graph: " << arrGraph.at(selectGraph) << std::endl;
        core->graph->destroy();
        core->graph = _graphLibArr.at(arrGraph[selectGraph]).createLib();
        core->graph->init();
    }
    return true;
}

std::size_t core::Core::_menuLoop(Core_t *core, game::Menu *menu)
{
    while (true) {
        auto arr = menu->dumpObjects();
        int input = core->graph->pollEvent();
        menu->update(input, _getDeltaTime());
        for (auto &obj : arr) {
            if (obj->offset.first == 0 && obj->offset.second == 0 && obj->type == core::TEXT) {
                obj->offset.first = 12;
                obj->offset.second = 6;
            }
            core->graph ->draw(*obj);
        }
        _getPlayerStatus(menu);
        core->graph->updateWindow();
        if (_getLibGameSetMenu(core, menu))
            break;
        if (input == KeyBoard::ESCAPE)
            return KeyBoard::ESCAPE;
        if (input == 'm')
            return 'm';
    }
    return 0;
}

std::size_t core::Core::_gameLoop(graph::IGraphic *graph, game::IGame *game)
{
    while (true) {
        auto arr = game->dumpObjects();
        int input = graph->pollEvent();
        game->update(input, _getDeltaTime());
        if (std::find_if(keymap.begin(), keymap.end(), [input](char c) {
            return (c == input);
        }) != keymap.end())
            return (input);
        std::for_each(arr.begin(), arr.end(), [&graph](std::shared_ptr<graph::Object> &obj) {
            if (obj->offset.first == 0 && obj->offset.second == 0 && obj->type) {
                obj->offset.first = 12;
                obj->offset.second = 6;
            }
            graph->draw(*obj);
        });
        graph->updateWindow();
        _loadLibs();
        _updLibs(graph, game);
    }
}

double core::Core::_getDeltaTime() const noexcept
{
    return (_deltaTime);
}

void core::Core::_setDeltaTime()
{
}

void core::Core::_nextGame(Core_t *core)
{
    selectGame += 1;
    if (selectGame == static_cast<int>(_gameLibArr.size()))
        selectGame = 0;
    std::cout << "Change " << core->game->getGameName() << " to " << arrGame[selectGame] << std::endl;
    core->game->end();
    core->game = _gameLibArr.at(arrGame[selectGame]).createLib();
    core->game->init();
}

void core::Core::_prevGame(Core_t *core)
{
    selectGame -= 1;
    if (selectGame == -1)
        selectGame = static_cast<int>(_gameLibArr.size()) - 1;
    std::cout << "Change " << core->game->getGameName() << " to " << arrGame[selectGame] << std::endl;
    core->game->end();
    core->game = _gameLibArr.at(arrGame[selectGame]).createLib();
    core->game->init();
}

void core::Core::_nextGraph(Core_t *core)
{
    selectGraph += 1;
    if (selectGraph == static_cast<int>(_graphLibArr.size()))
        selectGraph = 0;
    std::cout << "Change " << core->graph->getLibName() << " to " << arrGraph[selectGraph] << std::endl;
    core->graph->destroy();
    delete core->graph;
    core->graph = nullptr;
    core->graph = _graphLibArr.at(arrGraph[selectGraph]).createLib();
    core->graph->init();
}

void core::Core::_prevGraph(Core_t *core)
{
    selectGraph -= 1;
    if (selectGraph == -1)
        selectGraph = static_cast<int>(_graphLibArr.size()) - 1;
    std::cout << "Change " << core->graph->getLibName() << " to " << arrGraph[selectGraph] << std::endl;
    core->graph->destroy();
    delete core->graph;
    core->graph = nullptr;
    core->graph = _graphLibArr.at(arrGraph[selectGraph]).createLib();
    core->graph->init();
}

void core::Core::_toMenu(Core_t *core)
{
    (void)core;
    std::cout << "to menu" << std::endl;
}

void core::Core::_restart()
{
    // TODO: peut être rajouter une method restart
    std::cout << "restart" << std::endl;
}

void core::Core::_exitCore(graph::IGraphic *graph, game::IGame *game)
{
    game->end();
    destroyGraphicLib<game::IGame *>(game);
    graph->destroy();
    destroyGraphicLib<graph::IGraphic *>(graph);
}

void core::Core::run(char *av)
{
    static const std::map<char, std::function<void(Core_t *core)>> keymap = {{KeyBoard::MENU, [this](Core_t *core) {
        _toMenu(core);
    }}, {KeyBoard::PREV_GAME, [this](Core_t *core) {
        _prevGame(core);
    }}, {KeyBoard::NEXT_GAME, [this](Core_t *core) {
        _nextGame(core);
    }}, {KeyBoard::PREV_LIB, [this](Core_t *core) {
        _prevGraph(core);
    }}, {KeyBoard::NEXT_LIB, [this](Core_t *core) {
        _nextGraph(core);
    }}};
    Core_t core{};
    auto menu = game::Menu();
    core.graph = _findFirstGraph(av);
    core.game = _findFirstGame();

    core.graph->init();
    menu.init();
    if (_menuLoop(&core, &menu) == KeyBoard::ESCAPE)
        return (_exitCore(core.graph, core.game));
    while (true) {
        std::size_t input = _gameLoop(core.graph, core.game);
        try {
            keymap.at(input)(&core);
        } catch (const std::out_of_range &e) {
            return (_exitCore(core.graph, core.game));
        }
    }
}
