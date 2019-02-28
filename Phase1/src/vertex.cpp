#include "vertex.h"

vertex::vertex(){
    x=0;
    y=0;
    z=0;
}

vertex::vertex(float xx, float yy, float zz){
    x = xx;
    y = yy;
    z = zz;
}

vertex::vertex(std::string str){
    size_t pos;

    x = std::stof(str,&pos);
    str.erase(0,pos+1);
    y = std::stof(str,&pos);
    str.erase(0,pos+1);
    z = std::stof(str,&pos);
}

float vertex::getX(){
    return x;
}

float vertex::getY(){
    return y;
}

float vertex::getZ(){
    return z;
}
