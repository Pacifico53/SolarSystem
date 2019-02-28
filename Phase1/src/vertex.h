#ifndef _VERTEX_H
#define _VERTEX_H

#include <string>

class vertex {

    private:
        float x;
        float y;
        float z;

    public:
        vertex();
        vertex(float xx, float yy, float zz);
        vertex(const vertex *v);
        vertex(std::string str);
        float getX();
        float getY();
        float getZ();

};


#endif
