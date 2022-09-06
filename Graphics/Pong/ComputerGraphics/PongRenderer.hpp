//
//  PongRenderer.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/20/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#ifndef PongRenderer_hpp
#define PongRenderer_hpp

#include "graphics.hpp"

class PongRenderer: public Renderer {
public:
    /// Renderer subclass for reading and rendering Polymesh
    /// @param windowTitle title for the window
    /// @param width width of window
    /// @param height height of window
    /// @param filename filename containing Polymesh scene data
    PongRenderer(std::string windowTitle, int width, int height);
    
    virtual ~PongRenderer() noexcept {}
    
    // render the polymesh scene
    virtual void render() override;
    
    /// called when a key is pressed/released (default implementation quits on pressing Q or Esc)
    /// @param window the GLFW window
    /// @param key see http://www.glfw.org/docs/latest/group__keys.html
    /// @param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
    /// @param action one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

private:
    ShaderProgram _shaderProgram;
    // values for the GL_ARRAY_BUFFER for the vertices
    GLuint _buffer;
    
    // vertex shader layout position for x, y, z coordinates
    GLuint _vertexPosition;
    
    // location and increment for ball
    vec2 _ballLocation;
    vec2 _ballIncrement;
    // location and paddle increment for paddle
    // game states
    float _paddleIncrement;
    float _paddleLocationY;
    std::string _paddleState;
    std::string _gState;
    std::string _pState;
};

#endif /* PongRenderer_hpp */
