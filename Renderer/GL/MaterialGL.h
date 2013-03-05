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

#include "Util/String.h"
#include "Util/UniquePtr.h"

class ShaderGL;

class MaterialGL : public Material {
public:
    static const String IGNORED_UNIFORMS[];
    
    MaterialGL(const String& name);
    ~MaterialGL();
    
    virtual UniquePtr<MaterialParams> createParams() const override;
    virtual void apply(const MaterialParams& params) override;
    
    bool buildMaterial(ShaderGL* vertexShader, ShaderGL* fragmentShader);
    
    bool generated;
    
    GLuint program;
    GLint modelViewUniform;
    GLint projectionUniform;
    GLint colorUniform;
    
private:
    static const String ATTRIBUTE_NAMES[];
    
    bool mLinked;
};

#endif /* defined(__Wonderland__MaterialGL__) */
