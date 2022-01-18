/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesEncapsulation.hpp.h
*/
#ifndef ARCADE_NCURSESENCAPSULATION_HPP
#define ARCADE_NCURSESENCAPSULATION_HPP

#include "ADisplay.hpp"
#include "EnumCore.hpp"
#include "Text.hpp"
#include "UiBox.hpp"
#include "Image.hpp"
#include <ncurses.h>
#include <iostream>
#include <functional>
#include <map>

namespace graph {
    class NcursesEncapsulation final : public graph::ADisplay {
        public:
        NcursesEncapsulation();

        ~NcursesEncapsulation() final = default;

        void init() final;

        void destroy() final;

        void updateWindow() final;

        void draw(graph::Object &obj) final;

        [[nodiscard]] int pollEvent() final;

        private:
        static void _initColor();

        void _drawText(graph::Object &obj);

        void _drawImage(graph::Object &obj);

        void _drawUI(graph::Object &obj);

        std::map<std::string, WINDOW *> _uiMap;
    };
}

#endif //ARCADE_NCURSESENCAPSULATION_HPP
