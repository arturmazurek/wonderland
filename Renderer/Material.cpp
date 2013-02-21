//
//  Material.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Material.h"

Material::Material(const std::string& name) : mName(name) {
    
}

Material::~Material() {

}

const std::string& Material::name() const {
    return mName;
}