//
// Created by pacifico on 18-03-2019.
//

#ifndef _GROUP_H
#define _GROUP_H

#include "Shape.h"
#include "Action.h"
#include "Light.h"

class Group {
    vector<Shape*> shapes;      // Shapes
    vector<Group*> groups;      // Children of parent group
    vector<Action*> actions;    //Actions
    vector<Light*> lights;      //Lights

    public:
        Group();
        Group(vector<Shape*>,vector<Group*>,vector<Action*>, vector<Light*>);
        vector<Shape*> getShapes();
        vector<Group*> getChildren();
        vector<Action*> getActions();
        vector<Light*> getLights();
        void setShapes(vector<Shape*>);
        void setChilds(vector<Group*>);
        void setActions(vector<Action*>);
        void setLights(vector<Light*>);
        void addShape(Shape*);
        void addChild(Group*);
        void addAction(Action*);
};

#endif
