//
//  PolymeshSceneRenderer.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/21/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#include <fstream>

#include "PolymeshSceneRenderer.hpp"

using std::string;

PolymeshReader::PolymeshReader(){
    _color = 0;
    _scale = 0;
    _rotate = 0;
    _translate = 0;
    _filename = "";
};

std::ifstream& operator>>(std::ifstream &ifs, PolymeshReader &p){
    
    // trys to grab filename for the polymesh
    std::string line = "";
    std::getline(ifs, line);
    
    // if the filename is not on the line then it grabs the next line
    if (line == "" || line == " "){
        std::getline(ifs, p._filename);

    }
    else{
        p._filename = line;
    }
    
    // inputs all values for the polymesh: color, scale, rotate, translate
    ifs >> p._color.x >> p._color.y >> p._color.z >> p._color.w;
    ifs >> p._scale.x >> p._scale.y >> p._scale.z;
    ifs >> p._rotate.x >> p._rotate.y >> p._rotate.z;
    ifs >> p._translate.x >> p._translate.y >> p._translate.z;
    
    
    return ifs;
};

// returns the corresponding vector or filename
std::string PolymeshReader::getFilename(){return _filename;};
vec4 PolymeshReader::getColor(){return _color;};
vec3 PolymeshReader::getScale(){return _scale;};
vec3 PolymeshReader::getRotate(){return _rotate;};
vec3 PolymeshReader::getTranslate(){return _translate;};


PolymeshSceneRenderer::PolymeshSceneRenderer(std::string windowTitle, int width, int height, std::string filename):Renderer(windowTitle, width, height) {
   
    // opens file and reads it
    std::string line;
    std::ifstream infile;
    infile.open(filename);
    
    // brings in the first eight values of the file
    infile >> _eye.x >> _eye.y >> _eye.z >> _eye.w;
    infile >> _coi.x >> _coi.y >> _coi.z >> _coi.w;
    
    // initalizes _vec
    _vec = normalize(_coi - _eye);
    
    // vector u that is on the x-axis, needed for easier calculations
    vec4 u; u.x = 1; u.y = 0; u.z = 0; u.w = 0;
    
    // calculates the vector length of the normalized vector
    _vectorLength = (sqrt((_vec.x * _vec.x) + (_vec.y * _vec.y) + (_vec.z * _vec.z)));
    
    // calculates the angle from the two points from the file
    _angle = acos(dot(u,_vec) / _vectorLength );
    
    // checks to see if the angle calculated is below the z-axis or greater than pi
    if (_coi.z < _eye.z){
        _angle = 2 * M_PI - _angle;
    }
    
    // reads in the first polymesh filename
    std::getline(infile, line);
    
    PolymeshReader pR;
    
    // calls the PolymeshReader input operator
    // for each PolymeshReader object created it is placed into an array
    while (infile >> pR){
        
        _polymeshReaderArray[_polyIncrement] = pR;
        _polyIncrement++;
       
    };
    
    // for each PolymeshReader object the corresponding polymesh is created
    // each polymesh object file is then read and buffers are binded
    for (int i = 0; i < _polyIncrement; i++){
        
        std::string fName =  _polymeshReaderArray[i].getFilename();
        _polymeshArray[i].readFromObjectFile(fName);
        _polymeshArray[i].bindArrayAndElementBuffers(0);
    }
    
    

    glClearColor(0.39, 0.56, 0.85, 1);
    glEnable(GL_DEPTH_TEST);

    string vShader = R"(
    #version 330 core

    layout(location = 0) in vec3 vPosition;
    uniform mat4 projectionEyeMatrix;
    uniform mat4 objectMatrix;

    void main()
    {
      gl_Position = projectionEyeMatrix * objectMatrix * vec4(vPosition, 1);
    }
    )";

    string fShader = R"(
    #version 330 core

    // uniform value representing polygon color
    uniform vec4 polyColor;

    // color to use for fragment
    out vec4 finalColor;

    void main()
    {
      finalColor = vec4(polyColor);
    }
    )";

    _shaderProgram.makeProgramFromShaderStrings(vShader, fShader);
    _shaderProgram.useProgram();
}

