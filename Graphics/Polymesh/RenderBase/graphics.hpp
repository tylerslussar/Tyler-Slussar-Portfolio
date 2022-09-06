//
//  graphics.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/17/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef graphics_h
#define graphics_h

// include the files necessary in the proper order since order matters for some of them

#include <memory>
#include <vector>

//#ifndef __APPLE__
#include <GL/glew.h>
//#endif

#include "GLFW/glfw3.h"
#include "Utils.hpp"
#include "ShaderProgram.hpp"

#include "Angel.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "Line.hpp"
#include "Drawable.hpp"
#include "PointDrawable.hpp"
#include "ColoredPointDrawable.hpp"
#include "PolyLineDrawable.hpp"
#include "LineStripDrawable.hpp"
#include "LineDrawable.hpp"
#include "Renderer.hpp"


#endif /* graphics_h */
