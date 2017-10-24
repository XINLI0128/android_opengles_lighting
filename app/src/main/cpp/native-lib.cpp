#include <jni.h>
#include <GLES3/gl3.h>
#include "Shape.h"
#include "glm/mat4x4.hpp"
#include "glm/ext.hpp"
#include "shader.h"
#include "camera.h"
#include "model.h"
#include "depth.h"

Depth depth;
//-2.0,3.0,2.0
Camera camera(glm::vec3(0.0f,0.0f,3.0f));
Model Airplane;

//Shader mShader;
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;
int Height,Width;
float cubeVertices[] = {
        // positions
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
          2.0f,-0.6f,2.0f,
         -2.0f,-0.6f,2.0f,
         -2.0f,-0.6f,-2.0f,
          2.0f,-0.6f,2.0f,
          2.0f,-0.6f,-2.0f,
         -2.0f,-0.6f,-2.0f,
};
float planeTexCoords[]={
};
float planeNormal[]={         0.0f,  1.0f,  0.0f,
                              0.0f,  1.0f,  0.0f,
                              0.0f,  1.0f,  0.0f,
                              0.0f,  1.0f,  0.0f,
                              0.0f,  1.0f,  0.0f,
                              0.0f,  1.0f,  0.0f
                     };

float quadVertices[]={
        -1.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
         1.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
         1.0f,1.0f,0.0f,
         1.0f,-1.0f,0.0f
         };

float quadTexCoords[]={0.0f,1.0f,
                       0.0f,0.0f,
                       1.0f,1.0f,
                       0.0f,0.0f,
                       1.0f,1.0f,
                       1.0f,0.0f
                       };
float quadNormal[]={};

Shape mShape(cubeVertices,cubeTexCoords,cubeNormal);
Shape mPlane(planeVertices,planeTexCoords,planeNormal);
Shape mQuad(quadVertices,quadTexCoords,quadNormal);
Shape mLight(cubeVertices,cubeTexCoords,cubeNormal);



Camera light_camera(glm::vec3(0.0f,1.0f,0.0f));
glm::vec3 lightPos(1.0f,1.0f,0.0f); //-2.0,3.0,2.0

GLint depthMapFBO;

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
        jstring fragmentShaderCode_Model,
        jstring vertexShaderCode_light,
        jstring fragmentShaderCode_light/* this */) {


    const char *vertexShaderCode = env->GetStringUTFChars(vertexShaderCode_, 0);
    const char *fragmentShaderCode = env->GetStringUTFChars(fragmentShaderCode_, 0);
    const char *vertexShaderCodeSkybox = env->GetStringUTFChars(vertexShaderCode_skybox, 0);
    const char *fragmentShaderCodeSkybox = env->GetStringUTFChars(fragmentShaderCode_skybox, 0);
    const char *vertexShaderCodeModel=env->GetStringUTFChars(vertexShaderCode_Model,0);
    const char *fragmentShaderCodeModel=env->GetStringUTFChars(fragmentShaderCode_Model,0);
    const char *vertexShaderCodeLight=env->GetStringUTFChars(vertexShaderCode_light,0);
    const char *fragmentShaderCodeLight=env->GetStringUTFChars(fragmentShaderCode_light,0);

    depthMapFBO=depth.createBuffer();


    //mShape.initGL(vertexShaderCode, fragmentShaderCode,"sdcard/image/front.jpg");
    mPlane.initGL(vertexShaderCodeSkybox,fragmentShaderCodeSkybox,"");
    mShape.initGL(vertexShaderCode, fragmentShaderCode,"");
    //Airplane.initGL(vertexShaderCodeModel,fragmentShaderCodeModel);
    //Airplane.Create("/sdcard/image/FREOBJ.obj");
    mQuad.initGL(vertexShaderCodeModel,fragmentShaderCodeModel,"");
    mLight.initGL(vertexShaderCodeLight,fragmentShaderCodeLight,"");


    env->ReleaseStringUTFChars(vertexShaderCode_, vertexShaderCode);
    env->ReleaseStringUTFChars(fragmentShaderCode_, fragmentShaderCode);
    env->ReleaseStringUTFChars(vertexShaderCode_skybox, vertexShaderCodeSkybox);
    env->ReleaseStringUTFChars(fragmentShaderCode_skybox, fragmentShaderCodeSkybox);
    env->ReleaseStringUTFChars(vertexShaderCode_Model, vertexShaderCodeModel);
    env->ReleaseStringUTFChars(fragmentShaderCode_Model, fragmentShaderCodeModel);
    env->ReleaseStringUTFChars(vertexShaderCode_light, vertexShaderCodeLight);
    env->ReleaseStringUTFChars(fragmentShaderCode_light, fragmentShaderCodeLight);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

}


