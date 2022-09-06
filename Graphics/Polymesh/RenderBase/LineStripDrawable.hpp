//
//  LineStrip.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 11/11/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef LineStripDrawable_hpp
#define LineStripDrawable_hpp

#include "PointDrawable.hpp"

class LineStripDrawable: public PointDrawable {
public:
    /// LineStrip (line between each point but not connecting first and last point)
    /// @param pts vector of Point3D for the line strip
    /// @param color color for the line strip
    /// @param objectTransformation transformation matrix to apply when rendering
    LineStripDrawable(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation = mat4());

    ~LineStripDrawable() noexcept {}
};

inline LineStripDrawable::LineStripDrawable(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation): PointDrawable(pts, color, 1.0, objectTransformation) {
    // same as points except draw as line strip
    _drawType = GL_LINE_STRIP;
}

#endif /* LineStrip_hpp */
