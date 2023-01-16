/**
 * @file sphere.h
 * @author Arthur BABIN
 * @brief Création de la classe Sphere
 * @date Décembre 2022
 */
#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h" // Pour inclure la définition de la classe Shape
#include <cmath> // Pour sqrt()

/**
 * @brief Classe pour représenter une sphère
 * 
 */
class Sphere : public Shape {
    private:

        /**
         * @brief Le centre de la sphère
         *
         */
        Vector3f center;

        /**
         * @brief Le rayon de la sphère
         *
         */
        float radius;

    public:
        /**
         * @brief Constructeur d'une Sphere avec un centre et un rayon donnés
         *
         * @param center
         * @param radius
         * @param mat
         */
        Sphere(const Vector3f &center, float radius, Material mat)
            : Shape(mat), center(center), radius(radius) {}

        /**
         * @brief Retourne le centre de la Sphere
         *
         * @return const Vector3f&
         */
        inline const Vector3f &getCenter() const { return center; }

        /**
         * @brief Retourne le rayon de la Sphere
         *
         * @return float
         */
        inline float getRadius() const { return radius; }

        /**
         * @brief Méthode qui renvoie -1 si le Ray3f n'intersecte pas la Sphère et
         * la distance entre l'origine du rayon et l'intersection sinon
         * 
         * @param ray 
         * @return float 
         */
        float is_hit(const Ray3f &ray) const override;

        /**
         * @brief Méthode qui calcule le vecteur normal à un point situé sur la sphère 
         * 
         * @param v 
         * @return Vector3f 
         */
        Vector3f getNormal(const Vector3f& v) const override;

        /**
         * @brief Retourne si le point se trouve à l'intérieur de la Sphère ou non 
         *
         * @param vec
         * @return bool 
         */
        bool isInside(const Vector3f &v) const override;

        /**
         * @brief Retourne le Ray3f réfléchi par l'intersection avec la Sphere (on
         * suppose qu'il y a intersection)
         *
         * @param ray
         * @return Ray3f
         */
        Ray3f reflect(const Ray3f &ray) const override;
};
#endif
