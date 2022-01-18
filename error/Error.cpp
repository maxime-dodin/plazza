/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Error.cpp.cc
*/
#include "Error.hpp"
#include <utility>

err::ArcadeError::ArcadeError(std::string message, std::string component) : _message(std::move(message)), _component(std::move(component))
{
}

std::string const &err::ArcadeError::where() const
{
    return (_component);
}

const char *err::ArcadeError::what() const noexcept
{
    return (_message.c_str());
}

err::GraphicError::GraphicError(const std::string &message, const std::string &component) : ArcadeError(message, component)
{
}

err::NcursesError::NcursesError(const std::string &message, const std::string &component) : GraphicError(message, component)
{
}

err::Sdl2Error::Sdl2Error(const std::string &message, const std::string &component) : GraphicError(message, component)
{
}

err::ObjectError::ObjectError(const std::string &message, const std::string &component) : ArcadeError(message, component)
{
}

err::TextError::TextError(const std::string &message, const std::string &component) : ObjectError(message, component)
{
}

err::GameObjectError::GameObjectError(const std::string &message, const std::string &component) : ArcadeError(message, component)
{
}

err::LoaderException::LoaderException(const std::string &message, const std::string &component) : ArcadeError(message, component)
{
}
