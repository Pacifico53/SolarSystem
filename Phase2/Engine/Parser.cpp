#include <iostream>
#include <fstream>
#include <sstream>
#include "Parser.h"

int total = 0;

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
            vector<Vertex*> verts = read_file(modelName);
            Shape *s = new Shape(verts);
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
vector<Vertex*> read_file(string fileName){
    vector<Vertex*> result;
    string line;
    string pathToFile = "../files3d/" + fileName;

    ifstream file(pathToFile);

    if (!file.fail()){
        while(getline(file, line)){
            Vertex *v = new Vertex(line);
            result.push_back(v);
        }
    }
    else {
        cout << "Failed to open file " << fileName << "." << endl;
    }

    return result;
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
