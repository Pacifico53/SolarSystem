#ifndef _SHAPE_H
#define _SHAPE_H

#include <string>
#include <vector>
#include <IL/il.h>
#include <GL/gl.h>
#include <GL/glut.h>

#include "Vertex.h"
#include "Material.h"

using namespace std;

class Shape{

    Material* material;
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
        void loadTexture(string texture_file);
        void setMaterial(Material* m);
        void reverse();
        int getNormSize();
        int getTexSize();
        int getSize();
        vector<Vertex*> getVertexes();
        vector<Vertex*> getNormal();
        vector<Vertex*> getTexture();
        Material* getMaterial();
        GLuint* getVertexBuffer();
        void setUp();
        void draw();
        virtual ~Shape();

};

#endif
