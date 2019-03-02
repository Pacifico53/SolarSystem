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

    plane->pushVertex(new Vertex(half,0,half));
    plane->pushVertex(new Vertex(-half,0,-half));
    plane->pushVertex(new Vertex(half,0,-half));

    plane->pushVertex(new Vertex(half,0,half));
    plane->pushVertex(new Vertex(-half,0,half));
    plane->pushVertex(new Vertex(-half,0,-half));


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
            n_radius = radius - r_angle;

            cone->pushVertex(new Vertex(radius*cos(a),b,radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a),b+v_angle,n_radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a+h_angle),b+v_angle,n_radius*sin(a+h_angle)));



            cone->pushVertex(new Vertex(radius*cos(a),b,radius*sin(a)));
            cone->pushVertex(new Vertex(n_radius*cos(a+h_angle),b+v_angle,n_radius*sin(a+h_angle)));
            cone->pushVertex(new Vertex(radius*cos(a+h_angle),b,radius*sin(a+h_angle)));

        }

        radius -= r_angle;
        b += v_angle;
    }

    return cone;

}

Shape* createSphere(float radius, int slices, int stacks){
    float h_angle = 2 * M_PI / slices , v_angle = M_PI / stacks, a = 0, b = 0;
    Shape* sphere = new Shape();

    for(int i = 0; i < stacks; i++){
        b = i * v_angle;
        for(int j = 0; j < slices; j++){
            a = j * h_angle;

            sphere->pushVertex(new Vertex(radius*sin(a)*sin(b),radius*cos(b),radius*cos(a)*sin(b)));
            sphere->pushVertex(new Vertex(radius*sin(a)*sin(b+v_angle),radius*cos(b+v_angle),radius*cos(a)*sin(b+v_angle)));
            sphere->pushVertex(new Vertex(radius*sin(a+h_angle)*sin(b),radius*cos(b),radius*cos(a+h_angle)*sin(b)));

            sphere->pushVertex(new Vertex(radius*sin(a+h_angle)*sin(b),radius*cos(b),radius*cos(a+h_angle)*sin(b)));
            sphere->pushVertex(new Vertex(radius*sin(a)*sin(b+v_angle),radius*cos(b+v_angle),radius*cos(a)*sin(b+v_angle)));
            sphere->pushVertex(new Vertex(radius*sin(a+h_angle)*sin(b+v_angle),radius*cos(b+v_angle),radius*cos(a+h_angle)*sin(b+v_angle)));

        }

    }



    return sphere;
}

Shape* createBox(float x, float y, float z, int nd){
    Shape * box = new Shape();
    float shiftX = x/nd, shiftY = y/nd, shiftZ = z/nd;
    x = x/2;
    y = y/2;
    z = z/2;


    for(int i=0;i<nd;i++){
        for(int j=0;j<nd;j++){

            //XY Front
            box->pushVertex(new Vertex(x - (j*shiftX),y - (i*shiftY),z));
            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,y - (i*shiftY),z));
            box->pushVertex(new Vertex(x - (j*shiftX),(y-shiftY) - (i*shiftY),z));

            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,y - (i*shiftY),z));
            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,(y-shiftY) - (i*shiftY),z));
            box->pushVertex(new Vertex(x - (j*shiftX) ,(y-shiftY) - (i*shiftY),z));

            //XY Back
            box->pushVertex(new Vertex(x - (j*shiftX),y - (i*shiftY),-z));
            box->pushVertex(new Vertex(x - (j*shiftX),(y-shiftY) - (i*shiftY),-z));
            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,y - (i*shiftY),-z));

            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,y - (i*shiftY),-z));
            box->pushVertex(new Vertex(x - (j*shiftX) ,(y-shiftY) - (i*shiftY),-z));
            box->pushVertex(new Vertex((x-shiftX) - (j*shiftX) ,(y-shiftY) - (i*shiftY),-z));

            //ZY Front
            box->pushVertex(new Vertex(x, y - (i * shiftY),z - (j*shiftZ) ));
            box->pushVertex(new Vertex(x, (y-shiftY) - (i * shiftY),(z-shiftZ) - (j*shiftZ) ));
            box->pushVertex(new Vertex(x, y - (i * shiftY),(z-shiftZ) - (j*shiftZ)));


            box->pushVertex(new Vertex(x, y - (i * shiftY),z - (j*shiftZ) ));
            box->pushVertex(new Vertex(x, (y-shiftY) - (i * shiftY), z - (j * shiftZ)));
            box->pushVertex(new Vertex(x, (y-shiftY) - (i * shiftY),(z-shiftZ) - (j*shiftZ) ));


            //ZY Back
            box->pushVertex(new Vertex(-x, y - (i * shiftY),z - (j*shiftZ) ));
            box->pushVertex(new Vertex(-x, y - (i * shiftY),(z-shiftZ) - (j*shiftZ)));
            box->pushVertex(new Vertex(-x, (y-shiftY) - (i * shiftY),(z-shiftZ) - (j*shiftZ) ));


            box->pushVertex(new Vertex(-x, y - (i * shiftY),z - (j*shiftZ) ));
            box->pushVertex(new Vertex(-x, (y-shiftY) - (i * shiftY),(z-shiftZ) - (j*shiftZ) ));
            box->pushVertex(new Vertex(-x, (y-shiftY) - (i * shiftY), z - (j * shiftZ)));

            //XZ Front
            box->pushVertex(new Vertex(x - (i * shiftX),y,z - (j * shiftZ)));
            box->pushVertex(new Vertex(x - (i * shiftX),y,(z-shiftZ) - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),y,z - (j * shiftZ)));

            box->pushVertex(new Vertex(x - (i * shiftX),y,(z-shiftZ) - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),y,(z-shiftZ) - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),y,z - (j * shiftZ)));

            //XZ Back
            box->pushVertex(new Vertex(x - (i * shiftX),-y,z - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),-y,z - (j * shiftZ)));
            box->pushVertex(new Vertex(x - (i * shiftX),-y,(z-shiftZ) - (j * shiftZ)));

            box->pushVertex(new Vertex(x - (i * shiftX),-y,(z-shiftZ) - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),-y,z - (j * shiftZ)));
            box->pushVertex(new Vertex((x-shiftX) - (i * shiftX),-y,(z-shiftZ) - (j * shiftZ)));



        }
    }
    return box;

}