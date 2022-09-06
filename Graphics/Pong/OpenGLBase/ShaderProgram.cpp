//
//  ShaderProgram.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef __APPLE__
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <iostream>
#include "Utils.hpp"

#include "ShaderProgram.hpp"

using std::cerr;
using std::endl;
using std::string;

GLuint ShaderProgram::_programCounter = 0;

//----------------------------------------------------------------------

void ShaderProgram::makeProgramFromShaderFiles(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
    string vertexShader = contentsOfFile(vertexShaderFilePath);
    string fragmentShader = contentsOfFile(fragmentShaderFilePath);
    makeProgramFromShaderStrings(vertexShader, fragmentShader);
}

//----------------------------------------------------------------------

void ShaderProgram::makeProgramFromShaderStrings(std::string vertexShader, std::string fragmentShader) {
    // delete the old program
    if (_program != 0) {
        glDeleteProgram(_program);
    }

    // create and compile the vertex and fragment shaders
    _program = glCreateProgram();
    compileShader(vertexShader, GL_VERTEX_SHADER);
    compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    // link  and error check
    glLinkProgram(_program);
    GLint linked;
    glGetProgramiv(_program, GL_LINK_STATUS, &linked);

    // error checking
    if (!linked) {
        std::cerr << "Shader program failed to link" << std::endl;

        GLint  logSize;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logSize);
        if (logSize > 0) {
            char* logMsg = new char[logSize];
            glGetProgramInfoLog(_program, logSize, NULL, logMsg);
            std::cerr << logMsg << std::endl;
            delete [] logMsg;
        }
    }
}

//----------------------------------------------------------------------

void ShaderProgram::compileShader(std::string shaderCode, GLenum shaderType) const {
    GLuint shader = glCreateShader(shaderType);

    const char *shaderString = shaderCode.c_str();
    glShaderSource(shader, 1, (const GLchar **)&shaderString, NULL);
    glCompileShader(shader);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    // error checking
    if (!compiled) {
        cerr << "Failed to compile shader code:\n\n" << shaderCode << endl;
        GLint  logSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        char* logMsg = new char[logSize];
        glGetShaderInfoLog( shader, logSize, NULL, logMsg);
        std::cerr << logMsg << std::endl;
        delete [] logMsg;
        return;
    }

    // attach shader to program and deallocate
    glAttachShader(_program, shader);
    glDeleteShader(shader);
}

//----------------------------------------------------------------------

