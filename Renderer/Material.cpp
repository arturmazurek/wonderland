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

Material::Material(const String& name) : mName(name) {
    
}

Material::~Material() {

}

const String& Material::name() const {
    return mName;
}

static MaterialParam* _findParam(const String& name, Array<MaterialParam>& params) {
    for(int i = 0; i < params.size(); ++i) {
        if(name == params[i].name) {
            return &params[i];
        }
    }
    
    return nullptr;
}

void Material::setDefaults(Array<MaterialParam>& params) {
    MaterialParam* param = _findParam("color", params);
    param->type = PARAM_TYPE_VEC4;
    param->size = 4 * sizeof(float);
    param->value = malloc(param->size);
    float values[] = {0.f, 1.f, 0.f, 1.f};
    memcpy(param->value, values, param->size);
}