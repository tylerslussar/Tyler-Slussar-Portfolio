//
//  LineDrawable.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 11/11/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef LineDrawable_hpp
#define LineDrawable_hpp

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include "GLFW/glfw3.h"
#include "Angel.hpp"
#include "Line.hpp"
#include "Color.hpp"
#include "Drawable.hpp"
#include "ShaderProgram.hpp"
#include "PointDrawable.hpp"

class LineDrawable: public Drawable {

public:
    /// lines to render
    /// @param lines vector of Line3D to render
    /// @param color color for the lines
    /// @param objectTransformation transformation matrix to apply when rendering
    LineDrawable(const std::vector<Line3D> lines, const Color &color, const mat4 &objectTransformation = mat4());

    ~LineDrawable() noexcept;

    /// render with specified projection and eye transformation matrix
    /// @param projectionEyeMatrix projection and eye matrix transformation
    void render(const mat4 &projectionEyeMatrix) override;

    /// set the ShaderProgram to be used by all LineDrawable instances
    /// @param shaderProgram shaderProgram to use for all LineDrawable instances
    static void setShaderProgram(const ShaderProgram &shaderProgram);

private:
    Color _color;
    unsigned int _buffer;
    unsigned int _numLines;
    static ShaderProgram _shaderProgram;
};


#endif /* LineDrawable_hpp */
