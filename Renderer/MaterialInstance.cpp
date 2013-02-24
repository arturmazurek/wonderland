//
//  MaterialInstance.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 23.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "MaterialInstance.h"

#include "Material.h"

MaterialInstance::MaterialInstance(Material* parent) : mParent(parent) {
    
}

MaterialInstance::~MaterialInstance() {
    
}

Material* MaterialInstance::parent() const {
    return mParent;
}