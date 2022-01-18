/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** NcursesEncapsulation.cpp.cc
*/
#include "EnumLdl.hpp"
#include "NcursesEncapsulation.hpp"
#include "Error.hpp"
#include <thread>

graph::NcursesEncapsulation::NcursesEncapsulation() : ADisplay("./lib/arcade_ncurses.so", 1920, 1080)
{
}

void graph::NcursesEncapsulation::_initColor()
{
    if (start_color() == ERR || !has_colors() || !can_change_color())
        throw err::NcursesError("Could not use colors.");
    init_pair(0, COLOR_BLACK, COLOR_WHITE);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_WHITE);
    init_pair(8, COLOR_CYAN, COLOR_CYAN);
    init_pair(9, COLOR_GREEN, COLOR_GREEN);
    init_pair(10, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(11, COLOR_BLUE, COLOR_BLUE);
    init_pair(12, COLOR_RED, COLOR_RED);
}

void graph::NcursesEncapsulation::init()
{
    std::cout << "Initiation of the " << getLibName() << " library." << std::endl;
    if (!(initscr()))
        throw err::NcursesError("Could not initialize basic screen.");
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
    _initColor();
    box(stdscr, ACS_VLINE, ACS_HLINE);
}

void graph::NcursesEncapsulation::destroy()
{
    for (auto &[x, y] : _uiMap)
        if (y)
            delwin(y);
    endwin();
    std::cout << "Stopping the " << getLibName() << " library." << std::endl;
}

void graph::NcursesEncapsulation::updateWindow()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    clear();
}

void graph::NcursesEncapsulation::_drawImage(graph::Object &obj)
{
    std::string text;

    wattron(stdscr, COLOR_PAIR(obj.color));
    text.push_back(((graph::Image *)(&obj))->m_defaultChar);
    mvwprintw(stdscr, obj.pos.second, obj.pos.first, text.c_str());
    for (auto &[x, y] : _uiMap)
        wrefresh(y);
    refresh();
    wattroff(stdscr, COLOR_PAIR(obj.color));
}

void graph::NcursesEncapsulation::_drawText(graph::Object &obj)
{
    wattron(stdscr, COLOR_PAIR(obj.color));
    mvwprintw(stdscr, obj.pos.second + obj.offset.second, obj.pos.first + obj.offset.first, ((graph::Text *)(&obj))->text.c_str());
    wattroff(stdscr, COLOR_PAIR(obj.color));
    for (auto &[x, y] : _uiMap)
        wrefresh(y);
    refresh();
}

void graph::NcursesEncapsulation::_drawUI(graph::Object &obj)
{
    try {
        _uiMap.at(obj.uid);
    } catch (const std::out_of_range &e) {
        auto ui = reinterpret_cast<graph::UIBox *>(&obj);
        _uiMap.emplace(obj.uid, subwin(stdscr, ui->size.second, ui->size.first, ui->pos.second, ui->pos.first));
    }
    wattron(_uiMap.at(obj.uid), COLOR_PAIR(obj.color));
    wattron(stdscr, COLOR_PAIR(obj.color));
    box(_uiMap.at(obj.uid), ACS_VLINE, ACS_HLINE);
    box(stdscr, ACS_VLINE, ACS_HLINE);
    wattroff(_uiMap.at(obj.uid), COLOR_PAIR(obj.color));
    wattroff(stdscr, COLOR_PAIR(obj.color));
    wrefresh(_uiMap.at(obj.uid));
    refresh();
}

void graph::NcursesEncapsulation::draw(graph::Object &obj)
{
    static const std::map<core::ObjectType, std::function<void(graph::Object &)>> map{{core::ObjectType::IMAGE, [this](graph::Object &obj) {
        _drawImage(obj);
    }}, {core::ObjectType::TEXT, [this](graph::Object &obj) {
        _drawText(obj);
    }}, {core::ObjectType::BOX_UI, [this](graph::Object &obj) {
        _drawUI(obj);
    }}};
    map.at(obj.type)(obj);
}

int graph::NcursesEncapsulation::pollEvent()
{
    int e = getch();

    switch (e) {
    case KEY_UP:
        return (core::KeyBoard::ARROW_UP);
    case KEY_DOWN:
        return (core::KeyBoard::ARROW_DOWN);
    case KEY_LEFT:
        return (core::KeyBoard::ARROW_LEFT);
    case KEY_RIGHT:
        return (core::KeyBoard::ARROW_RIGHT);
    case 27:
        return (core::KeyBoard::ESCAPE);
    case KEY_BACKSPACE:
        return (core::KeyBoard::DELETE);
    case '\n':
        return (core::KeyBoard::SELECT);
    default:
        break;
    }
    if (e >= 0 && e <= core::KeyBoard::ASCII_END)
        return (e);
    return (core::KeyBoard::NONE);
}

extern "C" arcade::LIB_TYPE getLibType()
{
    return (arcade::LIB_TYPE::GRAPHIC);
}

extern "C" graph::IGraphic *createGraphicLib()
{
    return (new graph::NcursesEncapsulation());
}

extern "C" void destroyGraphicLib(graph::IGraphic *t_lib)
{
    delete t_lib;
}