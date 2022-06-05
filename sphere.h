#ifndef COMMON2_H
#define COMMON2_H

#include <vector>

using std::vector;

typedef vector<vector<float>> Points;
typedef vector<float> Point;

const int RADIUS = 1;

class Sphere
{
public:
    Sphere() {}
    Sphere(int n_threads, int n_points)
    {
        this->radius = RADIUS;
        this->n_points = n_points;
        this->n_threads = n_threads;
        this->points = Points(this->n_points, Point(3));
        this->regularPoints = Points(this->n_points, Point(3));
    }

    float radius;
    int n_points;
    int n_threads;
    Points points;
    Points regularPoints;

    void multiThreadGenerateRandomPoints();
    void multiThreadGenerateRegularPoints();

private:
    static void generateRandomPoints(Sphere &);
    static void generateRegularPoints(Sphere &);
};

#endif
