//
//  RendererGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "RendererGL.h"

#include "Util/Constants.h"

#include "MaterialCacheGL.h"
#include "MaterialGL.h"

RendererGL::RendererGL() {
    mMaterialCache = new MaterialCacheGL(Constants::RESOURCES_BASE);
}

RendererGL::~RendererGL() {
    delete mMaterialCache;
}

void RendererGL::renderFrame() {
    
}

Material* RendererGL::createMaterial(const std::string& name) {
    return nullptr;
}