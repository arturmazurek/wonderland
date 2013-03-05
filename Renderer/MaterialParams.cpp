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

int MaterialParams::count() const {
    return mParams.size();
}
