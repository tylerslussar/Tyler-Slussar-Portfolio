//
//  Renderer.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#include "graphics.hpp"

using std::string;

Renderer::Renderer(std::string windowTitle, int width, int height) : GLFWBase(windowTitle, width, height) {

    // create the shaders needed

    // vertex shader for points
    string pointVShader = R"(
    #version 330 core

    // Input vertex data, different for all executions of this shader.
    layout(location = 0) in vec3 vPosition;

    uniform mat4 projectionEyeMatrix;
    uniform mat4 objectMatrix;

    void main()
    {
      // vertex shader must set gl_Position
      gl_Position = projectionEyeMatrix * objectMatrix * vec4(vPosition, 1);
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

//	string vertexPath = pathUsingEnvironmentVariable("pointVShader.txt", "GL_SHADER_DIR");
//	string shaderPath = pathUsingEnvironmentVariable("pointFShader.txt", "GL_SHADER_DIR");

    ShaderProgram program;
    program.makeProgramFromShaderStrings(pointVShader, pointFShader);
    PointDrawable::setShaderProgram(program);
    PolyLineDrawable::setShaderProgram(program);
    LineDrawable::setShaderProgram(program);

    // vertex shader for colored points
    string coloredPointVShader = R"(
    #version 330 core

    // Input vertex data, different for all executions of this shader.
    layout(location = 0) in vec3 vPosition;
    layout(location = 1) in vec3 vColor;

    uniform mat4 projectionEyeMatrix;
    uniform mat4 objectMatrix;

    out vec3 color;

    void main()
    {
      // vertex shader must set gl_Position
      gl_Position = projectionEyeMatrix * objectMatrix * vec4(vPosition, 1);
      color = vColor;
    }
    )";

    // fragment shader for colored points
    string coloredPointFShader = R"(
    #version 330 core

    // value representing interpolated vertex
    in vec3 color;

    // color to use for fragment
    out vec4 finalColor;

    void main()
    {
      finalColor = vec4(color, 1);
    }
    )";

//	vertexPath = pathUsingEnvironmentVariable("coloredPointVShader.txt", "GL_SHADER_DIR");
//	shaderPath = pathUsingEnvironmentVariable("coloredPointFShader.txt", "GL_SHADER_DIR");

    ShaderProgram program2;
    program2.makeProgramFromShaderStrings(coloredPointVShader, coloredPointFShader);
    ColoredPointDrawable::setShaderProgram(program2);
}

Renderer::~Renderer() noexcept {

}

void Renderer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods, double xPos, double yPos) {

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        // output to match (0, 0) bottom left and (width, height) top right
        std::cerr << "left press: " << xPos << " " << windowHeight() - yPos << " " << mods << std::endl;
    }
}

size_t Renderer::addPoints(const std::vector<Point3D> &pts, const Color &color, float pointSize, const mat4 &objectTransformation) {
    auto drawable = std::make_shared<PointDrawable>(pts, color, displayScale() * pointSize, objectTransformation);
    _objects.push_back(drawable);
    return _objects.size() - 1;
}

size_t Renderer::addColoredPoints(const std::vector<ColoredPoint3D> &pts, const float pointSize, const mat4 &objectTransformation) {
    auto drawable = std::make_shared<ColoredPointDrawable>(pts, displayScale() * pointSize, objectTransformation);
    _objects.push_back(drawable);
    return _objects.size() - 1;
}

size_t Renderer::addLines(const std::vector<Line3D> &lines, const Color &color, const mat4 &objectTransformation) {
    auto drawable = std::make_shared<LineDrawable>(lines, color, objectTransformation);
    _objects.push_back(drawable);
    return _objects.size() - 1;
}

size_t Renderer::addLineStrip(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation) {
    auto drawable = std::make_shared<LineStripDrawable>(pts, color, objectTransformation);
    _objects.push_back(drawable);
    return _objects.size() - 1;
}

size_t Renderer::addPolyLine(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation) {
    auto drawable = std::make_shared<PolyLineDrawable>(pts, color, objectTransformation);
    _objects.push_back(drawable);
    return _objects.size() - 1;
}

void Renderer::removeDrawable(size_t position) {
    _objects.erase(_objects.begin() + position);
}

void Renderer::render() {
    // set clear color to black
    glClearColor(0, 0, 0, 1);

    // glDisable(GL_DEPTH_BUFFER_BIT);
    // glDisable(GL_BLEND);

    // clear the window and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // make orthographic transformation that takes points in which
    // bottom left corner is (0, 0) and top right corner of window is (width, height)
    // and transforms them to bottom left (-1, 1) and top right (1, 1)
    float w = float(windowWidth());
    float h = float(windowHeight());
    mat4 projectionEyeMatrix = Translate(-1.0f, -1.0f, 0.0f) * Scale(2.0f / w, 2.0f / h, 1.0f);

    // draw each added drawable with the transformation
    for (auto i=0; i<_objects.size(); ++i) {
        _objects[i]->render(projectionEyeMatrix);
    }
}
