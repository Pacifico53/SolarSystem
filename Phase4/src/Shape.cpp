#include <GL/glew.h>
#include <GL/glut.h>
#include <algorithm>
#include <iostream>

#include "Shape.h"

using std::vector;

Shape::Shape(){}

Shape::Shape(vector<Vertex*> list){
    vertexes = list;
}

Shape::Shape(vector<Vertex*> v, vector<Vertex*> n, vector<Vertex*> t){
    vertexes = v;
    normal = n;
    texture = t;
    setUp();
}

void Shape::setMaterial(Material *m){
    material = m;
}

void Shape::pushShape(Shape *s) {
    vertexes.insert(vertexes.end(), s->vertexes.begin(), s->vertexes.end());
}

void Shape::getVertex(int i, Vertex **v) {
    *v = vertexes.at(i);
}

void Shape::pushVertex(Vertex* v){
    vertexes.push_back(v);
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

Material* Shape::getMaterial() {
    return material;
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
    float *normal_array = (float*) malloc(sizeof(float) * normal.size() * 3);
    float *texture_array = (float*) malloc(sizeof(float) * texture.size() * 2);

    int i = 0;
    for (Vertex* v : vertexes ){
        vertex_array[i] = v->getX();
        vertex_array[i+1] = v->getY();
        vertex_array[i+2] = v->getZ();
        i += 3;
     }

    int j = 0;
    for (Vertex* v : normal ){
        normal_array[j] = v->getX();
        normal_array[j+1] = v->getY();
        normal_array[j+2] = v->getZ();
        j += 3;
    }

    int k = 0;
    for (Vertex* v : texture ){
        texture_array[k] = v->getX();
        texture_array[k+1] = v->getY();
        k += 2;
    }

    glGenBuffers(3, buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * i, vertex_array,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * j, normal_array,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffer[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * k, texture_array,GL_STATIC_DRAW);

    free(vertex_array);
    free(normal_array);
    free(texture_array);
}

void Shape::draw(){

    material->draw();


    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    //Set the Vertex Pointer to the vertex buffer
    glVertexPointer(3, GL_FLOAT, 0, 0);

    if(!normal.empty()){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
        glNormalPointer(GL_FLOAT, 0, 0);
    }

    if(!texture.empty()){
        glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);
        glBindTexture(GL_TEXTURE_2D, text);
    }

    //Draw all Triangles at once
    glDrawArrays(GL_TRIANGLES, 0, vertexes.size()*3);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shape::loadTexture(string texture_file) {
    string path = "../Textures/" + texture_file;
    unsigned int tw,th;
    unsigned char *texData;

    unsigned int ima[1];

    cout << "Ficheiro Texture Encontrado!" << endl;
    ilGenImages(1, ima);
    ilBindImage(ima[0]);
    ilLoadImage((ILstring)path.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    cout << "Ficheiro Texture Encontrado!" << endl;
}

Shape::~Shape(void){
}
