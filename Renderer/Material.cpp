//
//  Material.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Material.h"

MaterialParam::MaterialParam() : handle(0), value(nullptr), size(0), type(PARAM_TYPE_INVALID) {
}

MaterialParam::~MaterialParam() {
    free(value);
}

MaterialParam::MaterialParam(const MaterialParam& other) : name(other.name), handle(other.handle), value(nullptr), type(other.type) {
    if(other.value) {
        size = other.size;
        value = malloc(size);
        memcpy(value, other.value, size);
    }
}

MaterialParam& MaterialParam::operator=(const MaterialParam& other) {
    name = other.name;
    handle = other.handle;
    if(other.value) {
        size = other.size;
        value = malloc(size);
        memcpy(value, other.value, size);
    } else {
        value = nullptr;
        size = 0;
    }
    type = other.type;
    
    return *this;
}

Material::Material(const std::string& name) : mName(name) {
    
}

Material::~Material() {

}

const std::string& Material::name() const {
    return mName;
}