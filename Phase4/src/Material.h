#ifndef GENERATOR_MATERIAL_H
#define GENERATOR_MATERIAL_H

class Material {
    float diffuse[4] = {0.8, 0.8, 0.8, 1};
    float ambient[4] = {0.2, 0.2, 0.2, 1};
    float specular[4] = {0, 0, 0, 1};
    float emission[4] = {0, 0, 0, 1};
    float shininess = 0;

    public:
        Material();
        Material(float *, float *, float *, float *, float);
        void draw();
};

#endif //GENERATOR_MATERIAL_H
