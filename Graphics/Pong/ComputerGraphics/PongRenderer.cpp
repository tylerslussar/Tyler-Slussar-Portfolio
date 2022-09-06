//
//  PongRenderer.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 12/20/21.
//  Copyright © 2021 David M Reed. All rights reserved.
//

#include <string>
# include <ctime>
using std::string;

#include "PongRenderer.hpp"
PongRenderer::PongRenderer(std::string windowTitle, int width, int height): Renderer(windowTitle, width, height) {
    
    glGenBuffers(1, &_buffer);

    // create the shaders needed
    
    // vertex shader
    string vertexShader = R"(
    #version 330 core
    
    // Input vertex data, different for all executions of this shader.
    layout(location = 0) in vec2 vPosition;
    
    uniform mat4 objectMatrix;
    uniform mat4 projectionMatrix;

    void main()
    {
      // vertex shader must set gl_Position
      gl_Position = projectionMatrix * objectMatrix * vec4(vPosition, 0, 1);
    }
    )";
    
    // fragment shader
    string fragmentShader = R"(
    #version 330 core
    
    // uniform value representing polygon color
    uniform vec3 color;
    
    // color to use for fragment
    out vec4 finalColor;
    
    void main()
    {
      finalColor = vec4(color, 1.0);
    }
    )";
    
    _shaderProgram.makeProgramFromShaderStrings(vertexShader, fragmentShader);
    
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    
    GLfloat vertices[] = {-0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5,0.5};
    //GLfloat vertices[] = {10, 10, 20, 10, 20, 20, 10, 20};
    
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GL_FLOAT), vertices, GL_STATIC_DRAW);

    // get the integer location for the vPosition attribute
    // in the vertex shader
    _vertexPosition = glGetAttribLocation(_shaderProgram.program(), "vPosition");
    // indicate we will be specifying this attribute using a vertex attribute array
    glEnableVertexAttribArray(_vertexPosition);
    
    // specify the actual vertex data from the buffer
    glVertexAttribPointer(_vertexPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
    
    // initial ball position
    float w = float(windowWidth());
    float h = float(windowHeight());
    _ballLocation = vec2(w - 40, h / 2);
   // paddle location and states of the game
    _paddleLocationY = h/2;
    _paddleIncrement = 4;
    _paddleState = "";
    _gState = "start";
    _pState = "start";
}

