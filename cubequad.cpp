/**
 * @file cubequad.cpp
 * @author Arthur BABIN
 * @brief Implémentation de la classe CubeQuad
 * @date Décembre 2022
 */
#include "cubequad.h"
#include <limits>
#include <cmath>
#include <iostream>

Vector3f CubeQuad::projectVector(const Vector3f& v) const {
    float newX = v.dot(basis[0]) / basis[0].squaredNorm();
    float newY = v.dot(basis[1]) / basis[1].squaredNorm();
    float newZ = v.dot(basis[2]) / basis[2].squaredNorm();
    return Vector3f(newX,newY,newZ);
}

float CubeQuad::is_hit(const Ray3f& ray) const {
    // Projection du rayon sur la base de l'OBB (oriented bounding box)
    Vector3f ray_origin = this->projectVector(ray.getOrigin());
    Vector3f ray_direction = this->projectVector(ray.getDirection()).normalized();

    // Calcul de l'intervalle de validité du rayon
    float tmin = 0, tmax = std::numeric_limits<float>::max();

    // Vérification de l'intersection sur chaque axe
    for (int i = 0; i < 3; i++) {
      // Calcul des limites de l'OBB sur l'axe i
      float vmin = this->getCenter()[i] - this->getHalfSize()[i];
      float vmax = this->getCenter()[i] + this->getHalfSize()[i];

      // Calcul du coefficient de proportionnalité du rayon sur l'axe i
      float t1 = (vmin - ray_origin[i]) / ray_direction[i];
      float t2 = (vmax - ray_origin[i]) / ray_direction[i];

      // Mise à jour de l'intervalle de validité
      tmin = std::max(tmin, std::min(t1, t2));
      tmax = std::min(tmax, std::max(t1, t2));
    }

    // Vérification de l'intersection
    if (tmin>tmax) {
        return -1;
    }
    if (tmin>0) {
        return tmin;
    }
    if (tmax>0) {
        return tmax;
    }
    return -1;
}

Vector3f CubeQuad::getNormal(const Vector3f& v) const {
    Vector3f nv= this->projectVector(v);
    Vector3f normal(0);
      
    double epsilon = 1e-2;
    double boxMinX = Vector3f(center - halfSize).getX();
    double boxMinY = Vector3f(center - halfSize).getY();
    double boxMinZ = Vector3f(center - halfSize).getZ();
    double boxMaxX = Vector3f(center + halfSize).getX();
    double boxMaxY = Vector3f(center + halfSize).getY();
    double boxMaxZ = Vector3f(center + halfSize).getZ();

    double cx = std::abs(nv.getX() - boxMinX);
    double fx = std::abs(nv.getX() - boxMaxX);
    double cy = std::abs(nv.getY() - boxMinY);
    double fy = std::abs(nv.getY() - boxMaxY);
    double cz = std::abs(nv.getZ() - boxMinZ);
    double fz = std::abs(nv.getZ() - boxMaxZ);

    if (cx < epsilon) 
        return Vector3f(0) - basis[0];
    else if (fx < epsilon)
        return Vector3f(0) + basis[0];
    else if (cy < epsilon)
        return Vector3f(0) - basis[1];
    else if (fy < epsilon)
        return Vector3f(0) + basis[1];
    else if (cz < epsilon)
        return Vector3f(0) - basis[2];
    else if (fz < epsilon)
        return Vector3f(0) + basis[2];
    return Vector3f(0);
}

Ray3f CubeQuad::reflect(const Ray3f& ray) const {
    // Calcul de la position de l'intersection sur le rayon
    float t = this->is_hit(ray);

    // Calcul du point d'intersection (= origine du rayon réfléchi)
    Vector3f intersection = ray.pointAt(t);

    // Calcul du vecteur normal au CubeQuad en le point d'intersection
    Vector3f normal = getNormal(intersection);

    // Calcul de la direction du rayon réfléchi
    Vector3f reflectedDirection = ray.getDirection().reflect(normal);

    return Ray3f(intersection,reflectedDirection);
}

bool CubeQuad::isInside(const Vector3f &v) const {
    Vector3f toCenter = this->projectVector(v-center);
    for (int i = 0; i < 3; i++) {
        if (std::abs(toCenter[i])>std::abs(halfSize[i])){
            return false;
        }
    }
    return true;
}
