//
//  ComponentType.h
//  Wonderland
//
//  Created by Artur Mazurek on 10.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ComponentType__
#define __Wonderland__ComponentType__

#define DEFINE_TYPE \
    static const Type TYPE; \
    virtual Type getType() const { return TYPE; }

#endif /* defined(__Wonderland__ComponentType__) */
