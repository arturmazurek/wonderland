//
//  ComponentBase.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ComponentBase.h"

ComponentBase::ComponentBase() : mOwner(nullptr) {
    
}

ComponentBase::~ComponentBase() {

}

GameObject* ComponentBase::owner() {
    return mOwner;
}

void ComponentBase::setOwner(GameObject* owner) {
    mOwner = owner;
}