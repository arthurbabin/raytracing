/**
 * @file camera.h
 * @author Teddy ALEXANDRE
 * @brief Création de la classe Camera
 * @date Décembre 2022
 */ 

#ifndef CAMERA_H
#define CAMERA_H

#include "vector3f.h" // Pour les attributs de la classe
#include "ray3f.h"    // Pour la méthode getRay


/**
 * @brief Classe pour la caméra, d'où l'on observe la scène
 * 
 */
class Camera {

    /**
     * @brief attributs de type Vector3f : position et direction
     */
    private:
        Vector3f _position;
        Vector3f _direction; // = orientation avant/arrière
        Vector3f _up; // orientation haut/bas
        Vector3f _right; // orientation gauche/droite
    
    public:
        
        /**
         * @brief Constructeur valué avec 3 paramètres, position, direction, et orientation haut/bas (_right étant calculé avec un produit vectoriel)
         */
        Camera(const Vector3f& position, const Vector3f& direction, const Vector3f& _up);
        
        /**
         * @brief Destructeur de la classe Camera
         */
        ~Camera();

        /**
         * @brief Getter sur la position
         */
        inline const Vector3f& getPos() const {return _position; };

        /**
         * @brief Getter sur la direction
         */
        inline const Vector3f& getDir() const {return _direction; };

        /**
         * @brief Retourne le rayon issu de la caméra et passant à travers un pixel
         * virtuel de coordonnées u,v
         *
         * @param u
         * @param v
         * @return Ray3f
         */
        Ray3f getRay(float u, float v);
};

#endif
