# Projet C++ Lancer de rayons

![](./Rapport Projet/rendu_modele_phong.png "Rendu")

## Diagramme UML

On présente les diverses classes :

- Vector3f : c’est un vecteur 3D de float.
- Ray3f : un rayon avec une origine et une direction
- Camera : la caméra ou œuil d’où on regarde la scène.
- Material : la couleur (uniforme) et un coefficient de luminosité entre 0 et 1 (0 signifie pas de réflection (objet mat) et 1 signifie que le rayon est entièrement réfléchi (un miroir)).
- Shape : classe abstraite. La méthode is_hit teste si le rayon intersecte l’objet et la méthode reflect renvoie le rayon réfléchi.
- Cube/Quad : un cube ou un rectangle, défini par une origine (le centre) et la taille.
- Sphere : une sphère définie par une origine et un rayon.
- Scene : la scène qui comprend la caméra et les objets et la source de lumière. La méthode render définit la taille de la grille (donc de l’image) ainsi que le nom du fichier dans lequel on sauve l’image.
- Sdl : classe facilitant l'usage de la bibliothèque SDL

Les constructeurs, destructeurs, getters et surcharges d'opérateurs sont omises pour plus de lisibilité.

```mermaid
classDiagram
	direction RL
    Shape <|-- CubeQuad
    Shape <|-- Sphere
    <<Interface>> Shape
    class Vector3f{
        float x,y,z
        float dot(Vector3f v) const
        float norm() const
        float squaredNorm() const
        void normalize()
        Vector3f normalized() const
        Vector3f cross(const Vector3f& other) const
        Vector3f reflect(const Vector3f& n) const
        static std::array<Vector3f, 3> basis()
    }
    class Ray3f{
	      Vector3f origin
				Vector3f destination
        Vector3f pointAt(float t)
    }
    class Camera{
        Vector3f position
				Vector3f direction
        Vector3f up
        Vector3f right
        Ray3f getRay(float u, float v)
    }

    class Material{
				float r,g,b
				float shininess
    }
    class Shape{
				Material matter
        float is_hit(const Ray3f& ray) const = 0
				Ray3f reflect(const Ray3f& ray) const = 0
        Vector3f getNormal(const Vector3f &vec) const = 0
        bool isInside(const Vector3f &vec) const = 0
    }
    class CubeQuad{
        Vector3f center
				Vector3f halfSize
        std::array<Vector3f, 3> basis
        Vector3f projectVector(const Vector3f &v) const
        float is_hit(Ray3f ray) const
        Vector3f getNormal(const Vector3f& v) const
        bool isInside(const Vector3f &v) const
        Ray3f reflect(const Ray3f& ray) 
    }
    class Sphere {
        Vector3f center
				Vector3f radius
        float is_hit(const Ray3f& ray) const
        Vector3f getNormal(const Vector3f& v) const
        bool isInside(const Vector3f &v) const
        Ray3f reflect(const Ray3f& ray)
    }
    class Scene {
				Camera camera
				Vector~Shape*~ shapes
				render(int width, int height)
    }
    class Sdl {
            SDL_Window* _window
            SDL_Renderer* _renderer
            void init(int width, int height, std::string filename)
            void setColor(int r, int g, int b, int a)
            void drawPoint(int x, int y)
            void update()
            void clear()
    }
```