JNIEXPORT void JNICALL
Java_com_example_xinli_myapplication_MyRenderer_nativeDraw(
        JNIEnv *env,jclass type, jfloat xoffset, jfloat yoffset
){  //float AngleX, float AngleY,boolean flag)
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    camera.ProcessMouseMovement(xoffset, yoffset);
    glm::mat4 mvpMatrix;
    float *mvp;
    glm::mat4 lightProjection,lightView;
    glm::mat4 lightSpaceMatrix;
    float near_plane=1.0f,far_plane=7.5f;
    lightProjection=glm::ortho(-2.0f,2.0f,-2.0f,2.0f,near_plane,far_plane);
    lightView=glm::lookAt(lightPos,glm::vec3(0.0f),glm::vec3(1.0,0.0,0.0));
    //lightView=light_camera.GetViewMatrix();
    lightSpaceMatrix=lightProjection*lightView;

    model=glm::mat4();
    model=glm::scale(model,glm::vec3(0.5f,0.5f,0.5f));
    //model=glm::rotate(model,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));

    /*if(flag==true)
    model=glm::rotate(model,glm::radians(AngleX),glm::vec3(0.0f,1.0f,0.0f));
    else
    model=glm::rotate(model,glm::radians(AngleY),glm::vec3(1.0f,0.0f,0.0f));*/
    //model=glm::rotate(model,glm::radians(90.0f),glm::vec3(1.0f,0.0f,0.0f));

    view=camera.GetViewMatrix();
    mvpMatrix=projection*view*model;
    mvp=(float *) glm::value_ptr(mvpMatrix);
    //view=glm::mat4();


    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,Width,Height);
    glBindFramebuffer(GL_FRAMEBUFFER,mQuad.depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        mShape.draw((float *)glm::value_ptr(model),(float *)glm::value_ptr(lightView),(float *)glm::value_ptr(lightProjection),light_camera,36);


        model=glm::mat4();
        mvpMatrix=projection*view*model;
        mvp=(float *) glm::value_ptr(mvpMatrix);
        mPlane.draw((float *)glm::value_ptr(model),(float *)glm::value_ptr(lightView),(float *)glm::value_ptr(lightProjection),light_camera,6);


        //model=glm::translate(model,glm::vec3(lightPos.x,lightPos.y,lightPos.z));
        //model=glm::scale(model,glm::vec3(0.1f,0.1f,0.1f));
        //mLight.draw((float *)glm::value_ptr(model),(float *)glm::value_ptr(view),(float *)glm::value_ptr(lightProjection),light_camera,6);
    glBindFramebuffer(GL_FRAMEBUFFER,0);

    /*glViewport(0,0,Width,Height);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D,depth.depthMap);

    model=glm::mat4();
    mQuad.draw((float *)glm::value_ptr(model),(float *)glm::value_ptr(view),(float *)glm::value_ptr(projection),camera,6);*/

}

JNIEXPORT void JNICALL
Java_com_example_xinli_myapplication_MyRenderer_nativeSurfaceChanged(JNIEnv *env,
jclass type, jint width,jint height)
{
    model=glm::rotate(model,glm::radians(0.0f),glm::vec3(0.0f,0.0f,1.0f));
    projection=glm::perspective(glm::radians(camera.Zoom),(float)width/height,0.0f,100.0f);
    //projection=glm::mat4();
    //projection=glm::ortho(-2.0f,2.0f,-2.0f,2.0f,0.1f,100.0f);


    glViewport(0,0,width,height);
    Width=width;
    Height=height;
}
}