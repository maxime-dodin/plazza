/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Ldl.hpp.h
*/
#ifndef ARCADE_LDL_HPP
#define ARCADE_LDL_HPP

#include "IGraphic.hpp"
#include "IGame.hpp"
#include "Error.hpp"
#include "EnumLdl.hpp"
#include <dlfcn.h>
#include <iostream>
#include <vector>

namespace arcade {
    class Ldl {
        public:

        explicit Ldl(const std::string &fp);

        Ldl(Ldl &&other) noexcept;

        ~Ldl();

        template<class T>
        T loadSymbol(const std::string &t_symbol)
        {
            auto symbol = (T)dlsym(_handle, t_symbol.c_str());

            if (!symbol)
                throw (err::LoaderException(dlerror()));
            return (symbol);
        }

        private:
        void *_handle;
    };
}

#endif //ARCADE_LDL_HPP
