/*
** EPITECH PROJECT, 2021
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** Sdl2Encapsulation
*/

#include "EnumLdl.hpp"
#include "Sdl2Encapsulation.hpp"

#include "Text.hpp"
#include "UiBox.hpp"
#include "Image.hpp"

graph::Sdl2Encapsulation::Sdl2Encapsulation() : ADisplay("./lib/arcade_sdl2.so", 0, 0), _window(nullptr), _windowRender(nullptr), _windowSurface(nullptr),
    _windowTexture(nullptr)
{
    std::cout << "build sdl2 = " << _textureArr.size() << "\n";
}

void graph::Sdl2Encapsulation::_initFont(std::string fp, std::size_t size)
{
    TTF_Init();

    _font = TTF_OpenFont(fp.c_str(), size);
    if (!_font)
        throw err::Sdl2Error("Font cannot be load" + std::string(TTF_GetError()));
}

void graph::Sdl2Encapsulation::_initColor()
{
    SDL_Color BLACK = {0, 0, 0, 0};
    SDL_Color WHITE = {255, 255, 255, 0};
    SDL_Color BLUE = {0, 0, 255, 0};
    SDL_Color GREEN = {0, 255, 0, 0};
    SDL_Color PURPLE = {128, 0, 128, 0};
    SDL_Color DARK_BLUE = {0, 0, 139, 0};
    SDL_Color RED = {255, 0, 0, 0};
    SDL_Color INVISIBLE = {255, 255, 255, 1};

    _colorArr[0] = BLACK;
    _colorArr[1] = WHITE;
    _colorArr[2] = BLUE;
    _colorArr[3] = GREEN;
    _colorArr[4] = PURPLE;
    _colorArr[5] = DARK_BLUE;
    _colorArr[6] = RED;
    _colorArr[7] = INVISIBLE;
}

void graph::Sdl2Encapsulation::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw err::Sdl2Error("Failed to initialize the SDL2 library\nSDL2 Error: " + std::string(SDL_GetError()));
    std::cout << "Initiation of the " << getLibName() << " library." << std::endl;
    _window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 960, SDL_WINDOW_SHOWN);
    if (!_window)
        throw err::Sdl2Error("Failed to create window\nSDL2 Error: " + std::string(SDL_GetError()));
    _windowRender = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_windowRender == nullptr)
        throw err::Sdl2Error("SDL_CreateRenderer SDL2 Error: " + std::string(SDL_GetError()) + "\n");
    _initColor();
    IMG_Init(IMG_INIT_PNG);
}

void graph::Sdl2Encapsulation::_drawText(graph::Object &obj)
{
    const auto *text = (graph::Text*)&obj;

    _initFont(text->fontPath, text->size);
    _rect.x = (text->pos.first + text->offset.first) * 16;
    _rect.y = (text->pos.second + text->offset.second) * 16;
    _rect.w *= 16;
    _rect.h *= 16;
    _windowSurface = TTF_RenderText_Solid(_font, text->text.c_str(), _colorArr.at(obj.color));
    _windowTexture = SDL_CreateTextureFromSurface(_windowRender, _windowSurface);
    SDL_QueryTexture(_windowTexture, NULL, NULL, &_rect.w, &_rect.h);
    SDL_RenderCopy(_windowRender, _windowTexture, NULL, &_rect);
    SDL_FreeSurface(_windowSurface);
    TTF_CloseFont(_font);
	TTF_Quit();
}

void graph::Sdl2Encapsulation::_drawUI(graph::Object &obj)
{
    const auto *square = (graph::UIBox *)&obj;

    SDL_SetRenderDrawColor(_windowRender, 255, 255, 255, 255);
    _rect.x = (square->pos.first + square->offset.first) * 16;
    _rect.y = (square->pos.second + square->offset.second) * 16;
    _rect.w = square->size.first * 16;
    _rect.h = square->size.second * 16;
    SDL_RenderDrawRect(_windowRender, &_rect);
    SDL_SetRenderDrawColor(_windowRender, 0, 0, 0, 255);
}

void graph::Sdl2Encapsulation::_drawTexture(graph::Object &obj)
{
    const auto *image = (graph::Image *)&obj;

    if (_textureArr.count(image->m_texturePath) <= 0) {
        std::cout << "pas load = " << image->m_texturePath << "\n";
        _windowSurface = IMG_Load(image->m_texturePath.c_str());
        std::cout << "pas load 1 = " << image->m_texturePath << "\n";
        _windowTexture = SDL_CreateTextureFromSurface(_windowRender, _windowSurface);
        std::cout << "pas load 2 = " << image->m_texturePath << "\n";
        SDL_FreeSurface(_windowSurface);
        std::cout << "pas load 5 = " << image->m_texturePath << "\n";
        _textureArr.try_emplace(image->m_texturePath, _windowTexture);
        std::cout << "pas load 6 = " << image->m_texturePath << "\n";
    }
    _rect.x = (image->pos.first + image->offset.first) * 16;
    _rect.y = (image->pos.second + image->offset.second) * 16;
    _rect.h = 16;
    _rect.w = 16;
    if (SDL_RenderCopy(_windowRender, _textureArr.at(image->m_texturePath), NULL, &_rect) == -1)
        throw err::Sdl2Error("SDL_RenderCopy Error \nSDL2 Error: " + std::string(SDL_GetError()));
}

void graph::Sdl2Encapsulation::draw(graph::Object &obj)
{
    _rect.x = obj.pos.first;
    _rect.y = obj.pos.second;

    static const std::map<core::ObjectType, std::function<void(graph::Object &)>> map{{core::ObjectType::IMAGE, [this](graph::Object &obj) {
        _drawTexture(obj);
    }}, {core::ObjectType::TEXT, [this](graph::Object &obj) {
        _drawText(obj);
    }}, {core::ObjectType::BOX_UI, [this](graph::Object &obj) {
        _drawUI(obj);
    }}};
    map.at(obj.type)(obj);
}

void graph::Sdl2Encapsulation::updateWindow()
{
    SDL_RenderPresent(_windowRender);
    SDL_RenderClear(_windowRender);
}

void graph::Sdl2Encapsulation::destroy()
{
	SDL_DestroyTexture( _windowTexture );
	SDL_DestroyRenderer( _windowRender );
	SDL_DestroyWindow( _window );

	IMG_Quit();
	SDL_Quit();
    std::cout << "Stopping the " << getLibName() << " library." << std::endl;
}

int graph::Sdl2Encapsulation::pollEvent()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
                return (core::KeyBoard::ARROW_UP);
            case SDLK_DOWN:
                return (core::KeyBoard::ARROW_DOWN);
            case SDLK_LEFT:
                return (core::KeyBoard::ARROW_LEFT);
            case SDLK_RIGHT:
                return (core::KeyBoard::ARROW_RIGHT);
            case SDLK_BACKSPACE:
                return (core::KeyBoard::DELETE);
            case SDLK_RETURN:
                return (core::KeyBoard::SELECT);
            case SDLK_ESCAPE:
                return (core::KeyBoard::ESCAPE);
            }
            if (e.key.keysym.sym >= 0 && e.key.keysym.sym <= core::KeyBoard::ASCII_END)
                return e.key.keysym.sym;
        }
    }
    return core::KeyBoard::NONE;
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GRAPHIC);
}

extern "C" graph::IGraphic *createGraphicLib()
{
    return (new graph::Sdl2Encapsulation());
}

extern "C" void destroyGraphicLib(graph::IGraphic *t_lib)
{
    delete t_lib;
}