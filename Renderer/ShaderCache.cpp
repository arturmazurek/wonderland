//
//  ShaderCache.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ShaderCache.h"

ShaderCache::ShaderCache() {
    
}

ShaderCache::~ShaderCache() {
    
}

Shader* ShaderCache::getShader(const std::string& name) {
    Shader* s = mShaders[name.c_str()];
    if(!s) {
        s = loadShader(name);
    }
    return s;
}

Shader* ShaderCache::loadShader(const std::string& name) {
    
}

