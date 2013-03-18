//
//  ComponentType.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "ComponentType.h"

#include "CameraComponent.h"
#include "ComponentBase.h"
#include "StaticMeshComponent.h"

#define CREATE_TYPE(componentClass, number) \
    const ComponentBase::Type componentClass::TYPE = number;

CREATE_TYPE(StaticMeshComponent, 1);
CREATE_TYPE(CameraComponent, 2);