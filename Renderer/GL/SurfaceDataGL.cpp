//
//  SurfaceDataGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 11.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "SurfaceDataGL.h"

SurfaceDataGL::SurfaceDataGL() : vbo(0) {
    
}

SurfaceDataGL::~SurfaceDataGL() {
    if(vbo) {
        glDeleteBuffers(1, &vbo);
    }
}