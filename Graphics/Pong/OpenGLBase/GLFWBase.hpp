//
//  GLFWBase.hpp
//  GLFWDemo
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#ifndef __GLFWDemo__GLFWBase__
#define __GLFWDemo__GLFWBase__

#include <iostream>
#include <string>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

class GLFWBase {

public:
    /// constructor
    /// @param windowTitle title for the window
    /// @param width width for window
    /// @param height height for window
    GLFWBase(std::string windowTitle, int width, int height);

    /// method to override for rendering scene; called automatially by event loop
    virtual void render();

    // MARK: input callbacks
    // more details of parameters are here: http://www.glfw.org/docs/latest/input.html

    /// called when a key is pressed/released (default implementation quits on pressing Q or Esc)
    /// @param window the GLFW window
    /// @param key see http://www.glfw.org/docs/latest/group__keys.html
    /// @param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
    /// @param action one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /// callback when cursor position changes (called even when mouse button is not pressed)
    /// @param window the GLFW window
    /// @param xPos x position within the window (0 is top left corner of window
    /// @param yPos y position within the window (0 is top left corner of window
    virtual void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);


    /// called whenever the cursor leavs or enters the window
    /// @param window the GLFW window
    /// @param entered non-zero if entered (I think)
    virtual void cursorEnterCallback(GLFWwindow* window, int entered);

    /// callback when a mouse button is pressed or released
    /// @param window the GLFW window
    /// @param button see: http://www.glfw.org/docs/latest/group__buttons.html
    /// @param action one of GLFW_PRESS or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    /// @param xPos x-position within the window (0 is top left corner of window
    /// @param yPos y-position within the window (0 is top left corner of window
    virtual void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos);

    /// callback when mouse/trackpad is scrolled
    /// @param window the GLFW window
    /// @param xOffset x-position within the window (0 is top left corner of window
    /// @param yOffset y-position within the window (0 is top left corner of window
    virtual void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    /// callback when the window is resized
    /// @param window the GLFW window
    /// @param width new width of window
    /// @param height new height of window
    virtual void windowSizeCallback(GLFWwindow *window, int width, int height);

    /// returns the window
    GLFWwindow* window() { return _window; }

    /// should not need to override, but virtual just in case
    /// @param waitForWevents - if true, uses glfwWaitEvents otherwise uses glfwPollEvents
    virtual void runLoop(bool waitForEvents = true);

    /// width of window
    int windowWidth() const { return _windowWidth; }

    /// height of window
    int windowHeight() const { return _windowHeight; }

    /// width of frame buffer (for retina screens may be twice the windowWidth)
    int frameBufferWidth() const { return _frameBufferWidth; }

    /// height of frame buffer (for retina screens may be twice the windowHeight)
    int frameBufferHeight() const { return _frameBufferHeight; }

    /// displayScale (should be 2.0 for retina screens)
    float displayScale() const { return _displayScale; }

protected:
    GLuint _vao;
    int _windowWidth, _windowHeight;
    int _frameBufferWidth, _frameBufferHeight;
    float _displayScale;

private:
    GLFWwindow *_window;
    static void staticKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void staticCursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
    static void staticCursorEnterCallback(GLFWwindow* window, int entered);
    static void staticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void staticScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    static void staticWindowSizeCallback(GLFWwindow *window, int width, int height);
};
#endif /* defined(__GLFWDemo__GLFWBase__) */
