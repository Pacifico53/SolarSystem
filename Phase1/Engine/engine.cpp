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

using namespace std;
using namespace tinyxml2;

float angleX = 1.0f, angleY = 1.0f;
int mode = GL_LINE;

float ex = 0.0f, ey = 0.0f , ez = 0.0f;
float ax = 0.0f, ay = 0.0f , az = 0.0f;


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
    gluLookAt(5.0 + ex , 5.0 + ey , 5.0 + ez ,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    // put the geometric transformations here
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, mode);
-+

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


    // put drawing instructions here


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
        case 'j': mode = GL_FILL;
            break;
        case 'k': mode = GL_LINE;
            break;
        case 'l': mode = GL_POINT;
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

vector<string> parseXML(char* fileName){
    string modelName;
    vector<string> files;

    XMLDocument docXML;
    XMLElement *root, *element;

    if((docXML.LoadFile(fileName)) == 0){
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

vector<Vertex*> read_file(string fileName){
    vector<Vertex*> result;
    string line;
    string pathToFile = "../Generator/" + fileName;

    ifstream file(fileName);

    if (!file.fail()){
        while(getline(file, line)){
            Vertex *v = new Vertex(line);
            result.push_back(v);
        }
    }
    else {
        cout << "Failed to open file " << fileName << "." << endl;
    }
}

int main(int argc, char **argv) {

    vector<string> files3d;
    string line;

    if(argc != 2){
        help_menu();
    }
    else {
        files3d = parseXML(argv[1]);
        if(!files3d.empty()){
            for (auto &file : files3d) {
                cout << file << endl;
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
