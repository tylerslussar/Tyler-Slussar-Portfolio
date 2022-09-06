//
//  ColoredPointDrawable.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef ColoredPointDrawable_hpp
#define ColoredPointDrawable_hpp

#include <memory>
#include <vector>

#include "Angel.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "Drawable.hpp"
#include "ShaderProgram.hpp"

class ColoredPointDrawable: public Drawable {

public:
    /// create colored points
    /// @param pts vector of ColoredPoint3D t
    /// @param pointSize size of point (defaults to 1.0)
    /// @param objectTransformation transformation matrix to apply when rendering
    ColoredPointDrawable(const std::vector<ColoredPoint3D> &pts, const GLfloat pointSize = 1.0, const mat4 &objectTransformation = mat4());

    ~ColoredPointDrawable() noexcept;

    /// render with specified projection and eye transformation matrix
    /// @param projectionEyeMatrix projection and eye matrix transformation
    void render(const mat4 &projectionEyeMatrix) override;

    /// set the ShaderProgram to be used by all ColoredPointDrawable instances
    /// @param shaderProgram shaderProgram to use for all ColoredPointDrawable instances
    static void setShaderProgram(const ShaderProgram &shaderProgram);

private:    
    unsigned int _buffer;
    unsigned int _numPoints;
    GLfloat _pointSize;
    static ShaderProgram _shaderProgram;
};

#endif /* ColoredPointDrawable_hpp */
