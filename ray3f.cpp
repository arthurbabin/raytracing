/**
 * @file ray3f.cpp
 * @author Arthur BABIN
 * @brief Implémentation de la classe Ray3f
 * @date Décembre 2022
 */

#include "ray3f.h"

Vector3f Ray3f::pointAt(float t) const {
    return origin + direction * t;
}