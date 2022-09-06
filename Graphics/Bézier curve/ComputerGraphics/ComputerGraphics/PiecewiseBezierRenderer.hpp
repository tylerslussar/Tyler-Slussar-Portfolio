//
//  PiecewiseBezierRenderer.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 12/26/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#ifndef PiecewiseBezierRenderer_hpp
#define PiecewiseBezierRenderer_hpp

#include <string>
#include "graphics.hpp"
#include "PiecewiseBezier.hpp"

class PiecewiseBezierRenderer: public Renderer {

public:
    PiecewiseBezierRenderer(std::string windowTitle, int width, int height);
    
    virtual ~PiecewiseBezierRenderer() noexcept {}
    
    /// called when a key is pressed/released (default implementation quits on pressing Q or Esc)
    /// @param window the GLFW window
    /// @param key see http://www.glfw.org/docs/latest/group__keys.html
    /// @param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
    /// @param action one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    
    /// callback when a mouse button is pressed or released
    /// @param window the GLFW window
    /// @param button see: http://www.glfw.org/docs/latest/group__buttons.html
    /// @param action one of GLFW_PRESS or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    /// @param xPos x-position within the window (0 is top left corner of window
    /// @param yPos y-position within the window (0 is top left corner of window
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos) override;
    
    /// callback when cursor position changes (called even when mouse button is not pressed)
    /// @param window the GLFW window
    /// @param xPos x position within the window (0 is top left corner of window
    /// @param yPos y position within the window (0 is top left corner of window
    void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) override;
    
    void render() override;
    
private:
    // the Bezier spline to display
    PiecewiseBezier _spline;
    
    // whether or not to display the handles and control points
    // whether or not a mouse has been pressed
    bool _showHandles;
    bool _mousePress;
    
    // OpenGL data
    GLuint _buffer[3];
    ShaderProgram _shaderProgram;
    int _index;
};


#endif /* PiecewiseBezierRenderer_hpp */
