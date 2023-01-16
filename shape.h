/**
 * @file shape.h
 * @author Arthur BABIN
 * @brief Création de la classe Shape
 * @date Décembre 2022
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "ray3f.h" // Pour inclure la définition de la classe Ray3f
#include "material.h" // Pour donner une texture aux Shapes

/**
 * @brief Classe abstraite pour représenter un objet
 * 
 */
class Shape {
    private:
        /**
         * @brief Attribut pour la texture de la Shape
         * 
         */
        Material mat;

    public:
        /**
         * @brief Constructeur par défaut de Shape
         * @param mat Material associé à la Shape
         */
        Shape(Material mat) : mat(mat) {}

        /**
         * @brief Destructeur virtuel de Shape
         *
         */
        virtual ~Shape() {}

        /**
         * @brief Méthode qui renvoie -1 si le Ray3f n'intersecte pas la Shape et
         * la distance entre l'origine du rayon et l'intersection sinon
         * 
         * @param ray 
         * @return float 
         */
        virtual float is_hit(const Ray3f &ray) const = 0;

        /**
         * @brief Méthode qui calcule le Ray3f réfléchi à partir de l'intersection
         * avec la Shape
         *
         * @param ray
         * @return Ray3f
         */
        virtual Ray3f reflect(const Ray3f &ray) const = 0;

        /**
         * @brief Retourne la normale à la surface de la shape au point vec
         * supposé appartenir à la surface
         *
         * @param vec
         * @return Vector3f
         */
        virtual Vector3f getNormal(const Vector3f &vec) const = 0;

        /**
         * @brief Retourne si le point se trouve à l'intérieur de la shape ou non 
         *
         * @param vec
         * @return bool 
         */
        virtual bool isInside(const Vector3f &vec) const = 0;

        /**
         * @brief Retourne la texture de l'objet
         * 
         * @return Material 
         */
        inline Material getMat() const {return mat;}
};
#endif
