#ifndef _SHAPE_H
#define _SHAPE_H

#include<vector>
#include "vertex.h"

class shape {

    private:
        std::vector<vertex*> vertexes;

    public:
        void pushVertex(vertex* v);
        void pushShape(shape * s);
        std::vector<float> *getVertexes();
        void getVertex(int i, vertex** v);
        void reverse();
        int getSize();
};


#endif
