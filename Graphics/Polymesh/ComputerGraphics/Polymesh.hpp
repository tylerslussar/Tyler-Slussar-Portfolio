//
//  Polymesh.hpp
//  PolymeshScene
//
//  Created by David M Reed on 12/21/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#ifndef Polymesh_hpp
#define Polymesh_hpp

#include "graphics.hpp"

class Polymesh {

public:
    Polymesh() { init(); }
    virtual ~Polymesh() noexcept { dealloc(); }

    /// initializes instance variables to indicate zero points/triangles and nullptr values for dynamic arrays
    virtual void init();

    /// deallocates OpenGL buffers
    virtual void dealloc();

    /// read polymesh from specified filename and store as triangles in CCW order
    /// @param filename full path to file containing polymesh data
    /// @param frontFaceIsClockwise
    /// @post sets _numPoints, _numTriangles and allocates _points and _indices arrays and fills in the arrays appropriately and sets the _frontFaceIsClockwise instance variable to the corresponding parameter
    virtual void readFromObjectFile(std::string filename, bool frontFaceIsClockwise=true);

    /// return number of triangles in polymesh
    GLsizei numTriangles() const { return _numTriangles; }

    /// return number of points in polymesh
    GLsizei numPoints() const { return _numPoints; }

    /*! creates OpenGL buffers based on the points and indices
     @param vertexPosition layout position in vertex shader of coordinate
     @post allocates OpenGL buffers and copies data for points and indices to the buffers and sets _vertexPosition to vertexPosition so can use it in glDraw
     */

    /// creates OpenGL buffers based on the points and indices
    /// @param vertexPosition  layout position in vertex shader of coordinate
    virtual void bindArrayAndElementBuffers(int vertexPosition);

    /// executes OpenGL commands to draw the Polymesh
    /// @pre OpenGL commands to clear color and depth buffer have been executed
    virtual void glDraw();

protected:
    // number of points in the polymesh
    GLsizei _numPoints;

    // number of triangles in the polymesh
    GLsizei _numTriangles;

    // dynamically allocated array of points (3 * _numPoints for x, y, z coordinates)
    std::unique_ptr<GLfloat[]> _points;

    // dynamically allocated array of indices (3 * _numTriangles since 3 point indices per triangle)
    std::unique_ptr<GLuint[]> _indices;

    // values for the GL_ARRAY_BUFFER and GL_ELEMENT_ARRAY_BUFFER for the point and index data
    GLuint _arrayAndElementBuffers[2];

    // vertex shader layout position for x, y, z coordinates
    GLuint _vertexPosition;
    
    bool _frontFaceIsClockwise;


private:
    // prevent copy constructor and operator= from being called
    Polymesh(const Polymesh &);
    Polymesh& operator=(const Polymesh &);
};

#endif /* Polymesh_hpp */
