/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ADisplay.cpp.c
*/
#include "ADisplay.hpp"
#include <utility>

graph::ADisplay::ADisplay(std::string libName, std::size_t height, std::size_t width) : _libName(std::move(libName)), _height(height), _width(width)
{
}

const std::string &graph::ADisplay::getLibName() const noexcept
{
    return (_libName);
}
