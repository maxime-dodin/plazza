/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** Sdl2Encapsulation
*/

#ifndef SDL2ENCAPSULATION_HPP_
#define SDL2ENCAPSULATION_HPP_

#include "Error.hpp"

#include "EnumCore.hpp"

#include "ADisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <ctime>
#include <fstream>

namespace graph
{
    class Sdl2Encapsulation final : public graph::ADisplay {
    public:
        Sdl2Encapsulation();
        ~Sdl2Encapsulation() final = default;

        void init() final;

        void destroy() final;

        void updateWindow() final;

        void draw(graph::Object &obj) final;

        [[nodiscard]] int pollEvent() final;


    private:

        void _initColor();

        void _initFont(std::string fp, size_t size);

        void _initTexture(const std::string&, const std::string&);

        void _drawUI(graph::Object &obj);

        void _drawText(graph::Object &obj);

        void _drawTexture(graph::Object &obj);

        std::map<std::string, SDL_Texture*> _textureArr;
        std::map<std::size_t, SDL_Color> _colorArr;

        SDL_Window *_window;
        SDL_Renderer* _windowRender;
        SDL_Surface *_windowSurface;
        SDL_Texture *_windowTexture;
        TTF_Font* _font;
        SDL_Rect _rect;
    };
}

#endif /* !SDL2ENCAPSULATION_HPP_ */