void PolymeshSceneRenderer::render() {
    // set to background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // get locations in shader so can send data
    GLuint color = glGetUniformLocation(_shaderProgram.program(), "polyColor");
    GLuint object = glGetUniformLocation(_shaderProgram.program(), "objectMatrix");
    GLuint projectionEye = glGetUniformLocation(_shaderProgram.program(), "projectionEyeMatrix");
   
    // eye x & z are moved according to the increment
    _eye.x += _movementIncrementX;
    _eye.z += _movementIncrementZ;
    
    // _angle is changed by the increment and coi x & z are calculated
    // based on the location of eye
    _angle += _angleIncrement;
    _coi.x = _vectorLength * cos(_angle) + _eye.x;
    _coi.z = _vectorLength * sin(_angle) + _eye.z;
    
    
    // polymesh objects are drawn
    for (int i = 0; i < _polyIncrement; i++){
        
        // values of the polymeshs are grabbed by their corresponding
        // PolymeshReader object
        vec4 vecColor = _polymeshReaderArray[i].getColor();
        vec3 scale = _polymeshReaderArray[i].getScale();
        vec3 rotate = _polymeshReaderArray[i].getRotate();
        vec3 translate = _polymeshReaderArray[i].getTranslate();
        
        // determining projection matrix with the eye and coi
        mat4 projectionEyeMatrix = Perspective(90, _windowWidth / float(_windowHeight), 0.1, 100) * LookAt(_eye, _coi, vec4(0, 1, 0, 1));
        glUniformMatrix4fv(projectionEye, 1, GL_TRUE, projectionEyeMatrix);
        
        // tranforming the polymesh
        mat4 objectMatrix = Translate(translate.x, translate.y, translate.z) * Scale(scale.x, scale.y, scale.z)
        * RotateX(rotate.x) * RotateY(rotate.y) * RotateZ(rotate.z);
        glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
        glUniform4fv(color, 1, vecColor);
        
        // draws the polymesh
        _polymeshArray[i].glDraw();
    }
}


void PolymeshSceneRenderer::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    
    if (key == GLFW_KEY_K){
        if (action == GLFW_PRESS){
            // normalized the _vec based on the coi & eye everytime it
            // changes based on press k
            _vec = normalize(_coi - _eye);
            
            // increments are assigned based on _vec x & z
            // moving forward
            _movementIncrementZ = 0.05 * _vec.z;
            _movementIncrementX = 0.05 * _vec.x;

        }
        else if (action == GLFW_RELEASE){
            // no movement, sets increment to 0
            _movementIncrementX = 0;
            _movementIncrementZ = 0;
        }
    }
    else if (key == GLFW_KEY_J){
        if (action == GLFW_PRESS){
            // normalized the _vec based on the coi & eye everytime it
            // changes based on press k
            _vec = normalize(_coi - _eye);
            
            // increments are assigned based on _vec x & z
            // moving backwards
            _movementIncrementZ = -0.05 * _vec.z;
            _movementIncrementX = -0.05 * _vec.x;
        }
        else if (action == GLFW_RELEASE){
         
            // no movement, sets increment to 0
            _movementIncrementZ = 0;
            _movementIncrementX = 0;
        }
    }
    else if (key == GLFW_KEY_D){
        if (action == GLFW_PRESS){
            // assigns increments for rotating
            _angleIncrement = -0.0314;
            
        }
        else if (action == GLFW_RELEASE){
            // rotation does not move when nothing is pressed
            _angleIncrement = 0;

        }
    }
    else if (key == GLFW_KEY_F){
        if (action == GLFW_PRESS){
            // assigns increments for rotating
            _angleIncrement = 0.0314;
        }
        else if (action == GLFW_RELEASE){
            // rotation does not move when nothing is pressed
            _angleIncrement = 0;

        }
    }
    // quit on escape key or q
    else if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    };
}

void PolymeshSceneRenderer::windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
