#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <vector>
#include "tinyxml2.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../src/Vertex.h"
#include "../src/Shape.h"
#include "Parser.h"
#include "../src/Group.h"

using namespace std;
using namespace tinyxml2;

//This is to be able to change the mode with keybinds
int mode = GL_LINE;

Group* scene;

//Camera movement variables
float angleX = 1.0f, angleY = 1.0f;
float ex = 0.0f, ey = 0.0f , ez = 0.0f;
float ax = 0.0f, ay = 0.0f , az = 0.0f;

void help_menu(){
    cout<<"################################" << endl;
    cout<<"#         Engine MENU          #" << endl;
    cout<<"#    Usage:                    #" << endl;
    cout<<"#    ./engine path_to_XML      #" << endl;
    cout<<"#                              #" << endl;
    cout<<"#    KeyBinds:                 #" << endl;
    cout<<"#       w - Rotate up          #" << endl;
    cout<<"#       s - Rotate down        #" << endl;
    cout<<"#       a - Rotate left        #" << endl;
    cout<<"#       d - Rotate right       #" << endl;
    cout<<"#                              #" << endl;
    cout<<"#       j - Fill Mode          #" << endl;
    cout<<"#       k - Line Mode          #" << endl;
    cout<<"#       l - Point Mode         #" << endl;
    cout<<"#                              #" << endl;
    cout<<"#      '-' - Move Cam Back     #" << endl;
    cout<<"#      '+' - Move Cam In       #" << endl;
    cout<<"#                              #" << endl;
    cout<<"#       m - Make axis longer   #" << endl;
    cout<<"#       n - Make axis smaller  #" << endl;
    cout<<"#                              #" << endl;
    cout<<"################################" << endl;
}

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void render(Group* g){
    float x, y, z;
    glPushMatrix();

    vector<Action*> actions = g->getActions();
    for(auto &action : actions){
        action->apply();
    }

    vector<Shape*> shapes = g->getShapes();

    for(auto &shape : shapes){
        vector<Vertex*> verts = shape->getVertexes();

        glBegin(GL_TRIANGLES);
        for(auto &vert : verts){
            x = vert->getX();
            y = vert->getY();
            z = vert->getZ();
            glVertex3f(x,y,z);
        }
        glEnd();
    }

    vector<Group*> children = g->getChildren();
    for (auto &child : children) {
        render(child);
    }

    glPopMatrix();
}

void renderScene() {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(50.0 + ex , 50.0 + ey , 50.0 + ez ,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    // put the geometric transformations here
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    glRotatef(angleX, 0,1,0);
    glRotatef(angleY, 0,0,1);

    //Draw axis
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(5.0 + ax, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 5.0 + ay, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 5.0 + az);
    glEnd();

    // Draw shapes
    render(scene);

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void keyBinds(unsigned char key, int x, int y){
    switch(key){
        case 'w': angleY+=5.0f;
            break;
        case 's': angleY-=5.0f;
            break;
        case 'a': angleX-=5.0f;
            break;
        case 'd': angleX+=5.0f;
            break;
        case 'j': mode = GL_FILL;
            break;
        case 'k': mode = GL_LINE;
            break;
        case 'l': mode = GL_POINT;
            break;
        case 'f': glutFullScreen();
            break;
        case '+': ex -= 2.0f; ey -= 2.0f; ez -= 2.0f;
            break;
        case '-': ex += 2.0f; ey += 2.0f; ez += 2.0f;
            break;
        case 'm': ax += 2.0f; ay += 2.0f; az += 2.0f;
            break;
        case 'n': ax -= 2.0f; ay -= 2.00f; az -= 2.0f;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    string line;

    if(argc != 2){
        help_menu();
    }
    else
        scene = parseXML(argv[1]);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(10,100);
    glutInitWindowSize(900,800);
    glutCreateWindow("Phase2");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc( keyBinds );

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 0;
}
