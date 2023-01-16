/**
 * @file scene.h
 * @author Teddy ALEXANDRE
 * @brief Création de la classe Scene
 * @date Décembre 2022
 */ 

#ifndef SCENE_H
#define SCENE_H

#include "camera.h"   // Pour les attributs
#include "shape.h"    // Idem
#include "ray3f.h"    // Idem
#include "sdl.h"      // Pour la méthode render
#include <string>
#include <vector>


/**
 * @brief Classe pour représenter la scène, avec la caméra, les différents objets (Shapes) et la source de lumière
 * 
 */
class Scene {

    /**
     * @brief Trois attributs de classe, une méthode pour la classe Scene
     */
    
    private:
        Camera _camera;
        std::vector<Shape*> _shapes;
        Ray3f _source;
    
    public:
        /**
         * Constructeur valué
         */
        Scene(const Camera& camera, std::vector<Shape*> shapes, const Ray3f& source) : _camera(camera), _shapes(shapes), _source(source) {}

        /**
         * Destructeur de la classe Scene
         */
        ~Scene() {}

        /**
         * @brief : Méthode qui effectue l'affichage de la Scene avec les méthodes de la classe SDL
         * @param width : largeur de la fenêtre
         * @param height : hauteur de la fenêtre
         */
        void render(int width, int height);

        /**
         * Getters sur la caméra et la source
         */
        inline const Camera& getCamera() const {return _camera;};

        inline const Ray3f& getSource() const {return _source;};
};

#endif
