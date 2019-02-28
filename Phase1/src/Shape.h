#ifndef _SHAPE_H
#define _SHAPE_H

#include<vector>
#include "Vertex.h"

class Shape {

    private:
        std::vector<Vertex*> vertexes;

    public:
        void pushVertex(Vertex* v);
        void pushShape(Shape * s);
        std::vector<float> *getVertexes();
        void getVertex(int i, Vertex** v);
        void reverse();
        int getSize();
};


#endif
