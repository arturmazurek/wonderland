//
//  ShaderCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ShaderCacheGL__
#define __Wonderland__ShaderCacheGL__

#include <string>

#include "Util/HashMap.h"

#include "ShaderGL.h"

class ShaderCacheGL {
public:
    ShaderCacheGL(const std::string& basePath);
    ~ShaderCacheGL();
    
    ShaderGL* getShader(const std::string& name, ShaderGL::Type type);
    
private:
    ShaderCacheGL(ShaderCacheGL&);
    ShaderCacheGL& operator=(ShaderCacheGL&);
    
    ShaderGL* loadShader(const std::string& name, ShaderGL::Type type) const;
    
private:
    static const std::string    VERTEX_SHADER_EXTENSION;
    static const std::string    FRAGMENT_SHADER_EXTENSION;
    
    const std::string           mBasePath;
    HashMap<ShaderGL*>          mShaders;
};

#endif /* defined(__Wonderland__ShaderCacheGL__) */
