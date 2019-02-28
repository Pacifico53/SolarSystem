#include <algorithm>
#include "Shape.h"

using std::vector;

Shape::Shape(vector<Vertex*> list){
    vertexes = list;
}

void Shape::pushVertex(Vertex *v) {
    vertexes.push_back(v);
}

void Shape::pushShape(Shape *s) {
    vertexes.insert(vertexes.end(),s->vertexes.begin(),s->vertexes.end());
}

void Shape::getVertex(int i, Vertex **v) {
    *v = vertexes.at(i);
}

void Shape::reverse() {
    std::reverse(vertexes.begin(),vertexes.end());
}

int Shape::getSize() {
    return vertexes.size();
}

vector<Vertex*> Shape::getVertexes(){
    return vertexes;
}
