//
//  Material.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Material.h"

#include "Util/Log.h"

#include "MaterialParams.h"

Material::Material(const String& name) : mName(name) {
    
}

Material::~Material() {

}

const String& Material::name() const {
    return mName;
}

void Material::setDefaults(MaterialParams& params) const {
//    MaterialParam* param = _findParam("uColor", params);
    MaterialParams::Parameter* param = params.getParameter("uColor");
    
    if(!param) {
        LOG("Can't find param named %s for %s", "color", mName.data());
        return;
    }
    
    param->type = MaterialParams::TYPE_VEC4;
    param->size = 4 * sizeof(float);
    param->value = malloc(param->size);
    float values[] = {0.f, 1.f, 0.f, 1.f};
    memcpy(param->value, values, param->size);
}