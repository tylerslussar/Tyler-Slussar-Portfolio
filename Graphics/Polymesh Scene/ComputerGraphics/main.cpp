//
//  main.cpp
//  
//
//  Created by David M. Reed on 12/21/21.
//  Copyright (c) 2021 David Reed. All rights reserved.
//

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;

#include "graphics.hpp"
#include "PolymeshSceneRenderer.hpp"

//----------------------------------------------------------------------

int main(int argc, const char * argv[]) {
    string filename;
    if (argc > 1) {
        filename = argv[1];
    }
    else {
//        cout << "enter filename: ";
//        cin >> filename;
        filename = "/path/to/file/on/your/computer/in.txt";
    }

    // create the class
    Renderer *renderer = new PolymeshSceneRenderer("Polymesh", 960, 540, "/Users/tyslu/Library/CloudStorage/OneDrive-Personal/Documents/School Documents/JR Cap/Spring/Computer Graphics/Lab 5/PolymeshScene-renderPolymesh/ComputerGraphics/Lab5Data.txt");

    // and enter the run loop
    // false parameter will cause render method to be called repeatedly instead of just on events
    renderer->runLoop(false);
}
