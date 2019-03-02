#ifndef _MODELS_H
#define _MODELS_H


#include "../src/Shape.h"

Shape* createPlane(float size);
Shape* createCone(float radius, float height, int slices, int stacks);
Shape* createSphere(float radius, int slices, int stacks);
Shape* createBox(float x, float y, float z, int div);
Shape* createCylinder(float radius, float height, int slices, int stacks);

#endif
