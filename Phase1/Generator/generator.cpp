#include "../src/Vertex.h"
#include "../src/Shape.h"
#include "models.h"

#include <cstring>
#include <fstream>

using std::ofstream;
using std::string;

void printGuide();
void writeFile(Shape* s, string f_path);
void generatePlane(char* s, char* f_path);
void generateCone(char* r, char* h, char* sl, char* st,char * f_path);


int main(int argc, char** argv){
    if (argc == 1) printGuide();
        // argv[1] = plane | argv[2] = size | argv[3] = file path
    else {
        if (!(strcmp(argv[1], "plane")) && (argc == 4))
            generatePlane(argv[2], argv[3]);
        else if (!(strcmp(argv[1], "cone")) && (argc == 7))
            generateCone(argv[2], argv[3], argv[4], argv[5], argv[6]);
    }



    return 0;
}

void printGuide() {

}

void generatePlane(char* s, char* f_path){
    float size = atof(s);
    ofstream file;

    Shape* p = createPlane(size);
    writeFile(p,f_path);
}

void generateCone(char* r, char* h, char* sl, char* st,char * f_path){
    float radius = atof(r), height = atof(h);
    int slices = atoi(sl), stacks = atoi(st);
    ofstream file;
    Shape* c = createCone(radius,height,slices,stacks);
    writeFile(c,f_path);

}

void writeFile(Shape* s, string f_path){
    char buff[1024];
    int i;
    int size = s->getSize();
    Vertex* v;

    system("mkdir -p ../files3d/ ");
    string path = "../files3d/" + f_path;
    ofstream file (path,std::ofstream::out);

    for(i=0;i<size;i++){
        s->getVertex(i,&v);
        sprintf(buff, "%f %f %f\n", v->getX(), v->getY(), v->getZ());
        file << buff;
    }
    file.close();
}


















