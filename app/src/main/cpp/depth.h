//
// Created by xinli on 17-10-23.
//

#ifndef MYAPPLICATION2_DEPTH_H
#define MYAPPLICATION2_DEPTH_H

class Depth
{
     const GLuint SHADOW_WIDTH=1024,SHADOW_HEIGHT=1024;
     //GLint depthMapFBO;
     public:
        GLuint depthMap;


     GLint createBuffer()
     {
        GLuint depthMapFBO;
        glGenFramebuffers(1,&depthMapFBO);
        glBindFramebuffer(GL_FRAMEBUFFER,depthMapFBO);



        //GLint depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,depthMap,0);

        //glDrawBuffer(GL_NONE);
        //glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER,0);

         return depthMapFBO;
      }



};
#endif //MYAPPLICATION2_DEPTH_H
