/**
 * @file scene.cpp
 * @author Teddy ALEXANDRE
 * @brief Implémentation de la classe Scene
 * @date Décembre 2022
 */

#include "scene.h"
#include "sdl.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

const float VIRTUAL_PIXEL_SIZE = 1.;
const int NB_RECURSIONS_MAX = 1;


/**
 * @brief Détermine l'objet le plus proche de la caméra en passant par le pixel courant
 * 
 * @param rayon le rayon depuis la caméra vers le pixel courant
 * @param objets la liste des objets de la scène
 * @param camera la caméra d'où l'on regarde la scène
 * @return l'indice dans le tableau dynamique de l'objet le plus proche de la caméra
 */
int plusProche(const Ray3f& rayon, std::vector<Shape*> objets, const Camera& camera) {
    int indexPlusProche = -1;
    int nbObjets = objets.size();
    float distMin = std::numeric_limits<float>::max();
    for (int k = 0; k < nbObjets; k++) {
        // Le t qui correspond à l'intersection entre la Shape (Cube ou Sphere) et le rayon depuis la caméra
        float t = objets[k]->is_hit(rayon);
        if (t>0) { 
            Vector3f pointIntersectionCur = rayon.pointAt(t); // Point d'intersection entre la shape et le rayon depuis la caméra
            float dist = (camera.getPos() - pointIntersectionCur).norm();
            if (dist < distMin) {
            // Si le point courant est plus proche que celui enregistré précédemment, on l'enregistre à son tour
                distMin = dist;
                indexPlusProche = k;
            }
        }
    }
    return indexPlusProche;
}

/**
 * @brief retourne la couleur ambiante de l'objet
 *
 * @param s la shape correspondant à l'objet
 * @return Material
 */
Material getAmbiantColor(const Shape& s){
    Material ambiantColor = s.getMat()*0.2;
    ambiantColor.setShininess(0);
    return ambiantColor;
}

/**
 * @brief retourne la somme de la couleur diffuse et de la couleur spéculaire sur le point
 * d'intersection (Phong Model)
 *
 * @param s la shape correspondant à l'objet où se situe le point d'intersection
 * @param camera la caméra
 * @param source la source de lumière
 * @param intersection le point d'intersection
 * @return Material
 */
Material getDiffuseSpecularColor(const Shape& closestObject, const Camera& camera, const Ray3f& source, const Vector3f& intersection){
    //Calcul de la direction de la normale (vers l'intérieur -1 ou vers l'extérieur +1)
    float normalDir = (closestObject.isInside(camera.getPos())) ? -1 : 1;

    //Calcul de la normale
    Vector3f normal = closestObject.getNormal(intersection)*normalDir;

    //Calcul du produit scalaire entre la normale et le rayon intersection -> source
    Vector3f dirVersSource = source.getOrigin() - intersection;
    float dot = normal.dot(dirVersSource.normalized());

    //Calcul de la couleur diffuse et de la couleur spéculaire
    if (dot>0) {
        float specularCoef=std::pow(dot,closestObject.getMat().getShininess())*0.1;
        Material diffuseColor = closestObject.getMat()*dot;
        Material specularColor = closestObject.getMat()*specularCoef;
        return specularColor + diffuseColor;
    }
    return Material(0,0,0,0);
}

/**
 * @brief Effectue le tracé de rayon, et renvoie la couleur finale du pixel
 * 
 * @param rayon le rayon depuis la caméra vers le pixel courant
 * @param objets la liste des objets de la scène
 * @param camera la caméra d'où l'on regarde la scène
 * @param source la source de lumière
 * @param niveauRecursion indique la profondeur de récursion dans laquelle on est
 * @return la couleur utilisée pour colorier le pixel virtuel courant
 */
