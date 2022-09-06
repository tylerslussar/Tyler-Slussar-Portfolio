//
//  PolyLineDrawable.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 11/11/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef PolyLineDrawable_hpp
#define PolyLineDrawable_hpp

#include "PointDrawable.hpp"

class PolyLineDrawable: public PointDrawable {
public:
    /// PolyLine (line between each point and between first and last points) using specified points
    /// @param pts vector of Point3D for the polyline
    /// @param color color for the polyline
    /// @param objectTransformation transformation matrix to apply when rendering
    PolyLineDrawable(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation = mat4());

    ~PolyLineDrawable() noexcept {}

private:
};

inline PolyLineDrawable::PolyLineDrawable(const std::vector<Point3D> &pts, const Color &color, const mat4 &objectTransformation): PointDrawable(pts, color, 1.0, objectTransformation) {
    // same as points except draw as line loop
    _drawType = GL_LINE_LOOP;
}

#endif /* PolyLineDrawable_hpp */
