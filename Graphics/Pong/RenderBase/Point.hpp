//
//  Point.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

// MARK: Point3D

class Point3D {
public:
    /// create a point with specified coordinates
    Point3D(const float x = 0.0, const float y = 0.0, const float z = 0.0);

    /// set the coordinates
    void set(const float x, const float y, const float z = 0);

    // public data for convenience
    float x, y, z;
};

inline Point3D::Point3D(const float x, const float y, const float z) {
    set(x, y, z);
}

inline void Point3D::set(const float x, const float y, const float z) {
    this->x = x; this->y = y; this->z = z;
}

// MARK: ColoredPoint3D

class ColoredPoint3D {
public:
    /// create a point with specified coordinates and color
    ColoredPoint3D(const float x = 0.0, const float y = 0.0, const float z = 0.0, const float r = 0.0, const float g = 0.0, const float b = 0.0);

    /// set the coordinates and color
    void set(const float x = 0.0, const float y = 0.0, const float z = 0.0, const float r = 0.0, const float g = 0.0, const float b = 0.0);

    // public data for convenience
    float x, y, z;
    float r, g, b;
};

inline ColoredPoint3D::ColoredPoint3D(const float x, const float y, const float z, const float r, const float g, const float b) {
    set(x, y, z, r, g, b);
}

inline void ColoredPoint3D::set(const float x, const float y, const float z, const float r, const float g, const float b) {
    this->x = x; this->y = y; this->z = z;
    this->r = r; this->g = g; this->b = b;
}

#endif /* Point_hpp */
