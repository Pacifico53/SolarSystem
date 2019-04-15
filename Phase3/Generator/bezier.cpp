#include "bezier.h"

using namespace std;

int number_patches;
int** patches;
Shape* model = new Shape();
vector<Vertex*> control_points;

Shape* parseBezier(string filename, int tesselation){
    string line, token;
    int pos;
    ifstream file(filename);

    if (file.fail()) {
        cout << "File \"" << filename << "\" not found!" << endl;
    } else {
        getline(file, line);

        number_patches = stoi(line);
        patches = new int*[number_patches];

        for (int i = 0; i != number_patches; i++) {
            getline(file, line);
            patches[i] = new int[16];

            for (int j = 0; j < 16; j++) {
                pos = line.find(',');
                token = line.substr(0, pos);
                patches[i][j] = atoi(token.c_str());
                line.erase(0, pos + 1);
            }
        }

        getline(file, line);

        while (getline(file, line)) {
            Vertex *v = new Vertex(line);
            control_points.push_back(v);
        }

        for (int i = 0; i != number_patches; i++) {
            processPatch(tesselation, i);
        }
    }

    return model;
}

void processPatch(int tess, int n) {
    float inc = 1.0 / tess, u, v, u2, v2;

    for (int i = 0; i < tess; i++) {
        for (int j = 0; j < tess; j++) {
            u = i * inc;
            v = j * inc;
            u2 = (i + 1) * inc;
            v2 = (j + 1) * inc;

            Vertex *p1 = bezierCalc(u,v,n);
            Vertex *p2 = bezierCalc(u,v2,n);
            Vertex *p3 = bezierCalc(u2,v,n);
            Vertex *p4 = bezierCalc(u2,v2,n);

            model->pushVertex(p1);
            model->pushVertex(p3);
            model->pushVertex(p4);

            model->pushVertex(p1);
            model->pushVertex(p4);
            model->pushVertex(p2);
        }
    }
}


Vertex* bezierCalc(float u, float v, int patch_num){
    float bz_points[4][3], result[4][3];
    int k=0, j=0;

    for(int i = 0; i < 16; i++){
        Vertex* cp = control_points.at(patches[patch_num][i]);

        bz_points[j][0] = cp->getX();
        bz_points[j][1] = cp->getY();
        bz_points[j][2] = cp->getZ();

        j++;
        if( j == 4){
            Vertex *v = vertexCalc(u, bz_points[0], bz_points[1], bz_points[2], bz_points[3]);

            result[k][0] = v->getX();
            result[k][1] = v->getY();
            result[k][2] = v->getZ();

            k++;
            j=0;
        }
    }

    return vertexCalc(v, result[0], result[1], result[2], result[3]);
}

Vertex* vertexCalc(float t, float p1[3], float p2[3], float p3[3], float p4[3]){
    float x, y, z;

    float b0 = (1 - t) * (1 - t) * (1 - t);
    float b1 = 3 * t * (1 - t) * (1 - t);
    float b2 = 3 * t * t * (1 - t);
    float b3 = t * t * t;

    x = b0*p1[0] + b1*p2[0] + b2*p3[0] + b3*p4[0];
    y = b0*p1[1] + b1*p2[1] + b2*p3[1] + b3*p4[1];
    z = b0*p1[2] + b1*p2[2] + b2*p3[2] + b3*p4[2];

    return (new Vertex(x, y, z));
}
