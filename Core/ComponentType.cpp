//
//  ComponentType.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ComponentType.h"

#include "ComponentBase.h"
#include "StaticMeshComponent.h"

#define DEFINE_TYPE(componentClass, number) \
    const ComponentBase::Type componentClass::type = number;

DEFINE_TYPE(StaticMeshComponent, 1);