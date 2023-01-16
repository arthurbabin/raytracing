/**
 * @file main.cpp
 * @author Teddy ALEXANDRE et Arthur BABIN
 * @brief Ecriture du fichier main
 * @date Décembre 2022
 */ 

#include "scene.h"
#include "cubequad.h"
#include "sphere.h"
#include "camera.h"
#include "ray3f.h"
#include "vector3f.h"
#include "sdl.h"
#include "material.h"
#include <vector>
#include <iostream>
#include <cmath>

const int WIDTH = 853;
const int HEIGHT = 853;

int main() {
    // Initialisation des matériaux
    Material rouge = Material(255,10,10,0.5);
    Material vert = Material(30,255,30,0);
    Material bleu = Material(30,30,255,0.8);
    Material jaune = Material(255,255,30,0.8);
    Material violet = Material(255,20,255,0.5);
    Material cyan = Material(20,255,255,0);
    Material blanc = Material(255,255,255,0);
    Material noir = Material(0,0,0,0);
    Material gris = Material(70,70,70,0);
    Material brillant = Material(255,255,255,1);

    // Les rectangles délimitant la scène / boîte
    CubeQuad walls(Vector3f(0,500,0), Vector3f(1000,500,500), gris);

    // Initialisation de la caméra 
    const Vector3f& camCenter = Vector3f(100,600,-400);
    const Vector3f& camDirection = Vector3f(0,0,200);
    const Vector3f& camUp = Vector3f(0,1,0);
    Camera cam = Camera(camCenter, camDirection, camUp);
    
    // Initialisation de la source de lumière (dirigée vers le bas)
    const Vector3f& sourceOrigin = Vector3f(100,500,0);
    const Vector3f& sourceDirection = Vector3f(0,1,0);
    Ray3f source = Ray3f(sourceOrigin, sourceDirection);

    // Initialisation de la liste des objets
    std::vector<Shape*> shapes;
    Sphere sph(Vector3f(50,400,150),100,rouge);     // Sphère en rouge
    CubeQuad cube1(Vector3f(700,700,40),Vector3f(100),bleu);   // Cube en bleu
    CubeQuad cube2(Vector3f(300,1000,300),Vector3f(20,600,20),vert);   // Cube en bleu
    float theta = 0.75;
    std::array<Vector3f, 3> rotatedBasis = {
        Vector3f(std::cos(theta),std::sin(theta),0),
        Vector3f(-std::sin(theta),std::cos(theta),0),
        Vector3f(0,0,1)
    };
    CubeQuad cube3(Vector3f(400,700,40),Vector3f(100),jaune,rotatedBasis);

    shapes.push_back(&sph);
    shapes.push_back(&cube1);
    shapes.push_back(&cube2);
    shapes.push_back(&cube3);
    shapes.push_back(&walls);

    // Initialisation de la scène
    Scene sc = Scene(cam,shapes,source);

    // Fonction principale : rendu de la scène
    sc.render(WIDTH,HEIGHT);
    return 0;
}

