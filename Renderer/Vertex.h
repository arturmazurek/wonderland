//
//  Vertex.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Vertex__
#define __Wonderland__Vertex__

#include "Math/Vector.h"

struct Vertex {
    enum {
        ATTR_POS,
        ATTR_NORMAL,
        ATTR_UV,
        
        ATTR_ENUM_SIZE
    };
    
    Vector pos;
    float normal[3];
    float uv[2];
};

#endif /* defined(__Wonderland__Vertex__) */
