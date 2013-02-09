//
//  MaterialCacheGL.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialCacheGL.h"

#include "Util/Log.h"

#include "MaterialGL.h"
#include "OpenGL.h"
#include "ShaderCacheGL.h"
#include "ShaderGL.h"

MaterialCacheGL::MaterialCacheGL(const std::string& basePath) : mBasePath(basePath) {
    mShaderCache = new ShaderCacheGL(mBasePath);
}

MaterialCacheGL::~MaterialCacheGL() {
    delete mShaderCache;
    
    HashMap<MaterialGL*>::Iterator iterator = mMaterials.iterator();
    while(iterator.hasNext()) {
        delete iterator.next();
    }
}

MaterialGL* MaterialCacheGL::getMaterial(const std::string& name) {
    MaterialGL* material = mMaterials[name.c_str()];
    if(!material) {
        material = loadMaterial(name);
        if(!material) {
            LOG("Could not load material named %s", name.c_str());
            abort();
        }
        mMaterials[name.c_str()] = material;
    }
    return material;
}

MaterialGL* MaterialCacheGL::loadMaterial(const std::string& name) {
    // at the moment material consists only of a vertex and fragment shaders
    // named identically
    ShaderGL* vertexShader = mShaderCache->getShader(name, ShaderGL::VERTEX_SHADER);
    if(!vertexShader) {
        LOG("Could not get vertex shader %s", name.c_str());
        return nullptr;
    }
    
    ShaderGL* fragmentShader = mShaderCache->getShader(name, ShaderGL::FRAGMENT_SHADER);
    if(!fragmentShader) {
        LOG("Could not get fragment shader %s", name.c_str());
        return nullptr;
    }
    
    MaterialGL* result = new MaterialGL();
    result->program = glCreateProgram();
    glAttachShader(result->program, vertexShader->shader);
    glAttachShader(result->program, fragmentShader->shader);
    glLinkProgram(result->program);
    
    GLint linkSuccessful;
    glGetProgramiv(result->program, GL_LINK_STATUS, &linkSuccessful);
    if(linkSuccessful == GL_FALSE) {
        LOG("Could not link material %s", name.c_str());
        delete result;
        result = nullptr;
    }
    
    return result;
}
