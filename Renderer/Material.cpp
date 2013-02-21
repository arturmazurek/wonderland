//
//  Material.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Material.h"

#include "RendererData.h"

Material::Material(const std::string& name) : rendererData(nullptr), mName(name) {
    
}

Material::~Material() {
    if(rendererData) {
        delete rendererData;
    }
}

const std::string& Material::name() const {
    return mName;
}