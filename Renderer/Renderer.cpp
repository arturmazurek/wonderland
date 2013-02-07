//
//  Renderer.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 03.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Renderer.h"

#include "GL/RendererGL.h"

Renderer* Renderer::instance() {
    static Renderer* renderer = new RendererGL();
    return renderer;
}

Renderer::Renderer() {
    
}

Renderer::~Renderer() {
    
}