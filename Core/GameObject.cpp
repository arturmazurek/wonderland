//
//  GameObject.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject() {
    
}

GameObject::~GameObject() {
    
}

Transform& GameObject::transform() {
    return mTransform;
}