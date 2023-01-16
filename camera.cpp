/**
 * @file camera.cpp
 * @author Teddy ALEXANDRE
 * @brief Implémentation de la classe Camera
 * @date Décembre 2022
 */

#include "camera.h"

Camera::Camera(const Vector3f& position, const Vector3f& direction, const Vector3f& up) {
    _position = position;
    _direction = direction;
    _up = up.normalized();
    _right = _direction.cross(_up).normalized();
}

Camera::~Camera() {
}

Ray3f Camera::getRay(float u, float v) {
    Vector3f point = _position + _direction + _right*u + _up*v;
    return Ray3f(_position, (point - _position).normalized());
}
