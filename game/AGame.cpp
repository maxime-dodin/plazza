/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** AGame.cpp.cc
*/
#include "AGame.hpp"
#include <utility>
#include <chrono>

game::AGame::AGame(std::string gameName) : _gameName(std::move(gameName))
{
}

const std::string &game::AGame::getGameName() const noexcept
{
    return (_gameName);
}

std::string game::createUID() {
    static uint64_t toto = 0;

    return (std::to_string(toto++));
}