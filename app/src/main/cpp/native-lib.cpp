#include <jni.h>
#include <GLES3/gl3.h>
#include "Shape.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include "shader.h"
#include "camera.h"
#include "model.h"

Camera camera(glm::vec3(0.0f,0.0f,3.0f));


//Shader mShader;
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
float cubeNormal[]={
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,

         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,

         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,

         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f

};
float cubeTexCoords[]={
         0.0f, 0.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,

         0.0f, 0.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,

         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
         1.0f, 0.0f,

         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
         1.0f, 0.0f,

         0.0f, 1.0f,
         1.0f, 1.0f,
         1.0f, 0.0f,
         1.0f, 0.0f,
         0.0f, 0.0f,
         0.0f, 1.0f,

         0.0f, 1.0f,
         1.0f, 1.0f,
         1.0f, 0.0f,
         1.0f, 0.0f,
         0.0f, 0.0f,
         0.0f, 1.0f
};

float planeVertices[]={
          2.0f,-0.8f,2.0f,
         -2.0f,-0.8f,2.0f,
         -3.0f,-0.6f,-2.0f,
         2.0f,-0.8f,2.0f,
         3.0f,-0.6f,-2.0f,
         -3.0f,-0.6f,-2.0f,
};
float planeTexCoords[]={
};
float planeNormal[]={};


Shape mShape(cubeVertices,cubeTexCoords,cubeNormal);
Shape mPlane(planeVertices,planeTexCoords,planeNormal);
using namespace std;

extern "C"
{
JNIEXPORT void JNICALL
Java_com_example_xinli_myapplication_MyRenderer_nativeInit(
        JNIEnv *env,
        jclass type,
        jstring vertexShaderCode_,
        jstring fragmentShaderCode_,
        jstring vertexShaderCode_skybox,
        jstring fragmentShaderCode_skybox,
        jstring vertexShaderCode_Model,
        jstring fragmentShaderCode_Model/* this */) {

    const char *vertexShaderCode = env->GetStringUTFChars(vertexShaderCode_, 0);
    const char *fragmentShaderCode = env->GetStringUTFChars(fragmentShaderCode_, 0);
    const char *vertexShaderCodeSkybox = env->GetStringUTFChars(vertexShaderCode_skybox, 0);
    const char *fragmentShaderCodeSkybox = env->GetStringUTFChars(fragmentShaderCode_skybox, 0);
    const char *vertexShaderCodeModel=env->GetStringUTFChars(vertexShaderCode_Model,0);
    const char *fragmentShaderCodeModel=env->GetStringUTFChars(fragmentShaderCode_Model,0);


    //mShape.initGL(vertexShaderCode, fragmentShaderCode,"sdcard/image/front.jpg");
    mPlane.initGL(vertexShaderCodeSkybox,fragmentShaderCodeSkybox,"");
    mShape.initGL(vertexShaderCode, fragmentShaderCode,"sdcard/image/front.jpg");

    env->ReleaseStringUTFChars(vertexShaderCode_, vertexShaderCode);
    env->ReleaseStringUTFChars(fragmentShaderCode_, fragmentShaderCode);
    env->ReleaseStringUTFChars(vertexShaderCode_skybox, vertexShaderCodeSkybox);
    env->ReleaseStringUTFChars(fragmentShaderCode_skybox, fragmentShaderCodeSkybox);
    env->ReleaseStringUTFChars(vertexShaderCode_Model, vertexShaderCodeModel);
    env->ReleaseStringUTFChars(fragmentShaderCode_Model, fragmentShaderCodeModel);

    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
    //glDisable(GL_DEPTH_TEST);

}


JNIEXPORT void JNICALL
Java_com_example_xinli_myapplication_MyRenderer_nativeDraw(
        JNIEnv *env,jclass type, jfloat xoffset, jfloat yoffset
){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    camera.ProcessMouseMovement(xoffset, yoffset);
    glm::mat4 mvpMatrix;
    float *mvp;

    model=glm::mat4();
    model=glm::scale(model,glm::vec3(0.5f,0.5f,0.5f));
    model=glm::rotate(model,glm::radians(180.0f),glm::vec3(1.0f,0.0f,0.0f));
    //model=glm::translate(model,glm::vec3(0.0f,3.0f,0.0f));*/
    //model=glm::rotate(model,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));

    view=camera.GetViewMatrix();
    mvpMatrix=projection*view*model;
    mvp=(float *) glm::value_ptr(mvpMatrix);
    //
    mShape.draw(mvp,36);

    model=glm::mat4();
    mvpMatrix=projection*view*model;
    mvp=(float *) glm::value_ptr(mvpMatrix);
    mPlane.draw(mvp,6);
}

JNIEXPORT void JNICALL
Java_com_example_xinli_myapplication_MyRenderer_nativeSurfaceChanged(JNIEnv *env,
jclass type, jint width,jint height)
{
    model=glm::rotate(model,glm::radians(0.0f),glm::vec3(0.0f,0.0f,1.0f));
    projection=glm::perspective(glm::radians(camera.Zoom),(float)width/height,0.1f,100.0f);

    glViewport(0,0,width,height);
}
}