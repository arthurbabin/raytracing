/**
 * @file material.h
 * @author Teddy ALEXANDRE
 * @brief Création de la classe Material
 * @date Décembre 2022
 */ 

#ifndef MATERIAL_H
#define MATERIAL_H


/**
 * @brief Classe pour obtenir les couleurs (R,G,B) et la luminosité d'une Shape
 * 
 */
class Material {
    private:

        /**
         * @brief Quatre attributs, trois pour composer la couleur,
         * un pour le coefficient de luminosité
         */
        float _r, _g, _b;
        float _shininess;

    public:
        
        /**
         * @brief Constructeur valué
         */
        Material(float r, float g, float b, float shininess);

        /**
         * @brief Surcharge d'opérateur + pour les Material
         * 
         * @param other
         * @return Material 
         */
        Material operator+(const Material& other);

        /**
         * @brief Surcharge d'opérateur * pour les Material, à droite
         * 
         * @param k 
         * @return Material 
         */
        Material operator*(float k);

        /**
         * @brief Destructeur
         */
        ~Material();

        /**
         * @brief Rectifie les valeurs du Material selon les limites autorisées
         * pour chaque attribut
         */
        void correctRange();

        /**
         * @brief Getters sur les couleurs et la luminosité
         */
        inline float getR() const {return _r;};
        inline float getB() const {return _b;};
        inline float getG() const {return _g;};
        inline float getShininess() const {return _shininess;};

        /**
         * @brief Setters sur les couleurs et la luminosité
         */
        inline void setR(float r) {_r=r;};
        inline void setB(float b) {_b=b;};
        inline void setG(float g) {_g=g;};
        inline void setShininess(float s) {_shininess=s;};
};

#endif
