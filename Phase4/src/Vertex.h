#ifndef _VERTEX_H
#define _VERTEX_H

#include <string>

class Vertex {

    private:
        float x;
        float y;
        float z;

    public:
        Vertex();
        Vertex(float xx, float yy, float zz);
        Vertex(const Vertex *v);
        Vertex(std::string str);
        Vertex(std::string str, float z);
        float getX();
        float getY();
        float getZ();

};


#endif
