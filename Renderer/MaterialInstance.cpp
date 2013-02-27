//
//  MaterialInstance.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 23.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialInstance.h"

#include "Util/Log.h"

#include "Material.h"

struct MaterialInstanceParams {
    MaterialInstanceParams(MaterialInstanceParams* other) : params(other->params) {}
    
    Array<MaterialParam> params;
};

MaterialInstance::MaterialInstance(Material* parent) : mCopied(false), mParent(parent) {
    
}

MaterialInstance::~MaterialInstance() {
    
}

Material* MaterialInstance::parent() const {
    return mParent;
}

static MaterialParam* _getParameter(const std::string& name, Array<MaterialParam>& from) {
    for(int i = 0; i < from.size(); ++i) {
        if(from[i].name == name) {
            return &from[i];
        }
    }
    
    return nullptr;
}

void MaterialInstance::setParameter(const std::string& name, float* value, int size) {
    if(!mCopied) {
        MaterialInstanceParams* copy = new MaterialInstanceParams(mParams.get());
        mParams.reset(copy);
        mCopied = true;
    }
    
    MaterialParam* param = _getParameter(name, mParams->params);
    if(param->size != size) {
        LOG("Oops, trying to set %s in %s with something of size %d but destination expectes size %d", name.c_str(), mParent->name().c_str(), size, param->size);
        return;
    }
    memcpy(param->value, value, size);
}

MaterialInstance* MaterialInstance::clone() const {
    MaterialInstance* result = new MaterialInstance(mParent);
    result->mParams = mParams;
    
    return result;
}