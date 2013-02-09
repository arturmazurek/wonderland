//
//  ShaderGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ShaderGL__
#define __Wonderland__ShaderGL__

#include "Util/OpenGL.h"

struct ShaderGL {
    enum Type {
        TYPE_INVALID,
        
        VERTEX_SHADER = GL_VERTEX_SHADER,
        FRAGMENT_SHADER = GL_FRAGMENT_SHADER
    };
    
    ShaderGL();
    virtual ~ShaderGL();
    
    bool compile(const GLchar* body, Type type);
    
    GLuint  shader;
    Type    type;
};

#endif /* defined(__Wonderland__ShaderGL__) */
