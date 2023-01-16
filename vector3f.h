/**
 * @file vector3f.h
 * @author Arthur BABIN
 * @brief Création de la classe Vector3f (vecteur 3D de float)
 * @date Décembre 2022
 */
#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cmath> // Pour utiliser sqrt()
#include <array> // Pour la base de Vector3f

/**
 * @brief Classe pour représenter un vecteur de flottants dans l'espace
 * 
 */
class Vector3f {

    private:
        /**
         * @brief Composantes x,y,z du vecteur
         * 
         */
        float x, y, z;

    public:
        /**
         * @brief Construit un Vector3f
         * 
         */
        Vector3f() : x(0), y(0), z(0) {}

        /**
         * @brief Construit un Vector3f à coordonnées égales
         * 
         * @param s
         */
        Vector3f(float s) : x(s), y(s), z(s) {}

        /**
         * @brief Construit un Vector3f
         * 
         * @param x 
         * @param y 
         * @param z 
         */
        Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

        /**
         * @brief Retourne la coordonnée x
         * 
         * @return float 
         */
        inline float getX() const { return x; }

        /**
         * @brief Retourne la coordonnée y
         * 
         * @return float 
         */
        inline float getY() const { return y; }

        /**
         * @brief Retourne la coordonnée z
         * 
         * @return float 
         */
        inline float getZ() const { return z; }


        /**
         * @brief Opérateur d'addition de vecteurs
         * 
         * @param other le vecteur à additionner
         * @return Vector3f 
         */
        Vector3f operator+(const Vector3f &other) const;

        /**
         * @brief Opérateur de soustraction de vecteurs
         * 
         * @param other le vecteur à soustraire
         * @return Vector3f 
         */
        Vector3f operator-(const Vector3f &other) const;

        /**
         * @brief Opérateur de multiplication d'un vecteur par un scalaire
         * 
         * @param scalar 
         * @return Vector3f 
         */
        Vector3f operator*(float scalar) const;

        /**
         * @brief Opérateur de division d'un vecteur par un scalaire
         * 
         * @param scalar 
         * @return Vector3f 
         */
        Vector3f operator/(float scalar) const;

        /**
         * @brief Accède à une coordonnée 
         * 
         * @param index 
         * @return float 
         */
        float operator[](std::size_t index) const;

        /**
         * @brief Calcule le produit scalaire avec un vecteur
         * 
         * @param v 
         * @return float 
         */
        float dot(Vector3f v) const;

        /**
         * @brief Calcule la norme du vecteur
         * 
         * @return float 
         */
        float norm() const;

        /**
         * @brief Calcule la norme du vecteur au carré
         * 
         * @return float 
         */
        float squaredNorm() const;

        /**
         * @brief Normalise le vecteur
         * 
         */
        void normalize();

        /**
         * @brief Renvoie le vecteur normalisé
         * 
         * @return Vector3f 
         */
        Vector3f normalized() const;

        /**
         * @brief Renvoie le produit vectoriel avec un autre Vector3f 
         * 
         * @return Vector3f 
         */
        Vector3f cross(const Vector3f& other) const;

        /**
         * @brief Calcule la direction réfléchie à partir de sa 
         * de la normale au point d'intersection 
         * 
         * @param n direction de la normale au point d'intersection
         * @return Vector3f 
         */
        Vector3f reflect(const Vector3f& n) const;

        /**
         * @brief Retourne la base canonique de Vector3f
         * 
         * @return std::array<Vector3f, 3> 
         */
        static std::array<Vector3f, 3> basis() {
            std::array<Vector3f, 3> bas = {Vector3f(1,0,0),Vector3f(0,1,0),Vector3f(0,0,1)};
            return bas;
        } 
};

#endif
