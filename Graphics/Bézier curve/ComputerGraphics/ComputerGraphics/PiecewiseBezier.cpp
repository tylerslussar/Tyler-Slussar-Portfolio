////
//  PiecewiseBezier.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/26/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#include "PiecewiseBezier.hpp"

inline double sqr(double x) {
    return x * x;
}

inline double cube(double x) {
    return x * x * x;
}

void PiecewiseBezier::addControlPointWithHandles(vec2 pt, double xOffset, double yOffset) {
    // alternate where first handle point goes vs. second handle point
    double multiplier = (_controlPoints.size() % 2 == 0) ? 1.0 : -1.0;
    
    // add the handle offset from the pt
    _controlPoints.push_back(vec2(pt.x - xOffset, pt.y + multiplier * yOffset));
    // add the clicked control point
    _controlPoints.push_back(pt);
    // add the other handle offset from the point
    _controlPoints.push_back(vec2(pt.x + xOffset, pt.y - multiplier * yOffset));
}

std::vector<vec2> PiecewiseBezier::controlLines() const {
    std::vector<vec2> linePts;
    
    // add end points for handles skipping middle point which is the clicked control point
    // don't use _controlPoint.size() as it returns an unsigned long so subtracting two
    // from it would result in an int near largest possible long value
    for (auto i=0; i<numControlPoints() - 2; i += 3) {
        linePts.push_back(_controlPoints[i]);
        linePts.push_back(_controlPoints[i+2]);
    }
    return linePts;
}

std::vector<vec2> PiecewiseBezier::splinePts() const {
    
    std::vector<vec2> splinePoints;
    double xExpress;
    double yExpress;
    vec2 p0, p1, p2, p3;

    // loops through control points to get the 4 points for the spline
    // starts at the second control point
    // stops where it will not index out of control points and stops where controls points
    // are not needed to draw the spline
    for (int i = 1; i < numControlPoints() - 2; i += 3){
       
        p0 = _controlPoints[i];
        p1 = _controlPoints[i + 1];
        p2 = _controlPoints[i + 2];
        p3 = _controlPoints[i + 3];
        
        // loops through the t-values from 0-1 with increment of 0.01
        // calculates the new point with the points grabbed and t-value
        // places them into vector
        for (float t = 0; t < 1.0; t += 0.01){

            xExpress = cube(1-t) * p0.x + 3 * sqr(1-t) * t * p1.x + 3 * (1-t) * sqr(t) * p2.x + cube(t) * p3.x;
            yExpress = cube(1-t) * p0.y + 3 * sqr(1-t) * t * p1.y + 3 * (1-t) * sqr(t) * p2.y + cube(t) * p3.y;
               
            splinePoints.push_back(vec2(xExpress, yExpress));

        }
    }
    // returns vector of vec2
    return splinePoints;
}

int PiecewiseBezier::closeTo(double xPos, double yPos){
   
    // looping through control points
    for (int i = 0; i < numControlPoints(); i++){
        // if the click is within the point by 8 pixels in the x & y then that is
        // the point being clicked
        if (abs(xPos - _controlPoints[i].x) < 8 && abs(yPos - _controlPoints[i].y) < 8){
            return i;
        }
    }
    // if there is no point near the click, return a negative index
    return -1;
}

void PiecewiseBezier::updatePoint(int index, double xPos, double yPos){
   
    // if there is not a negative index, then execute
    if (index >= 0){
       
        // takes the current x and y and finds their differences
        double oldX = _controlPoints[index].x;
        double oldY = _controlPoints[index].y;
        double differenceY = yPos - oldY;
        double differenceX = xPos - oldX;
        
        if (index % 3 == 0){
            
            // handle point
            // handle point moves based on passed in position
            // other handle moves based on the differeces in the opposite direction
            _controlPoints[index].x = xPos;
            _controlPoints[index].y = yPos;
            _controlPoints[index + 2].x = _controlPoints[index + 2].x + -differenceX;
            _controlPoints[index + 2].y = _controlPoints[index + 2].y + -differenceY;

        }
        else if (index % 3 == 1){
           
            // middle control/non-handle point
            // middle control moves based on passed in position
            // handles move based on the differences from the previous position of middle control
            // and the new position of middle control
            _controlPoints[index].x = xPos;
            _controlPoints[index].y = yPos;
            _controlPoints[index - 1].x = _controlPoints[index - 1].x + differenceX;
            _controlPoints[index - 1].y = _controlPoints[index - 1].y + differenceY;
            _controlPoints[index + 1].x = _controlPoints[index + 1].x + differenceX;
            _controlPoints[index + 1].y = _controlPoints[index + 1].y + differenceY;

        }
        else {
          
            // handle point
            // handle point moves based on passed in position
            // other handle moves based on the differeces in the opposite direction
            _controlPoints[index].x = xPos;
            _controlPoints[index].y = yPos;
            _controlPoints[index - 2].x = _controlPoints[index - 2].x + -differenceX;
            _controlPoints[index - 2].y = _controlPoints[index - 2].y + -differenceY;
        }
    }
}

