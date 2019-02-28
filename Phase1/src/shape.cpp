#include <algorithm>
#include "shape.h"

using std::vector;

void shape::pushVertex(vertex *v) {
    vertexes.push_back(v);
}

void shape::pushShape(shape *s) {
    vertexes.insert(vertexes.end(),s->vertexes.begin(),s->vertexes.end());
}

void shape::getVertex(int i, vertex **v) {
    *v = vertexes.at(i);
}

void shape::reverse() {
    std::reverse(vertexes.begin(),vertexes.end());
}

int shape::getSize() {
    return vertexes.size();
}
