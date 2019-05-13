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

//Reads the .3d file and returns a vector of all the vertexes found
Shape* read_file(string fileName) {
    string line;
    string pathToFile = "../files3d/" + fileName;

    vector<Vertex*> vertexes;
    vector<Vertex*> normals;
    vector<Vertex*> textures;

    int i = 0;

    ifstream file(pathToFile);

    if (!file.fail()){
        getline(file, line);
        int size_vertex = atoi(line.c_str());

        for (i = 0; i < size_vertex; i++) {
            getline(file, line);
            Vertex* vv = new Vertex(line);
            vertexes.push_back(vv);
        }

        getline(file, line);
        int size_normals = atoi(line.c_str());

        for (i = 0; i < size_normals; i++) {
            getline(file, line);
            Vertex* vn = new Vertex(line);
            normals.push_back(vn);
        }

        getline(file, line);
        int size_textures = atoi(line.c_str());

        for (i = 0; i < size_textures; i++) {
            getline(file, line);
            Vertex* vt = new Vertex(line);
            textures.push_back(vt);
        }
    }
    else {
        cout << "Failed to open file " << fileName << "." << endl;
    }

    file.close();
    Shape* result = new Shape(vertexes, normals, textures);

    return result;
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
