//
//  RendererFactory.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "RendererFactory.h"

#include <cassert>

#include "GL/OpenGL.h"
#include "GL/RendererGL.h"

Renderer* RendererFactory::createRenderer(RendererType type) {
    switch (type) {
        case RENDERER_OPENGL:
            return createRendererGL();
            break;
            
        default:
            assert(!"Unknown type");
            return createRendererGL();
            break;
    }
}

Renderer* RendererFactory::createRendererGL() {
    return new RendererGL();
}