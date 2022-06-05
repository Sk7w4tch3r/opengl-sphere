#include <cstdlib>
#include <GL/glut.h>
#include <iostream>

#include "sphere.h"
#include "sphere_render.h"

// GLUT who makes me go global must be punushed in hell.
SphereRender sphereRender = SphereRender();

int main(int argc, char *argv[])
{
    int n_points = argc > 1 ? std::atoi(argv[1]) : 1000;
    int n_threads = argc > 2 ? std::atoi(argv[2]) : 4;

    Sphere sphere(n_threads, n_points);
    sphere.multiThreadGenerateRandomPoints();
    sphere.multiThreadGenerateRegularPoints();

    sphereRender.setSphere(sphere);

    sphereRender.render(argc, argv);

    return EXIT_SUCCESS;
}
