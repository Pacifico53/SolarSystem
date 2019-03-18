#ifndef _SHAPE_H
#define _SHAPE_H

#include <string>
#include <vector>
#include "Vertex.h"

using namespace std;

class Shape{

    vector<Vertex*> vertexes;

public:
    explicit Shape();
    explicit Shape(vector<Vertex*>);
    void pushVertex(Vertex* v);
    void pushShape(Shape* s);
    void getVertex(int i, Vertex** v);
    void reverse();
    int getSize();
    vector<Vertex*> getVertexes();
    virtual ~Shape(void);
};

#endif
