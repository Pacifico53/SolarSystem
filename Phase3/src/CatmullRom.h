#ifndef GENERATOR_CATMULLROM_H
#define GENERATOR_CATMULLROM_H

#include "Vertex.h"
#include <vector>
using namespace std;

void catmullRomPoint(float t, float *p, std::vector<Vertex*> points);
void calcCatmullrom(float t, int* index, float* p, std::vector<Vertex*> points);
#endif //GENERATOR_CATMULLROM_H
