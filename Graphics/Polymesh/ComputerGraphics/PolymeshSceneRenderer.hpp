//
//  PolymeshSceneRenderer.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 1/28/20.
//  Copyright © 2020 David M Reed. All rights reserved.
//

#ifndef PolymeshSceneRenderer_hpp
#define PolymeshSceneRenderer_hpp

#include "graphics.hpp"
#include "Polymesh.hpp"

class PolymeshSceneRenderer: public Renderer {
public:
    /// Renderer subclass for reading and rendering Polymesh
    /// @param windowTitle title for the window
    /// @param width width of window
    /// @param height height of window
    /// @param filename full path to a single polymesh text file
    PolymeshSceneRenderer(std::string windowTitle, int width, int height, std::string filename);

    virtual ~PolymeshSceneRenderer() noexcept {}

    // render the polymesh scene
    virtual void render() override;

    /// called when a key is pressed/released (default implementation quits on pressing Q or Esc)
    /// @param window the GLFW window
    /// @param key see http://www.glfw.org/docs/latest/group__keys.html
    /// @param scancode scancode is unique for every key, regardless of whether it has a key token. Scancodes are platform-specific but consistent over time, so keys will have different scancodes depending on the platform
    /// @param action one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
    /// @param mods one of GLFW_MOD_SHIFT GLFW_MOD_CONTROL GLFW_MOD_ALT GLFW_MOD_SUPER
    virtual void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

    /// callback when the window is resized
    /// @param window the GLFW window
    /// @param width new width of window
    /// @param height new height of window
    virtual void windowSizeCallback(GLFWwindow *window, int width, int height) override;

private:
    Polymesh _polymesh;
    ShaderProgram _shaderProgram;
};

#endif /* PolymeshSceneRenderer_hpp */
