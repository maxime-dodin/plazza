/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** pac_man.cpp.cc
*/

#include "EnumLdl.hpp"
#include "PacMan.hpp"
#include "Image.hpp"

game::PacMan::PacMan() : game::AGame("./lib/arcade_pacman.so")
{
    std::cout << "JE LOAD LE PACMAN" << "\n";
}

void game::PacMan::_enemyAI()
{
}

void game::PacMan::_makeMap(std::size_t maxHeight, std::size_t maxWidth)
{
    std::ifstream file;
    std::size_t x = 1;
    std::size_t y = 0;
    char carac = 0;
    (void)maxHeight;
    (void)maxWidth;
    int nbGhost = 0;
    std::map<std::size_t, std::string> ghostTexture = {{0, "./asset/sprite/orange_ghost.png"}, {1, "./asset/sprite/blue_ghost.png"}, {2, "./asset/sprite/red_ghost.png"}};

    file.open("./game/pacman/map.txt", std::ios::binary);
    if (!file.is_open())
        std::cerr << "Error while openning the map of Nibbler" << std::endl;
    while (file.get(carac))
    {
        if (carac == '\n')
        {
            y++;
            x = 0;
        }
        // std::map<char, std::function<game::AGameObject (int, int)>> obj_map = {
        //     {'0', [](int x, int y){return (graph::Coords(x, y), game::createUID(), "./asset/sprite/wall.resized.png", '#', true);}}
        // };

        // _objVecGame.emplace_back(obj_map[carac](x, y));

        else if (carac == '0')
        {
            game::StaticObject wall(graph::Coords(x, y), game::createUID(), "./asset/sprite/wall.resized.png", '#', true);
            _objVecGame.emplace_back(wall);
            arr.emplace_back(wall.obj);
        }
        else if (carac == '1')
        {
            game::StaticObject gold(graph::Coords(x, y), game::createUID(), "./asset/sprite/gold_resized.png", '.', false);
            _objVecGame.emplace_back(gold);
            arr.emplace_back(gold.obj);
        }
        else if (carac == '2')
        {
            game::AliveMovableObject player(graph::Coords(x, y), "player", "./asset/sprite/pacman.jpg", 'O', 1, game::Direction::UP, true);
            _objVecGame.emplace_back(player);
            arr.emplace_back(player.obj);
        }
        else if (carac == '3' && nbGhost < 3)
        {
            game::EnemyMovableObject ghost(graph::Coords(x, y), "enenmi" + (char)nbGhost, ghostTexture.at(nbGhost), '&', 1, game::Direction::UP, true, _enemyAI, false);
            _objVecGame.emplace_back(ghost);
            arr.emplace_back(ghost.obj);
            nbGhost += 1;
        }
        else if (carac == '4')
        {
            game::StaticObject cherry(graph::Coords(x, y), game::createUID(), "./asset/sprite/cherry.png", '*', true);
            _objVecGame.emplace_back(cherry);
            arr.emplace_back(cherry.obj);
        }
        x++;
    }
    file.close();
}

void game::PacMan::init()
{
    _makeMap(48, 60);
}

void game::PacMan::update(std::size_t input, double deltaTime)
{
    (void)deltaTime;
    auto it = std::find_if(_objVecGame.begin(), _objVecGame.end(), [](game::AGameObject const &i) { return i.type == game::Type::ALIVE_MOVABLE_OBJECT; });
    auto player = (game::AliveMovableObject *)(&(*(it)));

    switch (input)
     {
     case core::KeyBoard::ARROW_UP:
         player->_direction = Direction::UP;
         break;
     case core::KeyBoard::ARROW_DOWN:
         player->_direction = Direction::DOWN;
         break;
     case core::KeyBoard::ARROW_LEFT:
         player->_direction = Direction::LEFT;
         break;
     case core::KeyBoard::ARROW_RIGHT:
         player->_direction = Direction::RIGHT;
         break;
     default:
         break;
     }
}

void game::PacMan::end()
{
}

game::objVector game::PacMan::dumpObjects()
{
    return (arr);
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GAME);
}

extern "C" game::IGame *createGraphicLib()
{
    return (new game::PacMan());
}