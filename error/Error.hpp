/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Error.hpp.h
*/
#ifndef ARCADE_ERROR_HPP
#define ARCADE_ERROR_HPP

#include <exception>
#include <iostream>

namespace err {
    class ArcadeError : public std::exception {
        public:
        explicit ArcadeError (std::string message, std::string component = "Unknown");

        ~ArcadeError () noexcept override = default;

        [[nodiscard]] std::string const &where() const;

        [[nodiscard]] const char *what() const noexcept final;

        protected:
        std::string _message;

        std::string _component;
    };

    class GraphicError : public ArcadeError {
        public:
        explicit GraphicError(std::string const &message, std::string const &component = "GraphicEncapsulation");

        ~GraphicError() noexcept override = default;
    };

    class NcursesError : public GraphicError {
        public:
        explicit NcursesError(std::string const &message, std::string const &component = "NcursesEncapsulation");

        ~NcursesError() noexcept override = default;
    };

    class Sdl2Error : public GraphicError {
        public:
        explicit Sdl2Error(std::string const &message, std::string const &component = "Sdl2Encapsulation");

        ~Sdl2Error() noexcept override = default;
    };
    
    class SfmlError : public GraphicError {
        public:
        explicit SfmlError(std::string const &message, std::string const &component = "SfmlEncapsulation");

        ~SfmlError() noexcept override = default;
    };

    class ObjectError : public ArcadeError {
        public:
        explicit ObjectError(std::string const &message, std::string const &component = "Object");

        ~ObjectError() noexcept override = default;
    };

    class TextError : public ObjectError {
        public:
        explicit TextError(std::string const &message, std::string const &component = "Object Text");

        ~TextError() noexcept override = default;
    };

    class GameObjectError : public ArcadeError {
        public:
        explicit GameObjectError(std::string const &message, std::string const &component = "Game Object");

        ~GameObjectError() noexcept override = default;
    };

    class LoaderException : public ArcadeError {
        public:
        explicit LoaderException(std::string const &message, std::string const &component = "Loader Ldl");

        ~LoaderException() noexcept override = default;

    };
}

#endif //ARCADE_ERROR_HPP
