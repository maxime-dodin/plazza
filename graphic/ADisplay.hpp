/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** ADisplay.hpp.h
*/
#ifndef ARCADE_ADISPLAY_HPP
#define ARCADE_ADISPLAY_HPP

#include "IGraphic.hpp"
#include <map>
#include <vector>

namespace graph {
    class ADisplay : public graph::IGraphic {
        public:
        explicit ADisplay(std::string libName, std::size_t height, std::size_t width);

        static const std::map<std::string, std::string> uidArrAndPath;

        ~ADisplay() override = default;

        [[nodiscard]] const std::string &getLibName() const noexcept override;

        protected:
        std::string _libName;

        std::size_t _height;

        std::size_t _width;

        std::vector<std::string> _uidArr;
    };
}

template<class T>
class Split {
    public:
    Split(std::string str, std::string delim) : _str(std::move(str)), _delim(std::move(delim))
    {
    }

    ~Split() = default;

    void split(T &cont) const
    {
        size_t pos = 0;
        size_t beg;

        while ((beg = _str.find_first_not_of(_delim, pos)) != std::string::npos) {
            pos = _str.find_first_of(_delim, beg + 1);
            cont.push_back(_str.substr(beg, pos - beg));
        }
    }

    private:
    std::string _str;

    std::string _delim;
};

#endif //ARCADE_ADISPLAY_HPP