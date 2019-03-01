#include "models.h"

using std::vector;

Shape* createPlane(float size){
    Shape* shape = new Shape();
    float half = size / 2;
    //Upper
    shape->pushVertex(new Vertex(half,0,half));
    shape->pushVertex(new Vertex(half,0,-half));
    shape->pushVertex(new Vertex(-half,0,-half));


    shape->pushVertex(new Vertex(half,0,half));
    shape->pushVertex(new Vertex(-half,0,-half));
    shape->pushVertex(new Vertex(-half,0,half));

    //Upside-down
    shape->pushVertex(new Vertex(half,0,half));
    shape->pushVertex(new Vertex(-half,0,half));
    shape->pushVertex(new Vertex(half,0,-half));

    shape->pushVertex(new Vertex(-half,0,half));
    shape->pushVertex(new Vertex(half,0,-half));
    shape->pushVertex(new Vertex(half,0,half));


    return shape;

}