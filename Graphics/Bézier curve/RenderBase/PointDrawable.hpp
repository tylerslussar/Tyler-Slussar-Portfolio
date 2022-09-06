//
//  PointDrawable.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef PointDrawable_hpp
#define PointDrawable_hpp

#include <memory>
#include <vector>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include "GLFW/glfw3.h"
#include "Angel.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "Drawable.hpp"
#include "ShaderProgram.hpp"

class PointDrawable: public Drawable {

public:
    /// set of points to render
    /// @param pts vector of Point3D to render
    /// @param color color to use
    /// @param point size
    /// @param objectTransformation transformation matrix to apply when rendering
    PointDrawable(const std::vector<Point3D> &pts, const Color &color, const GLfloat pointSize = 1.0, const mat4 objectTransformation = mat4());

    ~PointDrawable() noexcept;

    /// render with specified projection and eye transformation matrix
    /// @param projectionEyeMatrix projection and eye matrix transformation
    void render(const mat4 &projectionEyeMatrix) override;

    /// set the ShaderProgram to be used by all PointDrawable instances
    /// @param shaderProgram shaderProgram to use for all PointDrawable instances
    static void setShaderProgram(const ShaderProgram &shaderProgram);

private:
    Color _color;
    unsigned int _buffer;
    unsigned int _numPoints;
    GLfloat _pointSize;
    static ShaderProgram _shaderProgram;
};

#endif /* PointDrawable_hpp */
