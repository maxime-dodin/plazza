/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** Menu
*/

#include "Menu.hpp"
#include "EnumLdl.hpp"

game::Menu::Menu() : _state(0), _line(0), _collLib(0), _collGame(0)
{
    _lib.emplace_back("arcade_ncurses.so");
    _lib.emplace_back("arcade_sdl2.so");
    _lib.emplace_back("arcade_sfml.so");

    _game.emplace_back("arcade_nibbler.so");
    _game.emplace_back("arcade_pacman.so");
}

void game::Menu::init()
{
    _obj.emplace_back(std::make_shared<graph::UIBox>(graph::UIBox("TITLE2", graph::Size(62, 50), core::Color::RED, graph::Coords(12, 6))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE8", "Please, enter a player UserName :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(18, 4))));
    _obj.emplace_back(
        std::make_shared<graph::Text>(graph::Text("TITLE1", "", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(22, 15))));

    auto SumScoreBox = std::make_shared<graph::UIBox>(graph::UIBox("TITLE4", graph::Size(24, 50), core::Color::RED, graph::Coords(92, 6)));
    auto *SumpPos = (graph::UIBox *)(&(*(SumScoreBox)));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE3", "Player Name :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 4),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE5", "Score :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 14),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE6", "Game Select :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 24),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE7", "Librarie Select :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 34),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(SumScoreBox);

    _obj.emplace_back(std::make_shared<graph::Text>(graph::Text("TITLE12", "", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 8),
                                                                graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(graph::Text("TITLE9", "0", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 18),
                                                                graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE10", "default", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 28),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
    _obj.emplace_back(std::make_shared<graph::Text>(
        graph::Text("TITLE11", "default", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(4, 38),
                    graph::Coords(SumpPos->pos.first, SumpPos->pos.second))));
}

std::string game::Menu::getPlayerName() const
{
    return _playerName;
}

std::string game::Menu::getScore() const
{
    return _playerScore;
}

std::string game::Menu::getLib() const
{
    if (_endMenu)
        return _libLoad;
    return "";
}

std::string game::Menu::getGame() const
{
    if (_endMenu)
        return _gameLoad;
    return "";
}

void game::Menu::_selectGameAndLib(std::size_t input)
{
    if (input == core::ARROW_UP)
        _line += 1;
    else if (input == core::ARROW_DOWN)
        _line -= 1;

    auto it = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
        return i.get()->uid == "TITLE16";
    });
    auto at = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
        return i.get()->uid == "TITLE17";
    });
    auto *lib = (graph::Text *)(&(*(*it)));
    auto *game = (graph::Text *)(&(*(*at)));

    if (_line % 2 == 0)
    {
        game->color = core::Color::RED;
        lib->color = core::Color::BLUE;
        if (input == core::ARROW_LEFT)
            _collLib -= 1;
        if (input == core::ARROW_RIGHT)
            _collLib += 1;
        if (_collLib < 0)
            _collLib = 2;
        if (_collLib >= 3)
            _collLib = 0;
        lib->text = _lib.at(_collLib);
        _libLoad = _lib.at(_collLib);
    }
    else
    {
        lib->color = core::Color::RED;
        game->color = core::Color::BLUE;
        if (input == core::ARROW_LEFT)
            _collGame -= 1;
        if (input == core::ARROW_RIGHT)
            _collGame += 1;
        if (_collGame < 0)
            _collGame = 1;
        if (_collGame >= 2)
            _collGame = 0;
        game->text = _game.at(_collGame);
        _gameLoad = _game.at(_collGame);
    }

    if (input == core::SELECT && _gameLoad.compare("default") && _libLoad.compare("default"))
    {
        _endMenu = true;
    }
}

void game::Menu::_setGameAndLib()
{
    auto LibScoreStr = std::make_shared<graph::Text>(
        graph::Text("TITLE14", "Please Select A Lib Using A or E :", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(18, 4)));
    auto GameScoreStr = std::make_shared<graph::Text>(
        graph::Text("TITLE15", "Please Select A Game Using X or C: ", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(18, 18)));
    auto PlayerLib = std::make_shared<graph::Text>(
        graph::Text("TITLE16", "Lib: ", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(18, 10)));
    auto PlayerGame = std::make_shared<graph::Text>(
        graph::Text("TITLE17", "Game: ", "asset/font/Times New Romance.ttf", 22, core::Color::RED, graph::Coords(18, 24)));
    _obj.emplace_back(LibScoreStr);
    _obj.emplace_back(GameScoreStr);
    _obj.emplace_back(PlayerLib);
    _obj.emplace_back(PlayerGame);
    _state = 2;
}

void game::Menu::_setPlayerName(std::size_t input)
{
    auto it = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
        return i.get()->uid == "TITLE1";
    });
    if (it == _obj.end())
        return;

    auto *playerName = (graph::Text *)(&(*(*it)));
    if (input == core::DELETE)
    {
        if (!playerName->text.empty())
            playerName->text.pop_back();
    }
    else if (input == core::SELECT && playerName->text.length() > 0)
    {
        auto it = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
            return i.get()->uid == "TITLE12";
        });
        auto *ValuePlayerName = (graph::Text *)(&(*(*it)));
        ValuePlayerName->text = playerName->text;
        _playerName = playerName->text;
        auto at = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
            return i.get()->uid == "TITLE1";
        });
        auto ot = std::find_if(_obj.begin(), _obj.end(), [](std::shared_ptr<graph::Object> &i) {
            return i.get()->uid == "TITLE8";
        });
        _obj.erase(at);
        _obj.erase(ot);
        _state = 1;
    }
    else if (input <= core::ASCII_END && std::isalpha(input) && playerName->text.length() < 20)
        if (it != _obj.end())
            playerName->text += input;
}

void game::Menu::update(std::size_t input, double)
{
    if (_state == 0)
        _setPlayerName(input);
    else if (_state == 1)
        _setGameAndLib();
    else if (_state == 2)
        _selectGameAndLib(input);
}

const std::string &game::Menu::getGameName() const noexcept
{
    return (_gameName);
}

void game::Menu::end()
{
}

game::objVector game::Menu::dumpObjects()
{
    return (_obj);
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GAME);
}

extern "C" game::IGame *createGraphicLib()
{
    return (new game::Menu());
}
