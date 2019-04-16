#ifndef _ACTION_H
#define _ACTION_H

#include "../Engine/tinyxml2.h"
#include "Vertex.h"
#include <vector>

using namespace std;
void calcCatmullrom(float t, int* index, float* p, std::vector<Vertex*> points);

class Action {
    public:
        virtual void apply() = 0;
};

class Translation : public Action{
    private:
        vector<Vertex*> curve_points;
        vector<Vertex*> catmull_points;
        float time;
        float x;
        float y;
        float z;

    public:
        Translation();
        void generateCurve();
        void parse(tinyxml2::XMLElement *tr);
        void apply();
};

class Rotation : public Action{
    private:
        float angle;
        float time;
        float x;
        float y;
        float z;

    public:
        Rotation();
        void parse(tinyxml2::XMLElement *rt);
        void apply();
};

class Scale : public Action{
    private:
        float x;
        float y;
        float z;
    public:
        Scale();
        void parse(tinyxml2::XMLElement *sc);
        void apply();
};

class Color : public Action{
    private:
        float r;
        float g;
        float b;

    public:
        Color();
        void parse(tinyxml2::XMLElement *cl);
        void apply();
};

#endif
