#ifndef GENERATOR_LIGHT_H
#define GENERATOR_LIGHT_H

#include "Vertex.h"
#include <GL/glut.h>

class Light {
    bool isPoint = false;
    Vertex* position = new Vertex();
    public:
        Light();
        Light(bool, Vertex*);
        bool is_point();
        Vertex* get_position();
        void set_type(bool);
        void set_position(Vertex *);
        void render();
};

#endif //GENERATOR_LIGHT_H
