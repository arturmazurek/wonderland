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

#include "Util/UniquePtr.h"

class ShaderGL;

class MaterialGL : public Material {
public:
    MaterialGL(const std::string& name);
    ~MaterialGL();
    
    bool buildMaterial(ShaderGL* vertexShader, ShaderGL* fragmentShader);
    
    bool generated;
    
    GLuint program;
    GLint modelViewUniform;
    GLint projectionUniform;
    GLint colorUniform;
    
private:
    static const std::string ATTRIBUTE_NAMES[];
};

#endif /* defined(__Wonderland__MaterialGL__) */
