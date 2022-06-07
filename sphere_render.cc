#include <iostream>
#include <math.h>

#include "sphere_render.h"

extern SphereRender sphereRender;

extern float camx = 0.0;
extern float camy = -5.0;
extern float camz = 10.0;

extern float posX = 0.0;
extern float posY = 0.0;
extern float posZ = -8.0;

extern float EarthT = 0.0;
extern float a = 3.5;

extern float angle = 0.0f;

void SphereRender::setSphere(Sphere sphere)
{
    this->sphere = sphere;
}

void SphereRender::resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SphereRender::timer(int some)
{

    EarthT += 0.05;
    posX = a * cos(EarthT);

    glLoadIdentity();
    gluLookAt(camx, camy, camz, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
    glutTimerFunc(50, timer, 1);
}

void SphereRender::drawPoints()
{
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i = 0; i < this->sphere.points.size(); i++)
    {
        glVertex3f(this->sphere.points[i][0], this->sphere.points[i][1], this->sphere.points[i][2]);
    }
    glEnd();
}

void SphereRender::drawRegularPoints()
{
    glPointSize(3);
    glBegin(GL_POINTS);
    for (int i = 0; i < this->sphere.regularPoints.size(); i++)
    {
        glVertex3f(this->sphere.regularPoints[i][0], this->sphere.regularPoints[i][1], this->sphere.regularPoints[i][2]);
    }
    glEnd();
}


void SphereRender::display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix(); // sun
    glColor3d(1, 1, 0);
    glTranslated(0, 0, -10);
    glRotated(angle, 1.0f, 1.0f, 1.0f);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();

    // random points
    glPushMatrix();
    glColor3d(1, 0, 0);
    glTranslated(0, 0, -10);
    glRotated(angle, 1.0f, 1.0f, 1.0f);
    sphereRender.drawPoints();
    glPopMatrix();

    glPushMatrix(); // earth
    glColor3d(1, 1, 1);
    glTranslated(posX, posY, posZ);
    glRotated(angle, 1.0f, 1.0f, 1.0f);
    glutSolidSphere(1, 30, 30);
    glPopMatrix();

    // regular points
    glPushMatrix();
    glColor3d(0, 0, 1);
    glTranslated(posX, posY, posZ);
    glRotated(angle, 1.0f, 1.0f, 1.0f);
    sphereRender.drawRegularPoints();
    glPopMatrix();


    angle += 0.5f;

    glutSwapBuffers();
}

void SphereRender::NormalKeyHandler(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
    }
}

void SphereRender::MouseHandler(int button, int state, int x, int y)
{
    if ((button == 3) || (button == 4))
    {
        if (button == 3 && state == GLUT_UP)
        {
            camz -= 1;
        }
        else if (button == 4 && state == GLUT_UP)
        {
            camz += 1;
        }
    }
}

void SphereRender::render(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Random sampled points");
    // glutFullScreen();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutTimerFunc(50, timer, 1);
    glutMouseFunc(MouseHandler);
    glutKeyboardFunc(NormalKeyHandler);
    glutIdleFunc(display);

    glutMainLoop();
}
