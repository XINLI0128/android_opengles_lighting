//
// Created by xinli on 17-10-10.
//

#ifndef MYAPPLICATION_SHAPE_H
#define MYAPPLICATION_SHAPE_H



#include <GLES3/gl3.h>
#include "shader.h"
#include <string>

using namespace std;

#define PI 3.1415926

class Shape
{
public:
    GLuint textureID;
    GLint mTexture;
    GLint mTexture1;
    GLint mProgram;
    GLint mUMVPMatrixHandle;
    GLint mAPositionHandle;
    GLint mANormalHandle;
    GLint mATexCoordsHandle;
    GLfloat *mVertexArray;
    GLfloat *mTexArray;
    GLfloat *mNormalArray;
    Shape(float *vertexArray, float *texCoordsArray,float *normalArray);
    void initVertex(float *vertexArray, float *texCoordsArray,float *normalArray);
    void initGL(const char * vertexShaderCode, const char * fragmentShaderCode, const string texture_path);
    void draw(float mvpMatrix[],int i);
    void loadTexture(string s);
    virtual ~Shape();
    Shader shader;

};
#endif //MYAPPLICATION_SHAPE_H
