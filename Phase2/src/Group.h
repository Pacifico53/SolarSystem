//
// Created by pacifico on 18-03-2019.
//

#ifndef _GROUP_H
#define _GROUP_H

#include "Shape.h"
#include "Action.h"

class Group {

    vector<Shape*> shapes;      // Shapes
    vector<Group*> groups;      // Children of parent group
    vector<Action*> actions;    //Actions

    public:
        Group();
        Group(vector<Shape*>,vector<Group*>,vector<Action*>);
        vector<Shape*> getShapes();
        vector<Group*> getChildren();
        vector<Action*> getActions();
        void setShapes(vector<Shape*>);
        void setChilds(vector<Group*>);
        void setActions(vector<Action*>);
        void addShape(Shape*);
        void addChild(Group*);
        void addAction(Action*);
};

#endif
