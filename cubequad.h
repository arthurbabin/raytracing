/**
 * @file cubequad.h
 * @author Arthur BABIN
 * @brief Création de la classe CubeQuad (pour les parrallélépipèdes rectangle
 * et les cubes)
 * @date Décembre 2022
 */

#ifndef CUBEQUAD_H
#define CUBEQUAD_H

#include <array> // Pour la base des CubeQuad 
#include "shape.h" // Pour inclure la définition de la classe Shape
#include "vector3f.h"
#include "ray3f.h"

/**
 * @brief Classe pour représenter les parallélépipèdes rectangle et les cubes
 *
 */
class CubeQuad : public Shape {

    private:
        /**
         * @brief Centre du CubeQuad dans l'espace
         * 
         */
        Vector3f center;
        
        /**
         * @brief Moitié de la taille de la boîte sur chaque axe de sa base
         * 
         */
        Vector3f halfSize;

        /**
         * @brief Base du CubeQuad correspondant à un repère dans lequel l'objet est
         * aligné par rapport aux axes
         * 
         */
        std::array<Vector3f, 3> basis;


    public:
        /**
         * @brief Constructeur avec un centre et une moitié de taille qui produit une boîte alignée
         * par rapport aux axes dans la base canonique
         *
         * @param center
         * @param halfSize
         * @param mat
         */
        CubeQuad(const Vector3f &center, const Vector3f &halfSize, Material mat)
            : Shape(mat), center(center), halfSize(halfSize), basis(Vector3f::basis()) {}
        
        /**
         * @brief Constructeur complet (attention basis doit bien correspondre à une base orthonormée)
         * 
         * @param center 
         * @param halfSize 
         * @param mat
         * @param basis 
         */
        CubeQuad(const Vector3f &center, const Vector3f &halfSize, Material mat, const std::array<Vector3f, 3>& basis)
            : Shape(mat), center(center), halfSize(halfSize), basis(basis) {}

        /**
         * @brief Constructeur avec un centre et des dimensions (produit une AABB)
         * 
         * @param origin 
         * @param width
         * @param height 
         * @param depth 
         */
        CubeQuad(const Vector3f &center, float width, float height, float depth, Material mat)
            : CubeQuad(center,Vector3f(width/2,height/2,depth/2), mat) {}

        /**
         * @brief Accesseur du centre du CubeQuad
         *
         * @return const Vector3f&
         */
        inline const Vector3f &getCenter() const {return center;}

        /**
         * @brief Accesseur du halfSize du CubeQuad
         *
         * @return const Vector3f&
         */
        inline const Vector3f &getHalfSize() const {return halfSize;}

        /**
         * @brief Retourne la base du CubeQuad dans laquelle c'est une AABB
         * 
         * @return const std::array<Vector3f, 3>& 
         */
        inline const std::array<Vector3f, 3> &getBasis() const {return basis;}

        /**
         * @brief retourne le projeté du vecteur sur la base du CubeQuad
         * 
         * @param v 
         * @return Vector3f 
         */
        Vector3f projectVector(const Vector3f &v) const;

        /**
         * @brief Méthode qui renvoie -1 si le Ray3f n'intersecte pas le CubeQuad et
         * la distance entre l'origine du rayon et l'intersection sinon
         * 
         * @param ray 
         * @return float 
         */
        float is_hit(const Ray3f &ray) const override;

        /**
         * @brief Méthode qui calcule le vecteur normal à un point situé sur une des faces du cube
         * 
         * @param v 
         * @return Vector3f 
         */
        Vector3f getNormal(const Vector3f& v) const override;

        /**
         * @brief Retourne si le point se trouve à l'intérieur du CubeQuad ou non 
         *
         * @param vec
         * @return bool 
         */
        bool isInside(const Vector3f &v) const override;

        /**
         * @brief Retourne le Ray3f réfléchi par l'intersection avec le CubeQuad (on
         * suppose qu'il y a bien intersection)
         *
         * @param ray
         * @return Ray3f
         */
        Ray3f reflect(const Ray3f &ray) const override;
};

#endif
