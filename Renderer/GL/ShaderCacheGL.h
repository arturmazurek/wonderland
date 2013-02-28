//
//  ShaderCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ShaderCacheGL__
#define __Wonderland__ShaderCacheGL__

#include "Util/HashMap.h"
#include "Util/String.h"

#include "ShaderGL.h"

class ShaderCacheGL {
public:
    ShaderCacheGL(const String& basePath);
    ~ShaderCacheGL();
    
    ShaderGL* getShader(const String& name, ShaderGL::Type type);
    
private:
    ShaderCacheGL(ShaderCacheGL&);
    ShaderCacheGL& operator=(ShaderCacheGL&);
    
    ShaderGL* loadShader(const String& name, ShaderGL::Type type) const;
    
    String fileName(String shaderName, ShaderGL::Type type) const;
    
private:
    static const String    VERTEX_SHADER_EXTENSION;
    static const String    FRAGMENT_SHADER_EXTENSION;
    
    const String           mBasePath;
    HashMap<ShaderGL*>     mShaders;
};

#endif /* defined(__Wonderland__ShaderCacheGL__) */
