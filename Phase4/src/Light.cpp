#include "Light.h"

Light::Light() = default;

Light::Light(bool b, Vertex * p) {
    isPoint = b;
    position = p;
}

Vertex* Light::get_position() {
    return position;
}

bool Light::is_point() {
    return isPoint;
}

void Light::set_position(Vertex * p) {
    position = p;
}

void Light::set_type(bool b){
    isPoint = b;
}

void Light::render(){
    GLfloat amb[4] = {0.1,0.1,0.1,1};
    GLfloat diff[4] = {1,1,1,0};
    GLfloat spec[4] = {1.0, 1.0, 1.0, 1.0};
    GLfloat pos[4] = {position->getX(), position->getY(), position->getZ(), (float) isPoint};

    //position
    glLightfv(GL_LIGHT0,GL_POSITION,pos);

    //colors
    //ambient
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb);
    //diffuse
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diff);
    //specular
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
}
