#ifndef _SHAPE_H
#define _SHAPE_H

#include <string>
#include <vector>
#include <GL/gl.h>

#include "Vertex.h"

using namespace std;

class Shape{

    vector<Vertex*> vertexes;
    GLuint buffer;

    public:
        explicit Shape();
        explicit Shape(vector<Vertex*>);
        void pushVertex(Vertex* v);
        void pushShape(Shape* s);
        void getVertex(int i, Vertex** v);
        void reverse();
        int getSize();
        vector<Vertex*> getVertexes();
        GLuint getVertexBuffer();
        void setUp();
        void draw();
        virtual ~Shape();

};

#endif
