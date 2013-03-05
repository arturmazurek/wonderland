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
#include "MaterialParams.h"

MaterialInstance::MaterialInstance(const HMaterial& parent) : mCopied(false), mParent(parent) {
    
}

MaterialInstance::~MaterialInstance() {
    
}

const HMaterial& MaterialInstance::parent() const {
    return mParent;
}

void MaterialInstance::setParameter(const String& name, void* value, int size) {
    if(!mCopied) {
        MaterialParams* copy = new MaterialParams(*mParams.get());
        mParams.reset(copy);
        mCopied = true;
    }
    
    MaterialParams::Parameter* param = mParams->getParameter(name);
    if(!param) {
        LOG("Oops, could not find parameter %s", name.data());
        return;
    }
    if(param->size != size) {
        LOG("Oops, trying to set %s with something of size %d but destination expectes size %d", name.data(), size, param->size);
        return;
    }
    
    memcpy(param->value, value, size);
}

UniquePtr<MaterialInstance> MaterialInstance::clone() const {
    UniquePtr<MaterialInstance> result(new MaterialInstance(mParent));
    result->mParams = mParams;
    
    return result;
}

void MaterialInstance::assignParameters(UniquePtr<MaterialParams> params) {
    mParams.reset(params.release());
}

const MaterialParams& MaterialInstance::getParams() const {
    return *mParams;
}
