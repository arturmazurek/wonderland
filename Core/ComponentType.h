//
//  ComponentType.h
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ComponentType__
#define __Wonderland__ComponentType__

#define COMPONENT_TYPE \
    static const Type type; \
    virtual Type getType() const { return type; }

#endif /* defined(__Wonderland__ComponentType__) */
