//
//  ShaderProgram.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <string>

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/freeglut.h>
#endif

#include "GLFW/glfw3.h"


class ShaderProgram {
    
public:
    /// create a shaderProgram
    ShaderProgram() { _program = _programCounter++; }

    /// make the vertex and fragement shaders from specified files
    /// @param vertexShaderFilePath  path to vertex shader
    /// @param fragmentShaderFilePath  path to fragment shader
    void makeProgramFromShaderFiles(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

    /// make vertex and fragment shader from specified strings
    /// @param vertexShader string containing vertex shader
    /// @param fragmentShader string containing fragment shader
    void makeProgramFromShaderStrings(std::string vertexShader, std::string fragmentShader);

    /// helper method to compile a shader
    /// @param shaderCode string containing shader
    /// @param shaderType GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
    void compileShader(std::string shaderCode, GLenum shaderType) const;

    /// return the OpenGL shader identifier
    GLuint program() const { return _program; }

    /// use this ShaderProgram to render
    void useProgram() const { glUseProgram(_program); }

protected:
    GLuint _program;
private:
    static GLuint _programCounter;
};

#endif /* ShaderProgram_hpp */
