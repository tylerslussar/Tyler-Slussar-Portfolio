//
//  Line.hpp
//  ComputerGraphics
//
//  Created by David M. Reed on 11/11/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include "Point.hpp"

class Line3D {

public:
    /// create line between two points
    /// @param p1 first end point
    /// @param p2 second end point
    Line3D(const Point3D &p1, const Point3D &p2);

    /// set end points of line
    /// @param p1 first end point
    /// @param p2 second end point
    void set(const Point3D &p1, const Point3D &p2);

    /// set end points of line
    /// @param x1 x-coordinate of first point
    /// @param y1 y-coordinate of first point
    /// @param z1 z-coordinate of first point
    /// @param x2 x-coordinate of second  point
    /// @param y2 y-coordinate of second point
    /// @param z2 z-coordinate of second point
    void set(const float x1, const float y1, const float z1,
             const float x2, const float y2, const float z2);

    /// return first point
    Point3D p1() const { return _p1; }
    /// return second point
    Point3D p2() const { return _p2; }

private:
    Point3D _p1, _p2;
};

inline Line3D::Line3D(const Point3D &p1, const Point3D &p2) {
    set(p1, p2);
}

inline void Line3D::set(const Point3D &p1, const Point3D &p2) {
    _p1 = p1;
    _p2 = p2;
}

inline void Line3D::set(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2) {
    _p1.set(x1, y1, z1);
    _p2.set(x2, y2, z2);
}

#endif /* Line_hpp */
