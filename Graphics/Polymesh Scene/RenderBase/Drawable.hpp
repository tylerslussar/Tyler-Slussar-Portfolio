//
//  Drawable.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef Drawable_hpp
#define Drawable_hpp

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "ShaderProgram.hpp"
#include "Angel.hpp"

/// abstract class for drawable objects the Renderer class will render
class Drawable {
public:
    Drawable() { _objectMatrix = mat4(); }

    virtual ~Drawable() {}

    /// set object transformation for drawable
    /// @param transform object transformation to use
    void setObjectTransformation(const mat4 &transform) {
        _objectMatrix = transform;
    }

    /// return object transformation for drawable
    mat4 objectTransformation() const { return _objectMatrix; }

    /// render with specified projection and eye transformation matrix
    virtual void render(const mat4 &projectionEyeMatrix) = 0;

    /// default method to set matrices in shaders
    /// @param shaderProgram the shader program
    /// @param projectionEyeMatrix projection and eye transformation
    /// @param objectMatrix object transformation
    void shaderTransformations(const ShaderProgram &shaderProgram, const mat4 &projectionEyeMatrix, const mat4 objectMatrix);

protected:
    // default OpenGL option for drawing
    GLenum _drawType = GL_POINTS;
    // transformation matrix
    mat4 _objectMatrix;
};

inline void Drawable::shaderTransformations(const ShaderProgram &shaderProgram, const mat4 &projectionEyeMatrix, const mat4 objectMatrix) {
    GLuint projectionEye = glGetUniformLocation(shaderProgram.program(), "projectionEyeMatrix");
    GLuint object = glGetUniformLocation(shaderProgram.program(), "objectMatrix");

    glUniformMatrix4fv(projectionEye, 1, GL_TRUE, projectionEyeMatrix);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
}

#endif /* Drawable_hpp */
