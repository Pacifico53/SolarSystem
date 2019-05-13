#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Parser.h"

Group* child_of(Group* parent){
    Group* child = new Group();
    parent->addChild(child);

    return child;
}

void parse_translation(XMLElement* element, Group* g){
    Translation* transl = new Translation();
    transl->parse(element);
    g->addAction(transl);
}

void parse_rotation(XMLElement* element, Group* g){
    Rotation* rot = new Rotation();
    rot->parse(element);
    g->addAction(rot);
}

void parse_scale(XMLElement* element, Group* g){
    Scale* scale = new Scale();
    scale->parse(element);
    g->addAction(scale);
}


void parse_color(XMLElement* element, Group* g){
    Color* color = new Color();
    color->parse(element);
    g->addAction(color);
}

vector<Shape*> parse_models(XMLElement* element){
    string modelName;
    vector<Shape*> models;

    for(element = element->FirstChildElement(); element; element = element->NextSiblingElement()){
        if(!strcmp(element->Name(),"model")){
            modelName = element->Attribute("file");
            Shape *s = read_file(modelName);


            if (s->getSize()){
                if(element->Attribute("texture")){
                    s->loadTexture(element->Attribute("texture"));
                }

            }
            s->setUp();
            models.push_back(s);

            cout << "Model found: " << modelName << "." << endl;
        }
    }

    return models;
}




void find_elements(XMLElement* element, Group* g){

    XMLElement* current = element;

    if(!strcmp(element->Name(),"translate"))
        parse_translation(element,g);
    else if(!strcmp(element->Name(),"rotate"))
        parse_rotation(element,g);
    else if(!strcmp(element->Name(),"scale"))
        parse_scale(element,g);
    else if(!strcmp(element->Name(),"models")){
        vector<Shape*> shapes = parse_models(element);
        if(!shapes.empty()){
            g->setShapes(shapes);
        }
    }
    else if(!strcmp(element->Name(),"colour"))
        parse_color(element, g);
    else if(!strcmp(element->Name(),"group")) {
        Group *childGroup = child_of(g);
        element = element->FirstChildElement();
        if (element) {
            find_elements(element, childGroup);
        }
    }

    current = current->NextSiblingElement();
    if(current)
        find_elements(current,g);
}

//Reads the .3d file and returns a vector of all the vertexes found
Shape* read_file(string fileName){
    vector<Vertex*> vertex,normal,texture;
    string line;
    string pathToFile = "../files3d/" + fileName;
    int i;
    ifstream file(pathToFile);
    Shape* s;

    if (!file.fail()){
        getline(file, line);
        int n_vertexes = atoi(line.c_str());

        for (i=0; i<n_vertexes; i++) {
            getline(file,line);
            Vertex *v = new Vertex(line);
            vertex.push_back(v);
        }
        getline(file,line);
        int n_normal = atoi(line.c_str());
        for(i=0; i<n_normal; i++){
            getline(file,line);
            Vertex *v = new Vertex(line);
            normal.push_back(v);
        }

        getline(file,line);
        int n_texture = atoi(line.c_str());
        for(i=0; i<n_texture; i++){
            getline(file,line);
            Vertex *v = new Vertex(line,0);
            texture.push_back(v);
        }

        s = new Shape(vertex,normal,texture);
    }
    else {
        cout << "Failed to open file " << fileName << "." << endl;
    }

    return s;
}

//Parses through the xml file and returns the first Group found
Group* parseXML(char* fileName) {
    XMLDocument docXML;
    XMLElement *element;

    Group *group = new Group();

    if(docXML.LoadFile(fileName) == 0){
        element = docXML.FirstChildElement("scene")->FirstChildElement("group");
        find_elements(element,group);
    }
    else
        cout << "XML file \"" << fileName << "\" not found!" << endl;

    return group;
}
