//
//  MaterialParams.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 05/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialParams.h"

MaterialParams::MaterialParams() {
    
}

MaterialParams::~MaterialParams() {
    
}

MaterialParams::MaterialParams(const MaterialParams& other) : mParams(other.mParams) {
    
}

MaterialParams& MaterialParams::operator=(const MaterialParams& other) {
    mParams = other.mParams;
    return *this;
}

void MaterialParams::addParameter(const Parameter& parameter) {
    mParams.add(parameter);
}

MaterialParams::Parameter& MaterialParams::getParameter(int i) {
    return mParams[i];
}

const MaterialParams::Parameter& MaterialParams::getParameter(int i) const {
    return mParams[i];
}

MaterialParams::Parameter* MaterialParams::getParameter(const String& name) {
    int n = count();
    for(int i = 0; i < n; ++i) {
        if(mParams[i].name == name) {
            return &mParams[i];
        }
    }
    
    return nullptr;
}

const MaterialParams::Parameter* MaterialParams::getParameter(const String& name) const {
    return const_cast<MaterialParams&>(*this).getParameter(name);
}

int MaterialParams::count() const {
    return mParams.size();
}
