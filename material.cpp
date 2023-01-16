/**
 * @file material.cpp
 * @author Teddy ALEXANDRE
 * @brief Implémentatiob de la classe Camera
 * @date Décembre 2022
 */

#include "material.h"
#include <cmath>
#include <algorithm>

Material::Material(float r, float g, float b, float shininess) {
    _r = r;
    _g = g;
    _b = b;
    _shininess = shininess;
    this->correctRange();
}

Material Material::operator+(const Material& other) {
    Material m = Material(_r + other._r, _g + other._g, _b + other._b, _shininess + other._shininess);
    m.correctRange();
    return m;
}

Material Material::operator*(float k) {
    Material m = Material(_r*k, _g*k, _b*k, _shininess);
    m.correctRange();
    return m;
}

void Material::correctRange(){
    _r = std::min(std::max(_r,(float) 0),(float) 255);
    _g = std::min(std::max(_g,(float) 0),(float) 255);
    _b = std::min(std::max(_b,(float) 0),(float) 255);
    _shininess = std::min(std::max(_shininess,(float) 0),(float) 1);
}

Material::~Material() {
}