Material lanceRayon(const Ray3f& rayon, std::vector<Shape*> objets, const Camera& camera, const Ray3f& source, int niveauRecursion) {
    // Si on a excédé le niveau de récursion maximal, on renvoie la couleur de fond (noir complet)
    if (niveauRecursion > NB_RECURSIONS_MAX)
        return Material(0,0,0,0);
    
    // Sinon :
    // 2bi) Détermination de l'ensemble des objets qui passent par le rayon
    // et 2bii) détermination de l'objet le plus proche de la caméra
    int nbObjets = objets.size();
    int indexPlusProche = plusProche(rayon, objets, camera); 

    // Calcul de la couleur finale

    if (indexPlusProche == -1) // Si aucun objet n'est frappé par le rayon, on renvoie la couleur de fond
        return Material(0,0,0,0);
    
    // 2biii) Si le rayon parvient à frapper un objet, et si cet objet n'est pas mat (shininess > 0), on suit son rayon réfléchi
    Material colorsReflect(0,0,0,0);
    if (objets[indexPlusProche]->getMat().getShininess() > 0)
        // On calcule récursivement la couleur issu du rayon réfléchi en le point d'intersection
        colorsReflect = lanceRayon(objets[indexPlusProche]->reflect(rayon), objets, camera, source, niveauRecursion+1)*objets[indexPlusProche]->getMat().getShininess();
    
    // Sinon, indexPlusProche != -1, et c'est alors un indice valide
    Vector3f pointIntersection = rayon.pointAt(objets[indexPlusProche]->is_hit(rayon));
    // 2c) Calcul de la couleur : on teste déjà si le point est éclairé ou non
    Vector3f dirVersSource = source.getOrigin() - pointIntersection;
    Ray3f rayonVersSource = Ray3f(pointIntersection + dirVersSource*0.001, dirVersSource.normalized()); // Rayon dirigé vers la source de lumière
    bool estEclaire = true;
    float distVersSource = (source.getOrigin() - pointIntersection).norm();
    int k = 0;
    // On teste si ce rayon intersecte un objet ou pas
    while (k < nbObjets && estEclaire) {
        // On regarde si le rayon qui part de l'intersection vers la source intersecte la shape
        float estObstrue = objets[k]->is_hit(rayonVersSource);
        // S'il y a intersection avant la source alors le point n'est pas éclairé
        if (estObstrue > 0 && (estObstrue < distVersSource))
            estEclaire = false;
        k++;
    }

    Material ambiantColor = getAmbiantColor(*objets[indexPlusProche]);

    // Si le pixel est éclairé par un objet, on l'affiche avec les propriétés de l'objet le plus proche (le Material associé)
    if (estEclaire) {
        Material diffAndSpecColor = getDiffuseSpecularColor(*objets[indexPlusProche],camera,source,pointIntersection);
        return ambiantColor + diffAndSpecColor + colorsReflect;
    }
    return ambiantColor;
}

/**
 * @brief On applique l'algorithme fourni dans l'énoncé
 */
void Scene::render(int width, int height) {
    // Mise en place de la fenêtre SDL et du rendu
    Sdl sdl = Sdl();
    sdl.init(width, height, "raytracing.png");
    
    // Dimensions des pixels virtuels (les cases de la grille)
    float px_width = VIRTUAL_PIXEL_SIZE;
    float px_height = px_width;


    // Etape 2 : Pour chaque pixel de l'image ou point de la grille, qu'on suppose avec z = 0 pour
    // tous les pixels
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float i_px = i*px_width;
            float j_px = j*px_height;

            // 2a) : On calcule le rayon qui part de la caméra vers le pixel virtuel
            Ray3f rayFromCam = _camera.getRay(i_px-width/2,j_px-height/2);

            // 2b) et 2c) : On détermine les intersections, pour en déduire la couleur finale du pixel virtuel
            Material colors = lanceRayon(rayFromCam, _shapes, _camera, _source, 0);
            sdl.setColor(colors.getR(), colors.getG(), colors.getB(), colors.getShininess());
            sdl.drawPoint(i,j);
        }
    }
    sdl.update();
    sdl.~Sdl();
}
