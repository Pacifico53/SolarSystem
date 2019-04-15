#ifndef GENERATOR_BEZIER_H
#define GENERATOR_BEZIER_H

#include "../src/Shape.h"
#include <string>
#include <fstream>
#include <iostream>

Shape* parseBezier(string patch_path, int tesselation);
void processPatch(int tess, int n);
Vertex* bezierCalc(float u, float v, int patch_num);
Vertex* vertexCalc(float t, float *p1, float *p2, float *p3, float *p4);
#endif //GENERATOR_BEZIER_H
