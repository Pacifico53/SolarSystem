#include <math.h>
#include "models.h"

using std::vector;

Shape* createPlane(float size){
    Shape* plane = new Shape();
    float half = size / 2;

    plane->pushVertex(new Vertex(half,0,half));
    plane->pushVertex(new Vertex(half,0,-half));
    plane->pushVertex(new Vertex(-half,0,-half));


    plane->pushVertex(new Vertex(half,0,half));
    plane->pushVertex(new Vertex(-half,0,-half));
    plane->pushVertex(new Vertex(-half,0,half));


    return plane;

}

Shape* createCone(float radius, float height, int slices, int stacks){
    float h_angle = 2 * M_PI / slices, v_angle = height / stacks, a=0,b=0, n_radius = 0, r_angle = radius / stacks;
    Shape* cone = new Shape();
    int i;


    for (i = 0; i < slices;i++){
        a = i * h_angle;
        cone->pushVertex(new Vertex(radius*cos(a + h_angle),0,radius*sin(a + h_angle)));
        cone->pushVertex(new Vertex(0,0,0));
        cone->pushVertex(new Vertex(radius*cos(a),0,radius*sin(a)));
    }


    for(i = 0; i < stacks; i++){

        for(int j = 0; j < slices; j++){
            a = j * h_angle;
            n_radius = radius - v_angle;

            cone->pushVertex(new Vertex(radius*cos(a),b,radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a),b+v_angle,n_radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a+h_angle),b+v_angle,n_radius*sin(a+h_angle)));



            cone->pushVertex(new Vertex(radius*cos(a),b,radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a+h_angle),b+v_angle,n_radius*sin(a+h_angle)));
            cone->pushVertex(new Vertex(radius*cos(a+h_angle),b,radius*sin(a+h_angle)));

        }

        radius -= v_angle;
        b += r_angle;
    }

    return cone;

}