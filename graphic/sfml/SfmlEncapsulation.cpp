/*
** EPITECH PROJECT, 2024
** B-OOP-400-PAR-4-1-arcade-killian.fleury
** File description:
** SfmlEncapsulation.cpp.cc
*/

#include "EnumLdl.hpp"
#include "SfmlEncapsulation.hpp"

graph::SfmlEncapsulation::SfmlEncapsulation() : ADisplay("./lib/arcade_sfml.so", 0, 0), _videoMode(1920, 1080), _window(_videoMode, "Arcade"), _event()
{
}

void graph::SfmlEncapsulation::_initFont()
{
    std::cout << "Initialisation of the font" << std::endl;
    sf::Font font;
    _font = font;
    if (!_font.loadFromFile("asset/font/Times New Romance.ttf"))
        std::cerr << "Error while loading font from file" << std::endl;
}

void graph::SfmlEncapsulation::_initColors()
{
    colors[core::Color::BLACK] = sf::Color::Black;
    colors[core::Color::WHITE] = sf::Color::White;
    colors[core::Color::BLUE] = sf::Color::Cyan;
    colors[core::Color::GREEN] = sf::Color::Green;
    colors[core::Color::PURPLE] = sf::Color::Magenta;
    colors[core::Color::DARK_BLUE] = sf::Color::Blue;
    colors[core::Color::RED] = sf::Color::Red;
    colors[core::Color::INVISIBLE] = sf::Color::Transparent;
}

void graph::SfmlEncapsulation::init()
{
    std::cout << "Initialisation of the SFML library" << std::endl;
    _window.setFramerateLimit(60);
    _initFont();
    _initColors();
}

void graph::SfmlEncapsulation::destroy()
{
    _window.close();
    std::cout << "Stopping the SFML library" << std::endl;
}

void graph::SfmlEncapsulation::updateWindow()
{
    _window.display();
    _window.clear();
}

int graph::SfmlEncapsulation::pollEvent()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            _window.close();
            return (core::KeyBoard::EXIT);
        }
        if (_event.type == sf::Event::KeyPressed)
            switch (_event.key.code) {
            case sf::Keyboard::Up:
                return (core::KeyBoard::ARROW_UP);
            case sf::Keyboard::Down:
                return (core::KeyBoard::ARROW_DOWN);
            case sf::Keyboard::Left:
                return (core::KeyBoard::ARROW_LEFT);
            case sf::Keyboard::Right:
                return (core::KeyBoard::ARROW_RIGHT);
            case sf::Keyboard::Backspace:
                return (core::KeyBoard::ESCAPE);
            case sf::Keyboard::Enter:
                return (core::KeyBoard::SELECT);
            case sf::Keyboard::Escape:
                return (core::KeyBoard::DELETE);
            case sf::Keyboard::A:
                //_window.close();
                return ('a');
            case sf::Keyboard::B:
                return ('b');
            case sf::Keyboard::C:
                return ('c');
            case sf::Keyboard::D:
                return ('d');
            case sf::Keyboard::E:
                //_window.close();
                return ('e');
            case sf::Keyboard::F:
                return ('f');
            case sf::Keyboard::G:
                return ('g');
            case sf::Keyboard::H:
                return ('h');
            case sf::Keyboard::I:
                return ('i');
            case sf::Keyboard::J :
                return ('j');
            case sf::Keyboard::K :
                return ('k');
            case sf::Keyboard::L :
                return ('l');
            case sf::Keyboard::M :
                return ('m');
            case sf::Keyboard::N :
                return ('n');
            case sf::Keyboard::O :
                return ('o');
            case sf::Keyboard::P :
                return ('p');
            case sf::Keyboard::Q :
                return ('q');
            case sf::Keyboard::R :
                return ('r');
            case sf::Keyboard::S :
                return ('s');
            case sf::Keyboard::T :
                return ('t');
            case sf::Keyboard::U :
                return ('u');
            case sf::Keyboard::V :
                return ('v');
            case sf::Keyboard::W :
                return ('w');
            case sf::Keyboard::X :
                return ('x');
            case sf::Keyboard::Y :
                return ('y');
            case sf::Keyboard::Z :
                return ('z');
            default:
                return (-1);
            }
    }
    return (-1);
}

void graph::SfmlEncapsulation::_drawTexture(graph::Object &obj)
{
    auto image = (graph::Image *)&obj;
    sf::Sprite tempSprite;
    sf::Texture tempTexture;

    std::cout << "Draw texture" << std::endl;
    if (_textureArr.find(image->m_texturePath) == _textureArr.end()) {
        std::cout << "Texture not loaded" << std::endl;
        if (!tempTexture.loadFromFile(image->m_texturePath)) {
            std::cerr << "Error while loading texture of element: " << obj.uid << std::endl;
            return;
        }
        _textureArr[image->m_texturePath] = std::move(tempTexture);
        tempSprite.setTexture(_textureArr[image->m_texturePath]);
        _spriteArr[obj.uid] = std::move(tempSprite);
    }
    if (_spriteArr.find(obj.uid) == _spriteArr.end()) {
        std::cout << "Sprite not loaded" << std::endl;
        tempSprite.setTexture(_textureArr[image->m_texturePath]);
        _spriteArr[obj.uid] = std::move(tempSprite);
    }
    tempSprite = _spriteArr.at(obj.uid);
    tempSprite.setPosition(sf::Vector2f((obj.pos.first + obj.offset.first) * 16, (obj.pos.second + obj.offset.second) * 16));
    tempSprite.setScale(sf::Vector2f(0.35, 0.35));
    _window.draw(tempSprite);
}

void graph::SfmlEncapsulation::_drawText(graph::Object &obj)
{
    sf::Text temp;
    auto temp2 = (graph::Text *)&obj;

    temp.setString(temp2->text);
    temp.setFont(_font);
    temp.setCharacterSize(20);
    temp.setFillColor(sf::Color::Red);
    temp.setPosition(sf::Vector2f((obj.pos.first + obj.offset.first) * 16, (obj.pos.second + obj.offset.second) * 16));
    _window.draw(temp);
}

void graph::SfmlEncapsulation::_drawUI(graph::Object &obj)
{
    sf::RectangleShape temp;
    auto temp2 = (graph::UIBox *)&obj;

    temp.setSize(sf::Vector2f(temp2->size.first * 16, temp2->size.second * 16));
    temp.setPosition(sf::Vector2f((obj.pos.first + obj.offset.first) * 16, (obj.pos.second + obj.offset.second) * 16));
    temp.setOutlineThickness(1);
    temp.setOutlineColor(colors[obj.color]);
    temp.setFillColor(colors.at(core::INVISIBLE));
    _window.draw(temp);
}

void graph::SfmlEncapsulation::draw(graph::Object &obj)
{
    static const std::map<core::ObjectType, std::function<void(graph::Object &)>> map{{core::ObjectType::IMAGE, [this](graph::Object &obj) {
        _drawTexture(obj);
    }}, {core::ObjectType::TEXT, [this](graph::Object &obj) {
        _drawText(obj);
    }}, {core::ObjectType::BOX_UI, [this](graph::Object &obj) {
        _drawUI(obj);
    }}};
    map.at(obj.type)(obj);
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GRAPHIC);
}

extern "C" graph::IGraphic *createGraphicLib()
{
    return (new graph::SfmlEncapsulation());
}

extern "C" void destroyGraphicLib(graph::IGraphic *t_lib)
{
    delete t_lib;
}
