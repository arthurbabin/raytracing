/**
 * @file sdl.h
 * @author Teddy ALEXANDRE
 * @brief Création de la classe SDL
 * @date Décembre 2022
 */ 

#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>   // Import de la bibliothèque SDL
#include <string>       // Pour le nom du rendu

/**
 * @brief Classe pour utiliser la bibliothèque SDL de façon plus pratique
 * 
 */
class Sdl {
    private:
        /**
         * @brief Deux attributs, un pointeur sur un SDL_Window,
         * un autre sur un SDL_Renderer
         */
        SDL_Window* _window;
        SDL_Renderer* _renderer;

    public:
        /**
         * Constructeur par défaut de la classe SDL
         */
        Sdl() : _window(nullptr), _renderer(nullptr) {}

        /**
         * Destructeur de la classe SDL
         */
        ~Sdl();

        /**
         * @brief Méthode qui initialise une fenêtre SDL avec les paramètres suivants
         * @param width : largeur de la fenêtre
         * @param height : hauteur de la fenêtre
         * @param filename : nom de la fenêtre SDL
         */
        void init(int width, int height, std::string filename);

        /**
         * @brief Remplace la couleur courante avec les paramètres suivants (entiers entre 0 et 255)
         * 
         * @param r rouge
         * @param g vert
         * @param b bleu
         * @param a paramètre d'opacité
         */
        void setColor(int r, int g, int b, int a);

        /**
         * @brief Dessine la couleur courante en le point de coordonnées (x,y)
         * 
         * @param x abscisse du point
         * @param y ordonnée du point
         */
        void drawPoint(int x, int y);

        /**
         * @brief Méthode qui met à jour le rendu obtenu avec les fonctions de la SDL
         */
        void update();

        /**
         * @brief Méthode qui nettoie la fenêtre (donne un noir complet)
         */
        void clear();
};

#endif
