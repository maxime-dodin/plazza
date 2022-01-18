/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** nibbler.cpp.cc
*/
#include "EnumLdl.hpp"
#include "Nibbler.hpp"
#include "Image.hpp"
#include "EnumCore.hpp"
#include <random>

game::Nibbler::Nibbler() : game::AGame("./lib/arcade_nibbler.so")
{
}

void game::Nibbler::_enemyAI() {
}

void game::Nibbler::_makeMap(std::size_t maxHeight, std::size_t maxWidth) {
    std::ifstream file;
    std::size_t x = 1;
    std::size_t y = 0;
    char carac = 0;
    (void) maxHeight;
    (void) maxWidth;

    file.open("./game/nibbler/map.txt", std::ios::binary);
    if (!file.is_open())
        std::cerr << "Error while openning the map of Nibbler" << std::endl;
    while (file.get(carac)) {
        if (carac == '\n') {
            y++;
            x = 0;
        }
        else if (carac == '0') {
            game::StaticObject wall(graph::Coords(x, y), game::createUID(), "./asset/sprite/wall.resized.png", '#', true);
            _objVecGame.emplace_back(wall);
            wall.obj->color = core::Color::RED;
            arr.emplace_back(wall.obj);
        } else if (carac == '2') {
            game::AliveMovableObject snakeHead(graph::Coords(x, y), game::createUID(), "./asset/sprite/snake_head.resized.png", 'O', 1, game::Direction::UP, true);
            _objVecGame.emplace_back(snakeHead);
            snakeHead.obj->color = core::Color::BLUE;
            arr.emplace_back(snakeHead.obj);
        } else if (carac == '3') {
            game::EnemyMovableObject snakeBody(graph::Coords(x, y), game::createUID(), "./asset/sprite/snake_body.png", 'I', 1, game::Direction::UP, true, _enemyAI, false);
            _objVecGame.emplace_back(snakeBody);
            arr.emplace_back(snakeBody.obj);
        } else if (carac == '4') {
            game::StaticObject bonus(graph::Coords(x, y), game::createUID(), "./asset/sprite/bonus.resized.png", 'X', false);
            _objVecGame.emplace_back(bonus);
            arr.emplace_back(bonus.obj);
        }
        x++;
    }
    file.close();
}

std::pair<std::size_t, std::size_t> game::Nibbler::_setBonusPos(std::size_t maxHeight, std::size_t maxWidth) {
    std::size_t x = std::rand() % maxWidth;
    std::size_t y = std::rand() % maxHeight;

    return (std::make_pair(x, y));
}

void game::Nibbler::_putBonus(std::size_t maxHeight, std::size_t maxWidth) {
    std::pair<std::size_t, std::size_t> pos = _setBonusPos(maxHeight, maxWidth);
    for (const auto &it : arr)
        if (pos == it.get()->pos)
            pos = _setBonusPos(maxHeight, maxWidth);
    game::StaticObject bonus(graph::Coords(pos), game::createUID(), "./asset/sprite/bonus.resized.png", 'X', false);
    _objVecGame.emplace_back(bonus);
    arr.emplace_back(bonus.obj);
}

void game::Nibbler::init()
{
    std::srand(time(nullptr));
    _makeMap(48, 60);
    _putBonus(48, 60);
}

void game::Nibbler::_changeDirection(game::AliveMovableObject &obj, std::size_t input) {
    std::cout << "Input value: " << (game::Direction::UP == obj._direction) << std::endl;
    if ((obj._direction == game::Direction::UP && input == core::KeyBoard::ARROW_LEFT)
    || (obj._direction == game::Direction::DOWN && input == core::KeyBoard::ARROW_LEFT))
        obj._direction = game::Direction::LEFT;
    else if ((obj._direction == game::Direction::UP && input == core::KeyBoard::ARROW_RIGHT)
    || (obj._direction == game::Direction::DOWN && input == core::KeyBoard::ARROW_RIGHT))
        obj._direction = game::Direction::RIGHT;
    else if ((obj._direction == game::Direction::RIGHT && input == core::KeyBoard::ARROW_UP)
    || (obj._direction == game::Direction::LEFT && input == core::KeyBoard::ARROW_UP))
        obj._direction = game::Direction::UP;
    else if ((obj._direction == game::Direction::RIGHT && input == core::KeyBoard::ARROW_DOWN)
    || (obj._direction == game::Direction::LEFT && input == core::KeyBoard::ARROW_DOWN))
        obj._direction = game::Direction::DOWN;
    else
        std::cerr << "Euh ça marche pas ça" << std::endl;
    std::cout << (input == game::Direction::LEFT) << std::endl;
}

void game::Nibbler::_giveNewDirection(std::size_t input) {
    for (auto &it : _objVecGame)
        if (it.type == game::Type::ALIVE_MOVABLE_OBJECT)
            _changeDirection(*(game::AliveMovableObject *) &it, input);
}

void game::Nibbler::update(std::size_t input, double deltaTime)
{
    (void) deltaTime;
    if (input == core::KeyBoard::ARROW_UP || input == core::KeyBoard::ARROW_DOWN ||
            input == core::KeyBoard::ARROW_LEFT || input == core::KeyBoard::ARROW_RIGHT)
        _giveNewDirection(input);
}

void game::Nibbler::end()
{
    std::cout << "end Nibler" << "\n";
}

game::objVector game::Nibbler::dumpObjects()
{
    return (arr);
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GAME);
}

extern "C" game::IGame *createGraphicLib()
{
    return (new game::Nibbler());
}
