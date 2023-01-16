/**
 * @file sdl.cpp
 * @author Teddy ALEXANDRE
 * @brief Implémentation de la classe SDL
 * @date Décembre 2022
 */ 

#include "sdl.h"
#include <stdexcept>

Sdl::~Sdl() {
    if (_renderer != nullptr) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }

    if (_window != nullptr) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    SDL_Quit();
}

void Sdl::init(int width, int height, std::string filename) {
    // On teste si la SDL s'est bien initialisée avant toute opération
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("L'initialisation SDL a échoué");
    }

    // Création de la fenêtre de travail
    _window = SDL_CreateWindow(filename.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (_window == nullptr) {
        throw std::runtime_error("La création de la fenêtre SDL a échoué");
    }

    // Création du renderer dans lequel on dessine
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == nullptr) {
        throw std::runtime_error("La création du rendu SDL a échoué");
    }
}

void Sdl::setColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(_renderer, r, g, b, a);
}

void Sdl::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(_renderer, x, y);
}

void Sdl::update() {
    SDL_RenderPresent(_renderer);
    SDL_Delay(5000); // on attend 5s
}

void Sdl::clear() {
    setColor(0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
}
