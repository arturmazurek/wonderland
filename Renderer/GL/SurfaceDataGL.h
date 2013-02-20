//
//  SurfaceDataGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 11.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SurfaceDataGL__
#define __Wonderland__SurfaceDataGL__

#include "Renderer/SurfaceData.h"

#include "OpenGL.h"

struct SurfaceDataGL : SurfaceData {
    SurfaceDataGL();
    virtual ~SurfaceDataGL();
    
    GLuint vbo;
    GLuint vao;
};

#endif /* defined(__Wonderland__SurfaceDataGL__) */
