//
//  MaterialGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialGL__
#define __Wonderland__MaterialGL__

#include "../Material.h"

#include "OpenGL.h"

class MaterialGL : public Material {
public:
    MaterialGL();
    ~MaterialGL();
    
    GLuint program;
};

#endif /* defined(__Wonderland__MaterialGL__) */
