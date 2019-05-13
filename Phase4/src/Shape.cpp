#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include "Shape.h"

using std::vector;

Shape::Shape(){};

Shape::Shape(vector<Vertex*> list){
    vertexes = list;
}

void Shape::pushVertex(Vertex *v) {
    vertexes.push_back(v);
}

void Shape::pushShape(Shape *s) {
    vertexes.insert(vertexes.end(), s->vertexes.begin(), s->vertexes.end());
}

void Shape::getVertex(int i, Vertex **v) {
    *v = vertexes.at(i);
}

void Shape::pushNormal(Vertex* v){
    normal.push_back(v);
}


void Shape::pushTexture(Vertex* v){
    texture.push_back(v);
}

void Shape::reverse() {
    std::reverse(vertexes.begin(),vertexes.end());
}

int Shape::getSize() {
    return vertexes.size();
}
int Shape::getNormSize(){
    return normal.size();
}

int Shape::getTexSize(){
    return texture.size();
}

vector<Vertex*> Shape::getVertexes(){
    return vertexes;
}

vector<Vertex*> Shape::getNormal(){
    return normal;
}

vector<Vertex*> Shape::getTexture(){
    return texture;
}

GLuint* Shape::getVertexBuffer() {
    return buffer;
}


void Shape::setUp(){

    float *vertex_array = (float*) malloc(sizeof(float) * vertexes.size() * 3);
    int i = 0;
    for (Vertex* v : vertexes ){
        vertex_array[i] = v->getX();
        vertex_array[i+1] = v->getY();
        vertex_array[i+2] = v->getZ();
        i += 3;
     }

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i, vertex_array,GL_STATIC_DRAW);

    free(vertex_array);
}

void Shape::draw(){
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //Set the Vertex Pointer to the vertex buffer
    glVertexPointer(3, GL_FLOAT, 0, nullptr);
    //Draw all Triangles at once
    glDrawArrays(GL_TRIANGLES, 0, vertexes.size()*3);
}

Shape::~Shape(void){

}

