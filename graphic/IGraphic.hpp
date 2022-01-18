    /*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** IGraphic.hpp.h
*/
#ifndef ARCADE_IGRAPHIC_HPP
#define ARCADE_IGRAPHIC_HPP

#include "Object.hpp"
#include <utility>
#include <string>
#include <iostream>
#include <memory>

namespace graph {
    class IGraphic {
        public:
        virtual ~IGraphic() = default;

        virtual void init() = 0;

        virtual void destroy() = 0;

        virtual void updateWindow() = 0;

        [[nodiscard]] virtual const std::string &getLibName() const noexcept = 0;

        virtual void draw(graph::Object &obj) = 0;

        [[nodiscard]] virtual int pollEvent() = 0;
    };
}

#endif //ARCADE_IGRAPHIC_HPP