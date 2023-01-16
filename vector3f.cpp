/**
 * @file vector3f.cpp
 * @author Arthur BABIN
 * @brief Implémentation de la classe Vector3f
 * @date Décembre 2022
 */

#include "vector3f.h"
#include <stdexcept>


Vector3f Vector3f::operator+(const Vector3f& other) const {
    return Vector3f(x + other.x, y + other.y, z + other.z);
}


Vector3f Vector3f::operator-(const Vector3f& other) const {
    return Vector3f(x - other.x, y - other.y, z - other.z);
}


Vector3f Vector3f::operator*(float scalar) const {
    return Vector3f(x * scalar, y * scalar, z * scalar);
}


Vector3f Vector3f::operator/(float scalar) const {
    return Vector3f(x / scalar, y / scalar, z / scalar);
}

float Vector3f::operator[](std::size_t index) const {
    switch (index) {
      case 0:
        return x;
      case 1:
        return y;
      case 2:
        return z;
      default:
        throw std::out_of_range("Index out of range");
    }
}

// Produit scalaire
float Vector3f::dot(Vector3f v) const {
    return this->x*v.x + this->y*v.y + this->z*v.z;
}

float Vector3f::norm() const {
    return std::sqrt(x*x + y*y + z*z);
}


float Vector3f::squaredNorm() const {
    return x*x + y*y + z*z;
}


void Vector3f::normalize() {
    float n = norm();
    if (n > 0) {
        x /= n;
        y /= n;
        z /= n;
    }
}


Vector3f Vector3f::normalized() const {
    Vector3f v(*this);
    v.normalize();
    return v;
}

// Calcul du rayon réfléchi
Vector3f Vector3f::reflect(const Vector3f& n) const {
    Vector3f vNorm = this->normalized();
    Vector3f nNorm = n.normalized();
    return vNorm - nNorm*2*vNorm.dot(nNorm);
} 

// Produit vectoriel
Vector3f Vector3f::cross(const Vector3f& other) const {
    float cX = y * other.z - z * other.y;
    float cY = z * other.x - x * other.z;
    float cZ = x * other.y - y * other.x;
    return Vector3f(cX, cY, cZ);
}
