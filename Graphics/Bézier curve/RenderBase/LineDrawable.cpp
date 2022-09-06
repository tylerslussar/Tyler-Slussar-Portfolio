//
//  LineDrawable.cpp
//  ComputerGraphics
//
//  Created by David M. Reed on 11/11/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#include "LineDrawable.hpp"

ShaderProgram LineDrawable::_shaderProgram;

LineDrawable::LineDrawable(const std::vector<Line3D> lines, const Color &color, const mat4 &objectTransformation) {
    _numLines = (unsigned int) lines.size();
    _color = color;
    // _numPoints * 6 since x, y, z for each end point of each line
    auto points = std::make_unique<float[]>(_numLines * 6);
    size_t index = 0;
    for (auto i = 0; i<lines.size(); ++i) {
        Point3D p1 = lines[i].p1();
        Point3D p2 = lines[i].p2();
        points[index++] = p1.x;
        points[index++] = p1.y;
        points[index++] = p1.z;
        points[index++] = p2.x;
        points[index++] = p2.y;
        points[index++] = p2.z;
    }
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, _numLines * 6 * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
    _objectMatrix = objectTransformation;
}

LineDrawable::~LineDrawable() noexcept { 
    glDeleteBuffers(1, &_buffer);
}

void LineDrawable::render(const mat4 &projectionEyeMatrix) { 
    _shaderProgram.useProgram();
    shaderTransformations(_shaderProgram, projectionEyeMatrix, _objectMatrix);
    
    // layout value for vPosition
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    auto colorLocation = glGetUniformLocation(_shaderProgram.program(), "pointColor");
    glUniform3f(colorLocation, _color.r, _color.g, _color.b);
    // pass number of points so 2 * _numLines
    glDrawArrays(GL_LINES, 0, 2 * _numLines);
}

void LineDrawable::setShaderProgram(const ShaderProgram &shaderProgram) { 
    _shaderProgram = shaderProgram;
}
