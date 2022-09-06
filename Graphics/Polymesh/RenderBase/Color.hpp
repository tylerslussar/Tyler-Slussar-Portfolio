//
//  Color.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

class Color {
public:
    /// create specified color
    Color(float red = 0, float green = 0, float blue = 0);

    /// set specified color
    void set(float red, float green, float blue);

    // public data for convenience
    float r, g, b;
};

inline Color::Color(float red, float green, float blue) {
    set(red, green, blue);
}

inline void Color::set(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}

#endif /* Color_hpp */
