/**
 * @file ray3f.h
 * @author Arthur BABIN
 * @brief Création de la classe Ray3f (rayon dans un espace à 3 dimensions de
 * flottants)
 * @date Décembre 2022
 */
#ifndef RAY3F_H
#define RAY3F_H

#include "vector3f.h" // Pour inclure la définition de la classe Vector3f

/**
 * @brief Classe pour représenter un rayon optique
 * 
 */
class Ray3f {

    private:
        /**
         * @brief Origine et direction du rayon
         *
         */
        Vector3f origin, direction;

    public:
        /**
         * @brief Constructeur par défaut de Ray3f
         *
         */
        Ray3f() : origin(0, 0, 0), direction(0, 0, 0) {}

        /**
         * @brief Constructeur avec une origine et une direction données pour Ray3f
         *
         * @param origin
         * @param direction
         */
        Ray3f(const Vector3f &origin, const Vector3f &direction)
            : origin(origin), direction(direction) {}

        /**
         * @brief Retourne l'origine du Ray3f
         *
         * @return const Vector3f&
         */
        inline const Vector3f &getOrigin() const { return origin; }

        /**
         * @brief Retourne la direction du Ray3f
         *
         * @return const Vector3f&
         */
        inline const Vector3f &getDirection() const { return direction; }

        /**
         * @brief Calcule le point sur le Ray3f à une distance donnée du point
         * d'origine suivant la direction
         *
         * @param t
         * @return Vector3f
         */
        Vector3f pointAt(float t) const;

};

#endif