void PongRenderer::render() {
    mat4 objectMatrix;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shaderProgram.useProgram();
    glEnableVertexAttribArray(_vertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    // specify the actual vertex data from the buffer
    glVertexAttribPointer(_vertexPosition, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
    
    GLuint color = glGetUniformLocation(_shaderProgram.program(), "color");
    GLuint projection = glGetUniformLocation(_shaderProgram.program(), "projectionMatrix");
    GLuint object = glGetUniformLocation(_shaderProgram.program(), "objectMatrix");
    
    // make orthographic transformation that takes points in which
    // bottom left corner is (0, 0) and top right corner of window is (width, height)
    // and transforms them to bottom left (-1, -1) and top right (1, 1)
    float w = float(windowWidth());
    float h = float(windowHeight());
    mat4 projectionMatrix = Translate(-1.0f, -1.0f, 0.0f) * Scale(2.0f / w, 2.0f / h, 1.0f);
    
    glUniformMatrix4fv(projection, 1, GL_TRUE, projectionMatrix);

    glUniform3f(color, 1.0, 1.0, 1.0);

    // bottom boundary
    objectMatrix = Translate(w/2, 5, 0) * Scale(w, 10, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    // top boundary
    objectMatrix = Translate(w/2, h - 5, 0) * Scale(w, 10, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    // right boundary
    objectMatrix = Translate(w - 5, h/2, 0) * Scale(10, h, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    // render ball
    objectMatrix = Translate(_ballLocation.x, _ballLocation.y, 0) * Scale(10, 10, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    //  render paddle
    objectMatrix = Translate(20, _paddleLocationY, 0) * Scale(10, 80, 1);
    glUniformMatrix4fv(object, 1, GL_TRUE, objectMatrix);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    // velocity for ball
    int velocity = 10;
    
    // gives us a random number to give us random direction for ball
    if ((_ballLocation.x == w - 40)&&(_ballLocation.y == h/2)){
        // get a random number from -2 to 2
        srand(time(nullptr) % INT_MAX);
        float y = (rand() % 21 - 10) / 5.0;
        // use it to initialize ball increment
        _ballIncrement = normalize(vec2(-2, y));
        // make velocity vector have magnitude 10
        _ballIncrement = velocity * _ballIncrement;
    }
    
    

    // ball is within boundaries and game is in play, ball will move
    if (_ballLocation.x > 20 || _ballLocation.x < w - 5){
        if (_gState == "start"){
         _ballLocation.x = _ballLocation.x + _ballIncrement.x;
        }
    }
    if (_ballLocation.y > 5 || _ballLocation.y < h - 5){
        if (_gState == "start"){
            _ballLocation.y = _ballLocation.y + _ballIncrement.y;
        }
    }

    // bounce off the top boundary
    if (_ballLocation.y >= h - 20){
        _ballLocation.y -= _ballIncrement.y;
        
        srand(time(nullptr) % INT_MAX);
        float y = (rand() % 21 - 10) / 5.0;
        // use it to initialize ball increment
        _ballIncrement = normalize(vec2(-2, y));
        // make velocity vector have magnitude 10
        _ballIncrement = velocity * _ballIncrement;
    }
    
    // bounce off the bottom boundary
    if (_ballLocation.y <= 20){
        _ballLocation.y -= _ballIncrement.y;
        
        srand(time(nullptr) % INT_MAX);
        float y = (rand() % 21 - 10) / 5.0;
        // use it to initialize ball increment
        _ballIncrement = normalize(vec2(-2, y));
        // make velocity vector have magnitude 10
        _ballIncrement = velocity * _ballIncrement;

    }
    
    // bounce off right boundary
    if (_ballLocation.x >= w - 20){
        _ballLocation.x -= _ballIncrement.x;
        
        srand(time(nullptr) % INT_MAX);
        float y = (rand() % 21 - 10) / 5.0;
        // use it to initialize ball increment
        _ballIncrement = normalize(vec2(-2, y));
        // make velocity vector have magnitude 10
        _ballIncrement = velocity * _ballIncrement;
    }
    
    // bounce off the paddle and change ball direction
    if((_ballLocation.x <= 25) && (_ballLocation.y <= _paddleLocationY + 40) && (_ballLocation.y >= _paddleLocationY - 40)){
       
        _ballIncrement.x *= -1;
        }
  
    // if game is over, reset location of paddle and ball
    if (_ballLocation.x < 5){
        _paddleLocationY = h/2;
        _ballLocation = vec2(w - 40, h/2);
        _gState = "end";
        }
    
    // ball is currently in play but game needs paused
    // paddle and ball will not move
    if (_pState == "pause"){
        _ballLocation.x += 0;
        _ballLocation.y += 0;
        _paddleLocationY += 0;
    }
    
    // ball in play, ball will  move
    if (_pState == "play"){
        _ballLocation.x += _ballIncrement.x;
        _ballLocation.y += _ballIncrement.y;
    }
    
    // up is pressed and game is in play
    // paddle will move but not touch boundary
    if (_paddleState == "up" && _gState == "start"){
        _paddleLocationY += _paddleIncrement;
        if(_paddleLocationY > h - 55){
            _paddleLocationY = h - 55;
        }
    }
    
    // down is pressed and game is in play
    // paddle will move but not touch boundary
    if (_paddleState == "down" && _gState == "start"){
        _paddleLocationY -= _paddleIncrement;
        if (_paddleLocationY < 55){
            _paddleLocationY = 55;
        }
    }
    
    // up or down is released paddle will not move
    if (_paddleState == "release"){
        _paddleLocationY += 0;
    }
}
void PongRenderer::keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // quit on escape key or q
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    // key press of p
    if ((key == GLFW_KEY_P) && action == GLFW_PRESS){
        // pauses game
        if (_gState == "start"){
            _pState = "pause";
            _gState = "";
        }
        // plays games
        else if (_pState == "pause"){
            _pState = "play";
            _gState = "start";
        }
        // extra pause
        if (_pState == "play"){
            _pState = "pause";
        }
        // start new game
        if( _gState == "end"){
            _gState = "start";
        }
    }
    if ((key == GLFW_KEY_UP) && action == GLFW_PRESS){
        // move paddle up
        _paddleState = "up";
    }
    if ((key == GLFW_KEY_DOWN) && action == GLFW_PRESS){
        // move paddle down
        _paddleState = "down";
    }
    if ((key == GLFW_KEY_UP)||(key == GLFW_KEY_DOWN)){
        if (action == GLFW_RELEASE){
            // stops moving paddle after release
            _paddleState = "release";
        }
    }
}


