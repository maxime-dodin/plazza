/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** SfmlEncapsulation.h
*/
#ifndef B_OOP_400_PAR_4_1_ARCADE_KILLIAN_FLEURY_SFMLENCAPSULATION_H
#define B_OOP_400_PAR_4_1_ARCADE_KILLIAN_FLEURY_SFMLENCAPSULATION_H

#include "Error.hpp"

#include "ADisplay.hpp"
#include "EnumCore.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "UiBox.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <memory>

namespace graph {
class SfmlEncapsulation final : public graph::ADisplay
    {
    public:
        SfmlEncapsulation();

        ~SfmlEncapsulation() final = default;

        void init() final;

        void destroy() final;

        void draw(graph::Object &obj) final;

        void updateWindow() final;

        [[nodiscard]] int pollEvent() final;

    private:
        void _initFont();

        void _initTexture();

        void _initColors();

        void _drawTexture(graph::Object &obj);

        void _drawText(graph::Object &obj);

        void _drawUI(graph::Object &obj);

        sf::VideoMode _videoMode;

        sf::RenderWindow _window;

        sf::Event _event;

        sf::Font _font;

        std::map<std::string, sf::Texture> _textureArr;

        std::map<std::string, std::shared_ptr<sf::Text>> _textArr;

        std::map<std::string, sf::Sprite> _spriteArr;

        std::map<core::Color, sf::Color> colors;
    };
}

#endif //B_OOP_400_PAR_4_1_ARCADE_KILLIAN_FLEURY_SFMLENCAPSULATION_H