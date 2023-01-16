/**
 * @file sphere.cpp
 * @author Arthur BABIN
 * @brief Implémentation de la classe Sphere
 * @date Décembre 2022
 */

#include "sphere.h"
#include <iostream>

float Sphere::is_hit(const Ray3f& ray) const {
    // Calcule le vecteur d'origine du rayon à la sphère
    Vector3f oc = ray.getOrigin() - center;

    // Calcule les coefficients de l'équation quadratique qui décrit l'intersection entre le rayon et la sphère
    float a = ray.getDirection().squaredNorm();
    float b = 2 * oc.dot(ray.getDirection());
    float c = oc.squaredNorm() - radius*radius;

    // Calcule le discriminant de l'équation quadratique
    float discriminant = b*b - 4*a*c;

    // Renvoie true si le discriminant est positif, false sinon (c'est-à-dire si le rayon intersecte la sphère)
    if (discriminant > 0){
        // deux solutions
        float t1 = (-b + std::sqrt(discriminant)) / (2*a);
        float t2 = (-b - std::sqrt(discriminant)) / (2*a);
        if (t1<0) {
            return (t2<0) ? -1 : t2;
        } else {
            if (t2 < 0) {
                return t1;
            } else {
                return (t1<t2) ? t1 : t2;
            }
        }
    } else {
        return -1;
    };
}

Ray3f Sphere::reflect(const Ray3f& ray) const {
    // Calcul de la position de l'intersection sur le rayon
    float t = this->is_hit(ray);

    // Calcul du point d'intersection (= origine du rayon réfléchi)
    Vector3f intersection = ray.pointAt(t);

    // Calcul de la normale (ie le vecteur partant du centre vers le point d'intersection)
    Vector3f normal = intersection - center;

    // Calcul de la direction du rayon réfléchi
    Vector3f reflectedDirection = ray.getDirection().reflect(normal);

    return Ray3f(intersection,reflectedDirection);
}

Vector3f Sphere::getNormal(const Vector3f& v) const {
    return (v-center).normalized();
}

bool Sphere::isInside(const Vector3f &v) const {
    return (v-center).norm()<radius;
}
