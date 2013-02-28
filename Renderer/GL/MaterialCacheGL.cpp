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
#include "Vertex.h"

MaterialCacheGL::MaterialCacheGL(const String& basePath) : mBasePath(basePath) {
    mShaderCache = new ShaderCacheGL(mBasePath);
}

MaterialCacheGL::~MaterialCacheGL() {
    delete mShaderCache;
    
    HashMap<MaterialGL*>::Iterator iterator = mMaterials.iterator();
    while(iterator.hasNext()) {
        delete iterator.next();
    }
}

Material* MaterialCacheGL::getMaterial(const String& name) {
    MaterialGL* material = mMaterials[name.data()];
    if(!material) {
        material = loadMaterial(name);
        if(!material) {
            LOG("Could not load material named %s", name.data());
            abort();
        }
        mMaterials[name.data()] = material;
    }
    return material;
}

MaterialGL* MaterialCacheGL::loadMaterial(const String& name) {
    // at the moment material consists only of a vertex and fragment shaders
    // named identically
    ShaderGL* vertexShader = mShaderCache->getShader(name, ShaderGL::VERTEX_SHADER);
    if(!vertexShader) {
        LOG("Could not get vertex shader %s", name.data());
        return nullptr;
    }
    
    ShaderGL* fragmentShader = mShaderCache->getShader(name, ShaderGL::FRAGMENT_SHADER);
    if(!fragmentShader) {
        LOG("Could not get fragment shader %s", name.data());
        return nullptr;
    }
    
    MaterialGL* result = new MaterialGL(name);
    if(!result->buildMaterial(vertexShader, fragmentShader)) {
        LOG("Could not build material");
        delete result;
        return nullptr;
    }
    
    return result;
}
