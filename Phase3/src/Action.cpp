#include <GL/glut.h>
#include "Action.h"
#include <iostream>
#include <string>
#include "CatmullRom.h"

using tinyxml2::XMLElement;

Translation::Translation(){
    time = 0;
    x = 0;
    y = 0;
    z = 0;
}

Rotation::Rotation(){
    angle = 0;
    time = 0;
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

void Rotation::parse(XMLElement *rt){
    rt->QueryFloatAttribute("angle", &angle);
    rt->QueryFloatAttribute("time", &time);
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


void Translation::parse(XMLElement * tr){
    tr->QueryFloatAttribute("time", &time);
    tr->QueryFloatAttribute("X", &x);
    tr->QueryFloatAttribute("Y", &y);
    tr->QueryFloatAttribute("Z", &z);

    XMLElement* point_element = tr->FirstChildElement();

    for(; point_element; point_element = point_element->NextSiblingElement()){
        float px=0, py=0, pz=0;

        point_element->QueryFloatAttribute("X",&px);
        point_element->QueryFloatAttribute("Y",&py);
        point_element->QueryFloatAttribute("Z",&pz);

        Vertex* vertex = new Vertex(px,py,pz);
        catmull_points.push_back(vertex);
    }
    generateCurve();

}

void Translation::generateCurve(){
    float p[3];

    if(!catmull_points.empty()) {
        for (float gt = 0; gt < 1; gt += 0.01f) {
            catmullRomPoint(gt, p, catmull_points);

            curve_points.push_back(new Vertex(p[0], p[1], p[2]));
        }
    }
}

void drawCatmullRomCurve(vector<Vertex *> points) {
    float p[3];

    glBegin(GL_LINE_LOOP);
    for (auto &point : points) {
        p[0] = point->getX();
        p[1] = point->getY();
        p[2] = point->getZ();

        glVertex3fv(p);
    }
    glEnd();
}

void Translation::apply() {
    float coord[3] = {x, y, z};

    if(time>0){
        float elapsed = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        float rt = elapsed/(time*1000);
        drawCatmullRomCurve(curve_points);

        catmullRomPoint(rt,coord,catmull_points);
    }

    glTranslatef(coord[0], coord[1], coord[2]);
}

void Rotation::apply() {
    float t, ang;

    if (time == 0) {
        glRotatef(angle, x, y, z);
    }
    else {
        t = glutGet(GLUT_ELAPSED_TIME) % (int) (time * 1000);
        ang = (t * 360) / (time * 1000);
        glRotatef(ang, x, y, z);
    }
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
