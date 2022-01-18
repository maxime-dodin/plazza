/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ldl.cpp.cc
*/
#include "Ldl.hpp"

arcade::Ldl::Ldl(const std::string &fp)
{
    if (!(_handle = dlopen(fp.c_str(), RTLD_LAZY)))
        throw (err::LoaderException(dlerror()));
}

arcade::Ldl::Ldl(arcade::Ldl &&other) noexcept
{
    _handle = other._handle;
    other._handle = nullptr;
}

arcade::Ldl::~Ldl()
{
    if (_handle)
        dlclose(_handle);
}
