//
//  Material.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Material.h"

#include "RendererData.h"

Material::Material() : rendererData(nullptr), mShader(nullptr) {
    
}

Material::~Material() {
    if(rendererData) {
        delete rendererData;
    }
}

Material* Material::create(const std::string& name) {
    return nullptr;
}
