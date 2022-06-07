#include <cstdlib>
#include <random>
#include <iostream>
#include <thread>

#include "sphere.h"

using std::thread;

void Sphere::generateRandomPoints(Sphere &sphere, size_t start, size_t end)
{
    int n = sphere.n_points / sphere.n_threads;
    // int n = sphere.n_points;
    for (int i = 0; i < n && start < end; i++)
    {
        float z = (float)random() / (float)RAND_MAX * 2 * RADIUS - RADIUS;
        float phi = (float)random() / (float)RAND_MAX * 2 * M_PI;
        float x = sqrt(pow(RADIUS, 2) - pow(z, 2)) * cos(phi);
        float y = sqrt(pow(RADIUS, 2) - pow(z, 2)) * sin(phi);

        Point point = {
            x,
            y,
            z};
        sphere.points[start+i] = point;
    }
}

void Sphere::generateRegularPoints(Sphere &sphere, size_t start, size_t end) 
{
  float n = 0;
  float a = 4 * M_PI * pow(RADIUS, 2) / sphere.n_points;
  float d = sqrt(a);
  float M_v = round(M_PI / d);
  float d_v = M_PI / M_v;
  float d_phi = a / d_v;

  size_t i = start;
  for (int m = 0; m < M_v; m++) {
    float v = M_PI * (m + 0.5) / M_v;
    float m_phi = round(2 * M_PI * sin(v) / d_phi);
    for (int n = 0; n < m_phi && i < end; n++) {
      float phi = 2 * M_PI * n / m_phi;
      float x = RADIUS * sin(v) * cos(phi);
      float y = RADIUS * sin(v) * sin(phi);
      float z = RADIUS * cos(v);
      vector < float > point = {
        x,
        y,
        z
      };
      sphere.regularPoints[i] = point;
      ++i;
    }
  }
}

void Sphere::multiThreadGenerateRandomPoints()
{
    vector<thread> threads;
    points.resize(n_points);

    int unsigned n_points_per_thread = floor(n_points / n_threads);

    for (int unsigned k = 0; k < n_threads; k++)
    {
        auto start = k * n_points_per_thread; // starting index
        auto end = (k+1) * n_points_per_thread; // one past the last index
        std::cout << "Thread for [" << start << ", " << end << ")" << std::endl;
        threads.push_back(
            thread(generateRandomPoints, std::ref(*this), start, end)
        );
    }
    for (int unsigned k = 0; k < n_threads; k++) {
        threads[k].join();
    }
}


void Sphere::multiThreadGenerateRegularPoints()
{
    vector<thread> threads;

    int unsigned n_points_per_thread = floor(n_points / n_threads);

    for (int unsigned k = 0; k < n_threads; k++)
    {
        auto start = k * n_points_per_thread; // starting index
        auto end = (k+1) * n_points_per_thread; // one past the last index
        std::cout << "Thread for [" << start << ", " << end << ")" << std::endl;
        threads.push_back(
            thread(generateRegularPoints, std::ref(*this), start, end)
        );
    }
    for (int unsigned k = 0; k < n_threads; k++) {
        threads[k].join();
    }
}
