#include "CatmullRom.h"
#include <cmath>

void calcCatmullrom(float t, int* index, float* p, std::vector<Vertex*> points){
    float aux[4];
    float t2 = t*t;
    float t3 = t*t*t;

    float m[4][4] = { {-0.5f, 1.5f,-1.5f, 0.5f},
                      { 1.0f,-2.5f, 2.0f,-0.5f},
                      {-0.5f, 0.0f, 0.5f, 0.0f},
                      { 0.0f, 1.0f, 0.0f, 0.0f}
                    };

    p[0] = 0.0f;
    p[1] = 0.0f;
    p[2] = 0.0f;

    aux[0] = t3*m[0][0] + t2*m[1][0] + t*m[2][0];
    aux[1] = t3*m[0][1] + t2*m[1][1]            + m[3][1];
    aux[2] = t3*m[0][2] + t2*m[1][2] + t*m[2][2];
    aux[3] = t3*m[0][3] + t2*m[1][3];

    Vertex* v0 = points[index[0]];
    Vertex* v1 = points[index[1]];
    Vertex* v2 = points[index[2]];
    Vertex* v3 = points[index[3]];

    p[0] = aux[0] * v0->getX() + aux[1] * v1->getX() + aux[2] * v2->getX() + aux[3] * v3->getX();
    p[1] = aux[0] * v0->getY() + aux[1] * v1->getY() + aux[2] * v2->getY() + aux[3] * v3->getY();
    p[2] = aux[0] * v0->getZ() + aux[1] * v1->getZ() + aux[2] * v2->getZ() + aux[3] * v3->getZ();
}

void catmullRomPoint(float t, float *p, std::vector<Vertex*> points){
    int p_size = points.size();

    float rt = t * p_size;
    int i = floor(rt);
    rt = rt - i;

    int index[4];
    index[0] = (i  + p_size - 1) % p_size;
    index[1] = (index[0]  + 1) % p_size;
    index[2] = (index[1]  + 1) % p_size;
    index[3] = (index[2]  + 1) % p_size;

    calcCatmullrom(rt,index,p,points);
}
