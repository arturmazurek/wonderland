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
    mShaderCache.reset(new ShaderCacheGL(mBasePath));
}

MaterialCacheGL::~MaterialCacheGL() {

}

UniquePtr<Material> MaterialCacheGL::createMaterial(const String& name) {
    UniquePtr<MaterialGL> material(loadMaterial(name));
    if(!material) {
        LOG("Could not load material named %s", name.data());
        abort();
    }
    return material;
}

UniquePtr<MaterialGL> MaterialCacheGL::loadMaterial(const String& name) {
    // at the moment material consists only of a vertex and fragment shaders
    // named identically
    ShaderGL* vertexShader = mShaderCache->getShader(name, ShaderGL::VERTEX_SHADER);
    if(!vertexShader) {
        LOG("Could not get vertex shader %s", name.data());
        return UniquePtr<MaterialGL>();
    }
    
    ShaderGL* fragmentShader = mShaderCache->getShader(name, ShaderGL::FRAGMENT_SHADER);
    if(!fragmentShader) {
        LOG("Could not get fragment shader %s", name.data());
        return UniquePtr<MaterialGL>();
    }
    
    UniquePtr<MaterialGL> result(new MaterialGL(name));
    if(!result->buildMaterial(vertexShader, fragmentShader)) {
        LOG("Could not build material");
        result.reset();
    }
    
    return result;
}
