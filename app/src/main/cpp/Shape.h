//
// Created by xinli on 17-10-10.
//

#ifndef MYAPPLICATION_SHAPE_H
#define MYAPPLICATION_SHAPE_H



#include <GLES3/gl3.h>
#include "shader.h"
#include <string>
#include "camera.h"

using namespace std;

#define PI 3.1415926

class Shape
{
public:
    GLuint textureID;

    GLuint mTexture;
    GLint mTexture1;
    GLint viewPosHandle;
    GLint lightPosHandle;
    GLuint depthMapFBO;
    GLint mProgram;
    GLint modelHandle;
    GLint viewHandle;
    GLint projectionHandle;
    GLint mAPositionHandle;
    GLint mANormalHandle;
    GLint mATexCoordsHandle;
    GLfloat *mVertexArray;
    GLfloat *mTexArray;
    GLfloat *mNormalArray;
    Shape(float *vertexArray, float *texCoordsArray,float *normalArray);
    void initVertex(float *vertexArray, float *texCoordsArray,float *normalArray);
    void initGL(const char * vertexShaderCode, const char * fragmentShaderCode, const string texture_path);
    void draw(float *model,float *view, float *projection,Camera camera,int i);
    void loadTexture(string s);
    void loadTexture();
    virtual ~Shape();
    Shader shader;

};
#endif //MYAPPLICATION_SHAPE_H
