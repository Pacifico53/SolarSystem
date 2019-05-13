#include "../src/Vertex.h"
#include "../src/Shape.h"
#include "models.h"

#include "bezier.h"
#include <cstring>
#include <fstream>
#include <iostream>

using std::ofstream;
using std::string;

void gen_menu();
void writeFile(Shape* s, string f_path);
void generatePlane(char* s, char* f_path);
void generateCone(char* r, char* h, char* sl, char* st,char * f_path);
void generateSphere(char* r, char* sl, char* st, char* f_path);
void generateBox(char* x, char* y, char* z, char* n, char* f_path);
void generateCylinder(char* r, char* h, char* sl,char * f_path);
void generateTorus(char* innerR, char* outerR, char* sl, char* nrings, char* f_path);
void generatePatch(char* patch_path, int tesselation, char* f_path);


int main(int argc, char** argv){
    if (argc == 1) gen_menu();
    else {
        if (!(strcmp(argv[1], "plane")) && (argc == 4)) {
            std::cout << "Generating plane..." << std::endl;
            generatePlane(argv[2], argv[3]);
            std::cout << "Done!" << std::endl;
        }
        else if (!(strcmp(argv[1], "cone")) && (argc == 7)) {
            std::cout << "Generating cone..." << std::endl;
            generateCone(argv[2], argv[3], argv[4], argv[5], argv[6]);
            std::cout << "Done!" << std::endl;
        }
        else if (!(strcmp(argv[1],"sphere")) && (argc == 6)) {
            std::cout << "Generating sphere..." << std::endl;
            generateSphere(argv[2], argv[3], argv[4], argv[5]);
            std::cout << "Done!" << std::endl;
        }
        else if (!(strcmp(argv[1],"box")) && (argc == 7)) {
            std::cout << "Generating box..." << std::endl;
            generateBox(argv[2], argv[3], argv[4], argv[5], argv[6]);
            std::cout << "Done!" << std::endl;
        }
        else if (!(strcmp(argv[1],"cylinder")) && (argc == 6)) {
            std::cout << "Generating cylinder..." << std::endl;
            generateCylinder(argv[2], argv[3], argv[4], argv[5]);
            std::cout << "Done!" << std::endl;
        }
        else if (!strcmp(argv[1],"torus") && argc == 7){
            generateTorus(argv[2], argv[3], argv[4], argv[5], argv[6]);
            std::cout << "Done!" << std::endl;
        }
        else if(!strcmp(argv[1],"patch") && argc == 5){
            generatePatch(argv[2],atoi(argv[3]), argv[4]);
        }
    }
    return 0;
}

void gen_menu(){
    cout<<"#################################################################" << endl;
    cout<<"#                       Generator MENU                          #" << endl;
    cout<<"#     Usage:                                                    #" << endl;
    cout<<"#     ./generate <shape> [options] <file>                       #" << endl;
    cout<<"#                                                               #" << endl;
    cout<<"#     Shapes & Options:                                         #" << endl;
    cout<<"#        -> plane <size>                                        #" << endl;
    cout<<"#        -> box <width> <height> <length> <divisions>           #" << endl;
    cout<<"#        -> sphere <radius> <slices> <stacks>                   #" << endl;
    cout<<"#        -> cone <radius> <height> <slices> <stacks>            #" << endl;
    cout<<"#        -> cylinder <radius> <height> <slices>                 #" << endl;
    cout<<"#        -> torus <innerRadius> <outerRadius> <slices> <rings>  #" << endl;
    cout<<"#        -> patch <path_to_path_file> <tesselation> <shapename> #" << endl;
    cout<<"#################################################################" << endl;
}

void generatePlane(char* s, char* f_path){
    float size = atof(s);
    ofstream file;

    Shape* p = createPlane(size);
    writeFile(p,f_path);
}

void generateCone(char* r, char* h, char* sl, char* st, char * f_path){
    float radius = atof(r), height = atof(h);
    int slices = atoi(sl), stacks = atoi(st);
    ofstream file;
    Shape* c = createCone(radius,height,slices,stacks);
    writeFile(c,f_path);
}

void generateSphere(char* r, char* sl, char* st, char* f_path){
    float radius = atof(r);
    int slices = atoi(sl), stacks = atoi(st);
    ofstream file;
    Shape* s = createSphere(radius,slices,stacks);
    writeFile(s,f_path);
}

void generateBox(char* x, char* y, char* z, char* n, char* f_path){
    float xx = atof(x), yy = atof(y), zz = atof (z);
    int nd = atoi(n);
    ofstream file;
    Shape* b = createBox(xx,yy,zz,nd);
    writeFile(b,f_path);
}

void generateCylinder(char* r, char* h, char* sl, char * f_path){
    float radius = atof(r), height = atof(h);
    int slices = atoi(sl);
    ofstream file;
    Shape* c = createCylinder(radius,height,slices);
    writeFile(c,f_path);
}

void generateTorus(char* innerR, char* outerR, char* sl, char* nrings, char* f_path) {
    float radius = atof(innerR), radiusOuter = atof(outerR);
    int slices = atoi(sl), rings = atoi(nrings);
    Shape *t = createTorus(radius, radiusOuter, slices, rings);
    ofstream file;
    writeFile(t, f_path);
}

void generatePatch(char* patch_path, int tesselation, char* f_path){
    Shape* patch = parseBezier(patch_path,tesselation);
    writeFile(patch,f_path);
}

void writeFile(Shape* s, string f_path){
    char buff[1024];
    int i;
    int size = s->getSize();
    Vertex* v;

    system("mkdir -p ../files3d/ ");
    string path = "../files3d/" + f_path;
    ofstream file (path,std::ofstream::out);

    file << size << endl;
    for(i=0;i<size;i++){
        s->getVertex(i,&v);
        sprintf(buff, "%f %f %f\n", v->getX(), v->getY(), v->getZ());
        file << buff;
    }

    if(s->getNormSize()){
        float nsize = s->getNormSize();
        file << nsize << endl;
        vector<Vertex*> normal = s->getNormal();
        for(Vertex* n: normal){
            sprintf(buff, "%f %f %f\n", n->getX(),n->getY(),n->getZ());
            file << buff;
        }


    }
    if(s->getTexSize()) {
        float tsize = s->getTexSize();
        file << tsize << endl;
        vector<Vertex *> texture = s->getTexture();
        for (Vertex *t: texture) {
            sprintf(buff, "%f %f %f\n", t->getX(), t->getY(), t->getZ());
            file << buff;
        }
    }

    file.close();
}
