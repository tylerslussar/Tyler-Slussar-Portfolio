//
//  GLFWBase.cpp
//  
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#include <cstdlib>
#include <iostream>

#include <GL/glew.h>

#include "GLFWBase.hpp"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

static GLFWBase *glBase;

//----------------------------------------------------------------------

static void errorCallback(int error, const char* description)
{
    cerr << description << endl;
}

//----------------------------------------------------------------------

GLFWBase::GLFWBase(std::string windowTitle, int width, int height) {
    // save the object for use in static callbacks
    glBase = this;

    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // try to get a fairly recent version of OpenGL
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //  create the GLFW window
    _window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
    if (!_window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // set it to be the current OpenGL context
    glfwMakeContextCurrent(_window);

    // Initialize GLEW
    // global variable declared in GLEW files
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        cerr << "failed to initialize GLEW\n";
        exit(EXIT_FAILURE);
    }

    // specify refresh rate (normally 1)
    glfwSwapInterval(1);

    // output some information about OpenGL version
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    cerr << "------------------------------------------" << endl;
    cerr << "glfw OpenGL version: " << major << "." << minor << "." << rev << endl;
    cerr << "glfwGetVersion: " << glfwGetVersionString() << endl;
    cerr << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    cerr << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cerr << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cerr << "Renderer: " << glGetString(GL_RENDERER) << endl;
    GLint textureUnits;
    glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &textureUnits);
    cerr << "Num texture units: " << textureUnits << endl;
    cerr << "------------------------------------------" << endl << endl;

    // get window and frame buffer sizes
    glfwGetWindowSize(_window, &_windowWidth, &_windowHeight);
    glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);
    // will be 2.0 for retina displays
    _displayScale = _frameBufferWidth / float(_windowWidth);


    // set static callbacks
    glfwSetKeyCallback(_window, GLFWBase::staticKeyboardCallback);
    glfwSetCursorPosCallback(_window, GLFWBase::staticCursorPositionCallback);
    glfwSetCursorEnterCallback(_window, GLFWBase::staticCursorEnterCallback);
    glfwSetMouseButtonCallback(_window, GLFWBase::staticMouseButtonCallback);
    glfwSetScrollCallback(_window, GLFWBase::staticScrollCallback);
    glfwSetWindowSizeCallback(_window, GLFWBase::staticWindowSizeCallback);

    // Create a vertex array object since all programs need at least one
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
}

//----------------------------------------------------------------------

void GLFWBase::runLoop(bool waitForEvents) {
    while (!glfwWindowShouldClose(_window)) {

        // render and swap buffers
        render();
        glfwSwapBuffers(_window);

        // either wait for an event or just check for an event and continue
        if (waitForEvents ) {
            glfwWaitEvents();
        }
        else {
            glfwPollEvents();
        }
    }

    // deallocate the vertex array created in constructor
    glDeleteVertexArrays(1, &_vao);

    // close window and terminate
    glfwDestroyWindow(_window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

//----------------------------------------------------------------------

void GLFWBase::render() {
    // default to clearing screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//----------------------------------------------------------------------

void GLFWBase::keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // quit on escape key or q
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

//----------------------------------------------------------------------

void GLFWBase::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {

}

//----------------------------------------------------------------------

void GLFWBase::cursorEnterCallback(GLFWwindow* window, int entered) {
    if (entered) {
        // The cursor entered the client area of the window
    }
    else {
        // The cursor left the client area of the window
    }
}

//----------------------------------------------------------------------

void GLFWBase::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        cerr << "left press: " << xPos << " " << yPos << " " << mods << endl;
    }
}

//----------------------------------------------------------------------

void GLFWBase::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}

//----------------------------------------------------------------------

void GLFWBase::windowSizeCallback(GLFWwindow *window, int width, int height) {
    _windowWidth = width;
    _windowHeight = height;
    // also update frameBuffer width and height and display scale
    glfwGetFramebufferSize(_window, &_frameBufferWidth, &_frameBufferHeight);
    // will be 2.0 for retina displays
    _displayScale = _frameBufferWidth / float(_windowWidth);
}

//----------------------------------------------------------------------

void GLFWBase::staticKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    glBase->keyboardCallback(window, key, scancode, action, mods);
}

//----------------------------------------------------------------------

void GLFWBase::staticCursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
    glBase->cursorPositionCallback(window, xPos, yPos);
}

//----------------------------------------------------------------------

void GLFWBase::staticCursorEnterCallback(GLFWwindow* window, int entered) {
    glBase->cursorEnterCallback(window, entered);
}

//----------------------------------------------------------------------

void GLFWBase::staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    glBase->mouseButtonCallback(window, button, action, mods, xPos, yPos);
}

//----------------------------------------------------------------------

void GLFWBase::staticScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    glBase->scrollCallback(window, xOffset, yOffset);
}

//----------------------------------------------------------------------

void GLFWBase::staticWindowSizeCallback(GLFWwindow *window, int width, int height) {
    glBase->windowSizeCallback(window, width, height);
}

//----------------------------------------------------------------------
