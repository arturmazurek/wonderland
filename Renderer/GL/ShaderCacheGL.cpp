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

const String ShaderCacheGL::VERTEX_SHADER_EXTENSION(".vs");
const String ShaderCacheGL::FRAGMENT_SHADER_EXTENSION(".fs");

ShaderCacheGL::ShaderCacheGL(const String& basePath) : mBasePath(basePath) {
    
}

ShaderCacheGL::~ShaderCacheGL() {
    HashMap<ShaderGL*>::Iterator iterator = mShaders.iterator();
    while(iterator.hasNext()) {
        delete iterator.next();
    }
}

ShaderGL* ShaderCacheGL::getShader(const String& name, ShaderGL::Type type) {
    String file = fileName(name, type);
    ShaderGL* s = mShaders[file.data()];
    if(!s) {
        s = loadShader(file, type);
        if(s) {
            mShaders[file.data()] = s;
        } else {
            abort();
        }
    }
    return s;
}

ShaderGL* ShaderCacheGL::loadShader(const String& filename, ShaderGL::Type type) const {
    String fullPath = mBasePath  + "/" + filename;
    
    String shaderSource = File::asString(fullPath);
    if(shaderSource.empty()) {
        LOG("Could not load shader source located at: %s", fullPath.data());
        return nullptr;
    }
    
    ShaderGL* shader = new ShaderGL();
    if(!shader->compile(shaderSource.data(), type)) {
        LOG("Could not compile shader named %s, of type 0x%x", filename.data(), type);
        LOG("Info:\n%s\n", shader->getShaderError().c_str());
        
        delete shader;
        return nullptr;
    }
    
    return shader;
}

String ShaderCacheGL::fileName(String shaderName, ShaderGL::Type type) const {
    if(type == ShaderGL::VERTEX_SHADER) {
        shaderName += VERTEX_SHADER_EXTENSION;
    } else {
        shaderName += FRAGMENT_SHADER_EXTENSION;
    }
    return shaderName;
}