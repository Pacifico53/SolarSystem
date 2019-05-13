#ifndef _SHAPE_H
#define _SHAPE_H

#include <string>
#include <vector>
#include <GL/gl.h>

#include "Vertex.h"

using namespace std;

class Shape{

    vector<Vertex*> vertexes;
    vector<Vertex*> normal;
    vector<Vertex*> texture;
    GLuint text, buffer[3];


    public:
        explicit Shape();
        explicit Shape(vector<Vertex*>);
        explicit Shape(vector<Vertex*> vertexes, vector<Vertex*> normal, vector<Vertex*> texture);
        void pushVertex(Vertex* v);
        void pushShape(Shape* s);
        void getVertex(int i, Vertex** v);
        void pushNormal(Vertex* v);
        void pushTexture(Vertex* v);
        void reverse();
        int getNormSize();
        int getTexSize();
        int getSize();
        vector<Vertex*> getVertexes();
        vector<Vertex*> getNormal();
        vector<Vertex*> getTexture();
        GLuint* getVertexBuffer();
        void setUp();
        void draw();
        virtual ~Shape();

};

#endif
