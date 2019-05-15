#include <GL/glew.h>
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
float camX= 10, camY = 10 , camZ = 10;
float angleX = 0.8f, angleY = 0.4f, radius = 90.0f;
float ax = 0.0f, ay = 0.0f , az = 0.0f;
int frame = 0, timebase = 0;
float fps;

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

void spherical2Cartesian(){
    camX = radius * cos(angleY) * sin(angleX);
    camY = radius * sin(angleY);
    camZ = radius * cos(angleY) * cos(angleX);
}

void displayFPS(){
    int time;
    char display[30];

    frame ++;
    time = glutGet(GLUT_ELAPSED_TIME);
    if(time - timebase > 1000){
        fps = frame * 1000.0/(time-timebase);
        timebase = time;
        frame = 0;
        sprintf(display,"Engine  |  %.2f FPS",fps);
        glutSetWindowTitle(display);
    }

}

void render(Group* g){
    glPushMatrix();

    vector<Light*> lights = g->getLights();
    for(auto &light: lights){
        light->render();
    }

    vector<Action*> actions = g->getActions();
    for(auto &action : actions){
        action->apply();
    }

    vector<Shape*> shapes = g->getShapes();
    for(auto &shape : shapes){
        shape->draw();
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
    gluLookAt(camX , camY , camZ ,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    // put the geometric transformations here
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, mode);

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    glRotatef(angleX, 0,1,0);
    glRotatef(angleY, 0,0,1);

    //Draw axis
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(10.0 + ax, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 10.0 + ay, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 10.0 + az);
    glEnd();

    // Draw shapes
    glEnable(GL_LIGHTING);
    render(scene);
    glDisable(GL_LIGHTING);

    displayFPS();

    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void keyBinds(unsigned char key, int x, int y){
    switch(key){
        case 'w':
            angleY+=0.1f;
            if(angleY > 1.5f)
                angleY = 1.5f;
            break;
        case 's':
            angleY-=0.1f;
            if(angleY < -1.5f)
                angleY = -1.5f;
            break;
        case 'a': angleX-=0.1f;
            break;
        case 'd': angleX+=0.1f;
            break;
        case 'j': mode = GL_FILL;
            break;
        case 'k': mode = GL_LINE;
            break;
        case 'l': mode = GL_POINT;
            break;
        case 'f': glutFullScreen();
            break;
        case '-':
            radius += 10.1f;
            break;
        case '+':
            radius -= 10.1f;
            if(radius < 0.1f)
                radius = 0.1f;
            break;
        case 'm': ax += 2.0f; ay += 2.0f; az += 2.0f;
            break;
        case 'n': ax -= 2.0f; ay -= 2.00f; az -= 2.0f;
            break;
    }
    spherical2Cartesian();
}

int main(int argc, char **argv) {
    string line;

    spherical2Cartesian();
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(10,100);
    glutInitWindowSize(900,800);
    glutCreateWindow("Phase4");
    glewInit();
    ilInit();

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc( keyBinds );

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_NORMALIZE);

    if(argc != 2){
        help_menu();
    }
    else {
        scene = parseXML(argv[1]);
    }

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // enter GLUT's main cycle
    glutMainLoop();

    return 0;
}
