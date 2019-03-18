#include <GL/glut.h>
#include "Action.h"
#include <iostream>
#include <string>

using tinyxml2::XMLElement;

Translation::Translation(){
    x = 0;
    y = 0;
    z = 0;
}

Rotation::Rotation(){
    angle = 0;
    x = 0;
    y = 0;
    z = 0;
}

Scale::Scale(){
    x = 1;
    y = 1;
    z = 1;
}

Color::Color(){
    r = 0;
    g = 0;
    b = 0;
}

void Translation::parse(XMLElement * tr){
    tr->QueryFloatAttribute("X", &x);
    tr->QueryFloatAttribute("Y", &y);
    tr->QueryFloatAttribute("Z", &z);
}

void Rotation::parse(XMLElement *rt){
    rt->QueryFloatAttribute("angle", &angle);
    rt->QueryFloatAttribute("X", &x);
    rt->QueryFloatAttribute("Y", &y);
    rt->QueryFloatAttribute("Z", &z);
}

void Scale::parse(XMLElement *sc){
    sc->QueryFloatAttribute("X", &x);
    sc->QueryFloatAttribute("Y", &y);
    sc->QueryFloatAttribute("Z", &z);
}

void Color::parse(XMLElement *cl){
    cl->QueryFloatAttribute("R", &r);
    cl->QueryFloatAttribute("G", &g);
    cl->QueryFloatAttribute("B", &b);
}

void Translation::apply() {
    glTranslatef(x,y,z);
}

void Rotation::apply() {
    glRotatef(angle,x,y,z);
}

void Scale::apply() {
    glScalef(x,y,z);
}

void Color::apply() {
    float rt = r/255;
    float gt = g/255;
    float bt = b/255;
    glColor3f(rt,gt,bt);
}
