//
// Created by pacifico on 14-05-2019.
//

#include "Material.h"
#include <GL/glut.h>

Material::Material() = default;

Material::Material(float *diff, float *amb, float *spec, float *emi, float shin) {
    for (int i = 0; i < 4; i++) {
        diffuse[i] = diff[i];
        ambient[i] = amb[i];
        specular[i] = spec[i];
        emission[i] = emi[i];
    }

    shininess = shin;
}

void Material::draw(){
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    if(diffuse[3] != -1)
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);

    if(ambient[3] != -1)
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);

    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emission);
}
