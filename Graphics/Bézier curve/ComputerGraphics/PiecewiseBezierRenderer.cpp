//
//  PiecewiseBezierRenderer.cpp
//  ComputerGraphics
//
//  Created by David M. Reed on 12/26/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//



#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;

#include <memory>

#include "PiecewiseBezierRenderer.hpp"

PiecewiseBezierRenderer::PiecewiseBezierRenderer(std::string windowTitle, int width, int height): Renderer(windowTitle, width, height) {
    
    // create the shaders needed
    // vertex shader for points
    string pointVShader = R"(
    #version 330 core
    
    // Input vertex data, different for all executions of this shader.
    layout(location = 0) in vec2 vPosition;
    
    uniform mat4 projectionEyeMatrix;
    // uniform mat4 objectMatrix;
    
    void main()
    {
      // vertex shader must set gl_Position
      gl_Position = projectionEyeMatrix * vec4(vPosition, 0, 1);
    }
    )";
    
    // fragment shader for points
    string pointFShader = R"(
    #version 330 core
    
    // uniform value representing polygon color
    uniform vec3 pointColor;
    
    // color to use for fragment
    out vec4 finalColor;
    
    void main()
    {
      finalColor = vec4(pointColor, 1.0);
    }
    )";
    _shaderProgram.makeProgramFromShaderStrings(pointVShader, pointFShader);
    
    // make 3 buffers
    // one for points, one for handles, and one for spline pathq
    glGenBuffers(3, _buffer);
    
    // show the points and handles by default
    _showHandles = true;
    // large points for handles
    glPointSize(12);
    // draw lines antialiased
    glEnable(GL_LINE_SMOOTH);
}

void PiecewiseBezierRenderer::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // h key toggles showing points and handles
    if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        _showHandles = !_showHandles;
    }
    // quit on escape key or q
    else if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void PiecewiseBezierRenderer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos) {
        
    _index = -1;
    
    // shift click to add a control point
    if (action == GLFW_PRESS && mods == GLFW_MOD_SHIFT) {
        _spline.addControlPointWithHandles(vec2(xPos, yPos));
    }
    
   if (action == GLFW_PRESS){
       
       // gets the index of PiecewiseBezier class instance variable _controlPoints
       _index = _spline.closeTo(xPos, yPos);
       // mouse press is true on press
       _mousePress = true;
    }
    if (action == GLFW_RELEASE){
        // mouse press is false on press
        _mousePress = false;
    }
}

void PiecewiseBezierRenderer::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    
    // if the mouse is pressed and the index is valid
    // updates the point at the index with new x and y
    if (_mousePress && _index >= 0){
        _spline.updatePoint(_index, xPos, yPos);
    }

}

void PiecewiseBezierRenderer::render() {
    int numControlPts = _spline.numControlPoints();
    // nothing to draw unless there are control points
    if (numControlPts > 0) {
        // set clear color to black
        glClearColor(0, 0, 0, 1);

        _shaderProgram.useProgram();

        // clear the window and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // make orthographic transformation that takes points in which
        // top left corner is (0, 0) and bottom right corner of window is (width, height)
        // and transforms them to bottom left (-1, 1) and top right (1, 1)
        float w = float(windowWidth());
        float h = float(windowHeight());
        mat4 projectionEyeMatrix = Translate(-1.0f, 1.0f, 0.0f) * Scale(2.0f / w, -2.0f / h, 1.0f);

        // layout value for vPosition
        // get the integer location for the vPosition attribute
        // in the vertex shader
        GLuint vertexPosition = glGetAttribLocation(_shaderProgram.program(), "vPosition");

        GLuint projectionEye = glGetUniformLocation(_shaderProgram.program(), "projectionEyeMatrix");
        glUniformMatrix4fv(projectionEye, 1, GL_TRUE, projectionEyeMatrix);

        // color location in shader
        auto colorLocation = glGetUniformLocation(_shaderProgram.program(), "pointColor");

        if (_showHandles) {

            // white color for points and handles
            glUniform3f(colorLocation, 1, 1, 1);

            // draw control points
            glBindBuffer(GL_ARRAY_BUFFER, _buffer[0]);
            glBufferData(GL_ARRAY_BUFFER, numControlPts * 2 * sizeof(GLfloat), _spline.controlPoints(), GL_STATIC_DRAW);
            glEnableVertexAttribArray(vertexPosition);
            glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
            glDrawArrays(GL_POINTS, 0, numControlPts);

            // get handles and draw them
            auto linePts = _spline.controlLines();
            glBindBuffer(GL_ARRAY_BUFFER, _buffer[1]);
            glEnableVertexAttribArray(vertexPosition);
            // one line for every three control points and four values per line (two x, y pairs)
            glBufferData(GL_ARRAY_BUFFER, numControlPts / 3 * 4 * sizeof(GLfloat), &linePts[0], GL_STATIC_DRAW);
            glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
            glDrawArrays(GL_LINES, 0, int(linePts.size()));
        }
        
        if (numControlPts >= 5){
           // red color for the spline
            glUniform3f(colorLocation, 1, 0, 0);
            
            // gets the spline points
            // draws the spline points
            auto splinePoints = _spline.splinePts();
            glBindBuffer(GL_ARRAY_BUFFER, _buffer[2]);
            glEnableVertexAttribArray(vertexPosition);
            glBufferData(GL_ARRAY_BUFFER, int(splinePoints.size()) * 2 * sizeof(GLfloat), &splinePoints[0], GL_STATIC_DRAW);
            glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
            glDrawArrays(GL_LINE_STRIP, 0, int(splinePoints.size()));
        }
    }
}
