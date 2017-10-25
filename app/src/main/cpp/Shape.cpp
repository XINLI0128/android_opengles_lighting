//
// Created by xinli on 17-10-10.
//#define STB_IMAGE_IMPLEMENTATION
#include "Shape.h"
#include <math.h>
#include "mesh.h"
#include <stb_image.h>


void Shape::loadTexture(const string s)
{

    glGenTextures(1,&textureID);
    //glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textureID);
    int height, width, nChannels;
    unsigned char * data=stbi_load(s.c_str(), &width, &height, &nChannels,0);
    if(data)
    {
        LOGI(1,"SUCCEED TO LOAD TEXTURE");
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    LOGI(1,"FAILED TO LOAD TEXTURE");
}


void Shape::loadTexture()
{
               const GLuint SHADOW_WIDTH=1024,SHADOW_HEIGHT=1024;
               //GLuint depthMapFBO;
               glGenFramebuffers(1,&depthMapFBO);
               glBindFramebuffer(GL_FRAMEBUFFER,depthMapFBO);



               //GLint depthMap;
               glGenTextures(1, &textureID);
               glBindTexture(GL_TEXTURE_2D, textureID);
               glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

               glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,textureID,0);

               //glDrawBuffer(GL_NONE);
               //glReadBuffer(GL_NONE);
               glBindFramebuffer(GL_FRAMEBUFFER,0);
}



void Shape::initVertex(float *vertexArray, float *texCoordsArray, float *normalArray) {

    mVertexArray=new GLfloat[sizeof(vertexArray)];
    mTexArray=new GLfloat[sizeof(texCoordsArray)];
    mNormalArray=new GLfloat[sizeof(normalArray)];
    mVertexArray=vertexArray;
    mTexArray=texCoordsArray;
    mNormalArray=normalArray;
}

void Shape::initGL(const char *vertexShaderCode, const char *fragmentShaderCode, const string texture_path) {

    shader.create(vertexShaderCode,fragmentShaderCode);
    mProgram=shader.getID();
    //loadTexture(texture_path);
    //loadTexture();
}


void Shape::draw(float *model,float *view, float *projection, Camera camera, int i) {

    shader.use();
     //loadTexture(texture_path);
     //loadTexture();
     viewPosHandle=glGetUniformLocation(mProgram,"viewPos");
     modelHandle=glGetUniformLocation(mProgram,"model");
     viewHandle=glGetUniformLocation(mProgram,"view");
     projectionHandle=glGetUniformLocation(mProgram,"projection");
     mAPositionHandle=glGetAttribLocation(mProgram,"aPosition");
     mATexCoordsHandle=glGetAttribLocation(mProgram,"aTexCoords");
     mANormalHandle=glGetAttribLocation(mProgram,"aNormal");
     mTexture=glGetUniformLocation(mProgram,"texture_diffuse");
     lightPosHandle=glGetUniformLocation(mProgram,"lightPos");


     glVertexAttribPointer(mAPositionHandle,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),mVertexArray);
     glVertexAttribPointer(mATexCoordsHandle,2,GL_FLOAT,GL_FALSE,2*sizeof(GLfloat),mTexArray);
     glVertexAttribPointer(mANormalHandle,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),mNormalArray);

    glUniformMatrix4fv(modelHandle,1,GL_FALSE,model);
    glUniformMatrix4fv(viewHandle,1,GL_FALSE,view);
    glUniformMatrix4fv(projectionHandle,1,GL_FALSE,projection);
    glUniform3f(lightPosHandle,camera.Position.x,camera.Position.y,camera.Position.z);
    glUniform3f(viewPosHandle,camera.Position.x,camera.Position.y,camera.Position.z);

    //glVertexAttribPointer(mAPositionHandle,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray);
    //glVertexAttribPointer(mATexCoordsHandle,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray+3*sizeof(GLfloat));
    glEnableVertexAttribArray(mAPositionHandle);
    glEnableVertexAttribArray(mATexCoordsHandle);
    glEnableVertexAttribArray(mANormalHandle);

    //glActiveTexture(GL_TEXTURE0);
    glUniform1i(mTexture,0);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawArrays(GL_TRIANGLES,0,i);

}

Shape::Shape(float *vertexArray, float *texCoordsArray, float *normalArray) {
    initVertex(vertexArray, texCoordsArray, normalArray);
}

Shape::~Shape() {
    delete [] mVertexArray;
    delete [] mTexArray;
    delete [] mNormalArray;
    //delete [] mColorArray;
}

