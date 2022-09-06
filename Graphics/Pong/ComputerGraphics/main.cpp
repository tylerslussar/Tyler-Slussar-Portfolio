//
//  main.cpp
//  
//
//  Created by David M. Reed on 2/18/15.
//  Copyright (c) 2015 David Reed. All rights reserved.
//

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

#include "graphics.hpp"
#include "PongRenderer.hpp"

//----------------------------------------------------------------------

int main(int argc, const char * argv[]) {
    // create the class
    Renderer *renderer = new PongRenderer("Renderer", 960, 540);

    // and enter the run loop
    renderer->runLoop(false);
}
