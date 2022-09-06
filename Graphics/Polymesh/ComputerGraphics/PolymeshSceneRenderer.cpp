//
//  PolymeshSceneRenderer.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/21/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#include <fstream>

#include "PolymeshSceneRenderer.hpp"

using std::string;

PolymeshSceneRenderer::PolymeshSceneRenderer(std::string windowTitle, int width, int height, std::string filename) : Renderer(windowTitle, width, height) {

    
    _polymesh.readFromObjectFile(filename);
    _polymesh.bindArrayAndElementBuffers(0);

    glClearColor(0.39, 0.56, 0.85, 1);
    glEnable(GL_DEPTH_TEST);

    string vShader = R"(
    #version 330 core

    layout(location = 0) in vec3 vPosition;
    uniform mat4 projectionEyeMatrix;
    uniform mat4 objectMatrix;

    void main()
    {
      gl_Position = projectionEyeMatrix * objectMatrix * vec4(vPosition, 1);
    }
    )";

    string fShader = R"(
    #version 330 core

    // uniform value representing polygon color
    uniform vec4 polyColor;

    // color to use for fragment
    out vec4 finalColor;

    void main()
    {
      finalColor = vec4(polyColor);
    }
    )";

    _shaderProgram.makeProgramFromShaderStrings(vShader, fShader);
    _shaderProgram.useProgram();
}

void PolymeshSceneRenderer::render() {
    // set to background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // get locations in shader so can send data
    GLuint color = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    GLuint object = glGetUniformLocation(_shaderProgram.program(), "objectMatrix");
    GLuint projectionEye = glGetUniformLocation(_shaderProgram.program(), "projectionEyeMatrix");


    // perspective and eye transformation
    mat4 projectionEyeMatrix = Perspective(90, _windowWidth / float(_windowHeight), 0.1, 100) * LookAt(vec4(2, 1, 2, 1), vec4(0, 1, 0, 1), vec4(0, 1, 0, 1));
    glUniformMatrix4fv(projectionEye, 1, GL_TRUE, projectionEyeMatrix);

    // identity matrix for object transformation
    mat4 objectMatrix = Scale(1, 1, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    // use red
    glUniform4fv(color, 1, vec4(1, 0, 0, 1));

    _polymesh.glDraw();
}


void PolymeshSceneRenderer::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {

    // quit on escape key or q
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void PolymeshSceneRenderer::windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
