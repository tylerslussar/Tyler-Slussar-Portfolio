//
//  PiecewiseBezier.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/26/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#ifndef PiecewiseBezier_hpp
#define PiecewiseBezier_hpp

#include <stdio.h>
#include <vector>

#include "graphics.hpp"

class PiecewiseBezier {
    
public:
    PiecewiseBezier() {}
    
    /// adds a new control point at pt parameter along with the handle points before and after it
    /// when there are zero control points, the first handle point is below and to the left of the control
    /// point (by the offset amounts) and the second handle point is above and to the right of the control point
    /// after that, alternate whether first point is above or below the added pt
    /// @param pt location for middle control point to be added
    /// @param xOffset offset from pt.x for the handle points  coordinate
    /// @param yOffset offset from pt.y for the handle points  coordinate
    void addControlPointWithHandles(vec2 pt, double xOffset = 10.0, double yOffset = 40.0);
    
    /// number of control points added (note first and last point are not part of spline - just the handles
    int numControlPoints() const { return int(_controlPoints.size()); }
    
    /// starting address of first control point so can send to OpenGL buffer
    const vec2* controlPoints() const { return &_controlPoints[0]; }
     
    /// vector of end points for each handle
    std::vector<vec2> controlLines() const;
    
    // vector of points for the spline polyline
    std::vector<vec2> splinePts() const;
    
    /// when and xPos and yPos are passed the method loops through the control points to see if it close to any of the control points
    /// the click must be 8 pixels by the control point
    /// @param xPos x-coordinate of the click
    /// @param yPos y-coordinate of the click
    int closeTo(double xPos, double yPos);
    
    /// updates a certain control point based on index recieved and moves them to the xPos and yPos
    /// @param index the index at which point is moving
    /// @param xPos x-coordinate that the point is moved to
    /// @param yPos y-coordinate that the point is moved to
    void updatePoint(int index, double xPos, double yPos);
    
private:
    // vector for the control points
    std::vector<vec2> _controlPoints;
};

#endif /* PiecewiseBezier_hpp */
