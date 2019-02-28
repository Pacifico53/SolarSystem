#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define _USE_MATH_DEFINES
#include <vector>
#include "tinyxml2.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace tinyxml2;

float angleX = 1.0f, angleY = 1.0f;

void help_menu(){
    cout<<"##############################" << endl;
    cout<<"#          HELP MENU         #" << endl;
    cout<<"#    Usage:                  #" << endl;
    cout<<"#    ./engine path_to_XML    #" << endl;
    cout<<"#    KeyBinds:               #" << endl;
    cout<<"#       w - Rotate up        #" << endl;
    cout<<"#       s - Rotate down      #" << endl;
    cout<<"#       a - Rotate left      #" << endl;
    cout<<"#       d - Rotate right     #" << endl;
    cout<<"##############################" << endl;
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


void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    // put the geometric transformations here
    glRotatef(angleX, 0,1,0);
    glRotatef(angleY, 0,0,1);

    //Draw axis
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(5.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 5.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 5.0);
    glEnd();

    // End of frame
    glutSwapBuffers();
}



// write function to process keyboard events
void arrowKeys(unsigned char key, int x, int y){
    switch(key){
        case 'w': angleY+=5.0f;
            break;
        case 's': angleY-=5.0f;
            break;
        case 'a': angleX-=5.0f;
            break;
        case 'd': angleX+=5.0f;
            break;
    }
    glutPostRedisplay();
}

vector<string> parseXML(char* fileName){
    string modelName;
    vector<string> files;

    XMLDocument docXML;
    XMLElement *root, *element;

    if(!(docXML.LoadFile(fileName))){
        root = docXML.FirstChildElement("scene");
        for(element = root->FirstChildElement("model"); element; element = element->NextSiblingElement()){
            if(!strcmp(element->Name(),"model")){
                modelName = element->Attribute("file");
                files.push_back(modelName);
                cout << "Model found: " << modelName << "." << endl;
            }
        }
    }
    else{
        cout << "XML file \"" << fileName << "\" not found!" << endl;
    }

    return files;
}


int main(int argc, char **argv) {

    vector<string> files;
    string line;

    if(argc != 2){
        help_menu();
    }
    else {
        files = parseXML(argv[1]);
        if(!files.empty()){
            for(vector<string>::const_iterator i = files.begin(); i != files.end(); ++i){
                cout << *i << endl;
            }
        }
        else{
            return 0;
        }
    }

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(10,100);
    glutInitWindowSize(900,800);
    glutCreateWindow("Phase1");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc( arrowKeys );

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 0;
}
