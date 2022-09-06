//
//  Polymesh.cpp
//  PolymeshScene
//
//  Created by David M Reed on 12/21/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//
//  Tyler Slussar 9:30 AM
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

void Polymesh::readFromObjectFile(std::string filename, bool frontFaceIsClockwise){
    
    //opens the file
    std::ifstream myfile;
    myfile.open(filename);
    
    // vector for storing the indices and number of polygons
    int polygons;
    vector<int> vec;
    
    myfile >> _numPoints >> polygons;
    
    // initializes the amount of points
    _points = std::make_unique<GLfloat[]>(3 * _numPoints);

    // grabs the points from the file
    for(int i = 0; i < _numPoints * 3; ++i){
        float num;
        myfile >> num;
            
        _points[i] = num;
    };
    
    
    // counts the number fo vertices on the polygon
    // calculates the number of triangles
    // add all the indices to the vector
    int numOnPoly;
    for(int i = 0; i < polygons; ++i){
       myfile >> numOnPoly;
        _numTriangles += numOnPoly - 2;
        vec.push_back(numOnPoly);
        
        for(int j = 0; j < numOnPoly; ++j){
            int indexNum;
            myfile >> indexNum;
            vec.push_back(indexNum);
        }
    };
    
    // initializes the amount of indices
    _indices = std::make_unique<GLuint[]>(3 * _numTriangles);
    
    // assigns a vector to keep track of indices needed to make triangles
    vector<int> smallVec;
    int indicesIndex = 0;
    for(int i = 0; i < polygons; ++i){
        // first number in the row of sequences
        int counter = vec[0];
        int x = 0;

        vec.erase(vec.begin());
        
        // places the sequences into the smallVec
        for(int j = 0; j < counter; ++j){
            smallVec.push_back(vec[0]);
            vec.erase(vec.begin());
        }
        // counter - 2 is the amount of triangles based on the sequence for each polygon
        while(x < counter - 2 ){
           
            // places the first element into _indices
            _indices[indicesIndex] = smallVec[0];
            
            // places the other two indices into _indices to create the triangles
            for(int k = 1; k < 3; k++){
                indicesIndex += 1;
                _indices[indicesIndex] = smallVec[k];
            }
            smallVec.erase(smallVec.begin() + 1);
            x += 1;
            indicesIndex += 1;

            }
        smallVec.clear();
            
        }
        
    }
    


void Polymesh::bindArrayAndElementBuffers(int vertexPosition){
    // generates the buffers and binds them
    glGenBuffers(2, _arrayAndElementBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, _arrayAndElementBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * _numPoints * sizeof(GLfloat), &_points[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _arrayAndElementBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * _numTriangles * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexPosition);
    glVertexAttribPointer(vertexPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
    
    
    
}


void Polymesh::glDraw(){
    // draws the elements
    glDrawElements(GL_TRIANGLES, 3 *_numTriangles, GL_UNSIGNED_INT, nullptr);
    
}
