#ifndef RESOURCELOADER_H
#define RESOURCELOADER_H

#include "GL/glew.h"

#include <QFile>
#include <QGLShaderProgram>

/**
   A resource loader with code to handle loading models, skyboxes, and shader programs.

  @author: Justin Ardini (jardini)
   **/
namespace ResourceLoader
{
    // Returns the skybox ID
    GLuint loadSkybox();
    std::string loadResourceFileToString(const std::string &resourcePath);

    // These return a new QGLShaderProgram.  THIS MUST BE DELETED BY THE CALLER.
    QGLShaderProgram * newVertShaderProgram(const QGLContext *context, QString vertShader);
    QGLShaderProgram * newFragShaderProgram(const QGLContext *context, QString fragShader);
    QGLShaderProgram * newShaderProgram(const QGLContext *context, QString vertShader, QString fragShader, QString *errors = 0);

    // Returns the cubeMap ID
    GLuint loadCubeMap(QList<QFile *> files);

    void initializeGlew();

    GLuint createShaderProgram(const char * vertex_file_path,const char * fragment_file_path);
    GLuint createShader(GLenum shaderType, const char *filepath);
}

#endif // RESOURCELOADER_H
