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

#include "../ShaderCache.h"

class Shader;

class ShaderCacheGL : ShaderCache {
public:
    ShaderCacheGL(const std::string& basePath);
    virtual ~ShaderCacheGL();
    
    virtual Shader* loadShader(const std::string& name) override;
    
private:
    const std::string mBasePath;
};

#endif /* defined(__Wonderland__ShaderCacheGL__) */
