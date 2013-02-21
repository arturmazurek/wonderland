//
//  RendererDataGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 12.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__RendererDataGL__
#define __Wonderland__RendererDataGL__

#include <string>

#include "OpenGL.h"

struct RendererDataGL {
    RendererDataGL();
    ~RendererDataGL();
    
    GLint modelViewUniform;
    GLint projectionUniform;
    GLint colorUniform;
};

#endif /* defined(__Wonderland__RendererDataGL__) */
