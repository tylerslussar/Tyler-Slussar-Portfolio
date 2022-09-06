//
//  ColoredPointDrawable.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include "GLFW/glfw3.h"
#include "ColoredPointDrawable.hpp"

ShaderProgram ColoredPointDrawable::_shaderProgram;

ColoredPointDrawable::ColoredPointDrawable(const std::vector<ColoredPoint3D> &pts, const GLfloat pointSize, const mat4 &objectTransformation) {
    _numPoints = (unsigned int) pts.size();
    _pointSize = pointSize;
    // _numPoints * 6 since x, y, z, r, g, b for each point
    auto points = std::make_unique<float[]>(_numPoints * 6);
    size_t index = 0;
    for (auto i = 0; i<pts.size(); ++i) {
        points[index++] = pts[i].x;
        points[index++] = pts[i].y;
        points[index++] = pts[i].z;
        points[index++] = pts[i].r;
        points[index++] = pts[i].g;
        points[index++] = pts[i].b;    }
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, _numPoints * 6 * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
    _drawType = GL_POINTS;
    _objectMatrix = objectTransformation;
}

ColoredPointDrawable::~ColoredPointDrawable() noexcept {
    glDeleteBuffers(1, &_buffer);
}

void ColoredPointDrawable::render(const mat4 &projectionEyeMatrix) {
    _shaderProgram.useProgram();
    shaderTransformations(_shaderProgram, projectionEyeMatrix, _objectMatrix);
    
    glPointSize(_pointSize);
    // layout value for vPosition
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));

    glDrawArrays(_drawType, 0, _numPoints);
}

void ColoredPointDrawable::setShaderProgram(const ShaderProgram &shaderProgram) {
    _shaderProgram = shaderProgram;
}

