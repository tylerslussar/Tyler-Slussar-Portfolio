//
//  Polymesh.cpp
//  PolymeshScene
//
//  Created by David M Reed on 12/21/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//
#include <iostream>
#include <fstream>

using std::ifstream;
using std::vector;
using std::cout;
using std::endl;
using std::endl;

#include "Polymesh.hpp"

void Polymesh::init() {
    _numPoints = 0;
    _numTriangles = 0;
    _points = nullptr;
    _indices = nullptr;
    _arrayAndElementBuffers[0] = 0;
    _arrayAndElementBuffers[1] = 0;
}

void Polymesh::dealloc() {
    if (_arrayAndElementBuffers[0] != 0) {
        glDeleteBuffers(2, _arrayAndElementBuffers);
    }
    init();
}

void Polymesh::readFromObjectFile(std::string filename, bool frontFaceIsClockwise) {
    dealloc();
    
    _frontFaceIsClockwise = frontFaceIsClockwise;
    
    std::ifstream ifs;
    ifs.open(filename.c_str());
    int i, j, pos = 0, numPolygons, numVerts, value;
    vector<GLsizei> numVertsAndIndices;
    
    ifs >> _numPoints >> numPolygons;
    _points = std::make_unique<GLfloat[]>(_numPoints * 3);
    
    // read the points
    for (i=0; i<_numPoints * 3; ++i) {
        ifs >> _points[pos];
        pos++;
    }
    
    _numTriangles = 0;
    for (i=0; i<numPolygons; ++i) {
        ifs >> numVerts;
        numVertsAndIndices.push_back(numVerts);
        
        // number of triangles for a polygon is 2 fewer than number of points
        _numTriangles += numVerts - 2;
        
        // read indices and store them
        for (j=0; j<numVerts; ++j) {
            ifs >> value;
            numVertsAndIndices.push_back(value);
        }
    }
    
    _indices = std::make_unique<GLuint[]>(_numTriangles * 3);
    
    pos = 0;
    GLsizei indexPos = 0;
    for (i=0; i<numPolygons; ++i) {
        numVerts = numVertsAndIndices[pos];
        pos++;
        
        GLsizei fan0, fan1, fan2;
        fan0 = numVertsAndIndices[pos++];
        fan1 = numVertsAndIndices[pos++];
        // number of triangles for a polygon is 2 fewer than number of points
        for (j=0; j<numVerts - 2; ++j) {
            // grab next vertex for the triangle fan
            // after last index for polygon, this will increment pos to spot in vector that holds number of vertices in next polygon
            fan2 = numVertsAndIndices[pos++];
            _indices[indexPos++] = fan0;
            _indices[indexPos++] = fan1;
            _indices[indexPos++] = fan2;
            
            // set fan1 for next triangle
            fan1 = fan2;
        }
    }
    
    /* output for debugging purposes
     pos = 0;
     cout << _numPoints << endl;
     for (i=0; i<_numPoints; ++i) {
     cout << _points[pos] << " " << _points[pos+1] << " " << _points[pos+2] << endl;
     pos += 3;
     }
     
     pos = 0;
     cout << _numTriangles << endl;
     for (i=0; i<_numTriangles; ++i ) {
     cout << _indices[pos] << " " << _indices[pos+1] << " " << _indices[pos+2] << endl;
     pos += 3;
     }
     */
}

void Polymesh::bindArrayAndElementBuffers(int vertexPosition) {
    _vertexPosition = vertexPosition;
    
    // bind to buffers
    glGenBuffers(2, _arrayAndElementBuffers);
    
    // points go in array buffer
    glBindBuffer(GL_ARRAY_BUFFER, _arrayAndElementBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * _numPoints * sizeof(GLfloat), &_points[0], GL_STATIC_DRAW);
    
    // indices go in element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _arrayAndElementBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * _numTriangles * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);
    
    // specify buffer contains 3 floats for position
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    
    // save so can use in glDraw method
    _vertexPosition = vertexPosition;
    
    // must enable it
    glEnableVertexAttribArray(vertexPosition);
}

void Polymesh::glDraw() {
    // draw the traingles using the array and indices
    glBindBuffer(GL_ARRAY_BUFFER, _arrayAndElementBuffers[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _arrayAndElementBuffers[1]);
    glVertexAttribPointer(_vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    if (_frontFaceIsClockwise) {
        glFrontFace(GL_CW);
    } else {
        glFrontFace(GL_CCW);
    }
    glDrawElements(GL_TRIANGLES, 3 * _numTriangles, GL_UNSIGNED_INT, nullptr);
}
