#ifndef _PARSER_H
#define _PARSER_H


#include "../src/Group.h"
#include "tinyxml2.h"

using namespace tinyxml2;

Group* child_of(Group*);
void parse_translation(XMLElement*, Group*);
void parse_rotation(XMLElement*, Group*);
void parse_scale(XMLElement*, Group*);
void parse_color(XMLElement*, Group*);
vector<Shape*> parse_models(XMLElement*);
void find_elements(XMLElement*, Group*);
Shape* read_file(string);
Group* parseXML(char*);

#endif
