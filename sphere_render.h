#ifndef COMMON_H
#define COMMON_H

#include <GL/glut.h>

#include "sphere.h"

const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.0f, 1.0f, 0.3f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {0.5f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {80.0f};

extern float camx;
extern float camy;
extern float camz;
extern float angle;

class SphereRender
{
public:
    SphereRender(){};
    SphereRender(Sphere sphere)
    {
        this->sphere = sphere;
    };

    Sphere sphere;

    void setSphere(Sphere sphere);

    void drawPoints();
    void drawRegularPoints();
    static void display();
    static void resize(int width, int height);
    static void timer(int some);
    static void MouseHandler(int button, int state, int x, int y);
    static void NormalKeyHandler(unsigned char key, int x, int y);

    void render(int argc, char *argv[]);
};

extern SphereRender sphereRender;

#endif