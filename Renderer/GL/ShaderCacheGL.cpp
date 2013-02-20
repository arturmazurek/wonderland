//
//  ShaderCacheGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ShaderCacheGL.h"

#include "Util/File.h"
#include "Util/Log.h"

#include "ShaderGL.h"

const std::string ShaderCacheGL::VERTEX_SHADER_EXTENSION(".vs");
const std::string ShaderCacheGL::FRAGMENT_SHADER_EXTENSION(".fs");

ShaderCacheGL::ShaderCacheGL(const std::string& basePath) : mBasePath(basePath) {
    
}

ShaderCacheGL::~ShaderCacheGL() {
    HashMap<ShaderGL*>::Iterator iterator = mShaders.iterator();
    while(iterator.hasNext()) {
        delete iterator.next();
    }
}

ShaderGL* ShaderCacheGL::getShader(const std::string& name, ShaderGL::Type type) {
    ShaderGL* s = mShaders[fileName(name, type).c_str()];
    if(!s) {
        s = loadShader(name, type);
        if(s) {
            mShaders[fileName(name, type).c_str()] = s;
        } else {
            abort();
        }
    }
    return s;
}

ShaderGL* ShaderCacheGL::loadShader(const std::string& name, ShaderGL::Type type) const {
    std::string fullPath = mBasePath  + "/" + fileName(name, type);
    
    std::string shaderSource = File::asString(fullPath);
    if(shaderSource.empty()) {
        LOG("Could not load shader source located at: %s", fullPath.c_str());
        return nullptr;
    }
    
    ShaderGL* shader = new ShaderGL();
    if(!shader->compile(shaderSource.c_str(), type)) {
        LOG("Could not compile shader named %s, of type 0x%x", name.c_str(), type);
        LOG("Info:\n%s\n", shader->getShaderError().c_str());
        
        delete shader;
        return nullptr;
    }
    
    return shader;
}

std::string ShaderCacheGL::fileName(std::string shaderName, ShaderGL::Type type) const {
    if(type == ShaderGL::VERTEX_SHADER) {
        shaderName += VERTEX_SHADER_EXTENSION;
    } else {
        shaderName += FRAGMENT_SHADER_EXTENSION;
    }
    return shaderName;
}