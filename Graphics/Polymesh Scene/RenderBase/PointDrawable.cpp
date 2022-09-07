//
//  PointDrawable.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#include "PointDrawable.hpp"

ShaderProgram PointDrawable::_shaderProgram;

PointDrawable::PointDrawable(const std::vector<Point3D> &pts, const Color &color, const GLfloat pointSize, const mat4 objectTransformation) {
    _numPoints = (unsigned int) pts.size();
    _color = color;
    _pointSize = pointSize;
    // _numPoints * 3 since x, y, z for each point
    auto points = std::make_unique<float[]>(_numPoints * 3);
    size_t index = 0;
    for (auto i = 0; i<pts.size(); ++i) {
        points[index++] = pts[i].x;
        points[index++] = pts[i].y;
        points[index++] = pts[i].z;
    }
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, _numPoints * 3 * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
    _drawType = GL_POINTS;
    _objectMatrix = objectTransformation;
}

PointDrawable::~PointDrawable() noexcept {
    glDeleteBuffers(1, &_buffer);
}

void PointDrawable::render(const mat4 &projectionEyeMatrix) {
    _shaderProgram.useProgram();
    shaderTransformations(_shaderProgram, projectionEyeMatrix, _objectMatrix);

    glPointSize(_pointSize);
    // layout value for vPosition
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    auto colorLocation = glGetUniformLocation(_shaderProgram.program(), "pointColor");
    glUniform3f(colorLocation, _color.r, _color.g, _color.b);
    glDrawArrays(_drawType, 0, _numPoints);
}

void PointDrawable::setShaderProgram(const ShaderProgram &shaderProgram) {
    _shaderProgram = shaderProgram;
}

