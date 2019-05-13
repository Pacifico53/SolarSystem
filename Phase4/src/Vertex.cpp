#include "Vertex.h"

Vertex::Vertex(){
    x=0;
    y=0;
    z=0;
}

Vertex::Vertex(float xx, float yy, float zz){
    x = xx;
    y = yy;
    z = zz;
}

Vertex::Vertex(std::string str){
    size_t pos;

    x = std::stof(str,&pos);
    str.erase(0,pos+1);
    y = std::stof(str,&pos);
    str.erase(0,pos+1);
    z = std::stof(str,&pos);
}

Vertex::Vertex(std::string str, float zz){
    size_t pos;

    x = std::stof(str,&pos);
    str.erase(0,pos+1);
    y = std::stof(str,&pos);

    z = zz;

}

float Vertex::getX(){
    return x;
}

float Vertex::getY(){
    return y;
}

float Vertex::getZ(){
    return z;
}
