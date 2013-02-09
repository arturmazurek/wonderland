//
//  ShaderCache.h
//  Wonderland
//
//  Created by Artur Mazurek on 08.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ShaderCache__
#define __Wonderland__ShaderCache__

#include <string>

#include "Util/HashMap.h"

#include "Shader.h"

class ShaderCache {
public:
    ShaderCache();
    virtual ~ShaderCache();

    Shader* getShader(const std::string& name);

protected:
    virtual Shader* loadShader(const std::string& name) = 0;
    
private:
    ShaderCache(const ShaderCache&);
    ShaderCache& operator=(const ShaderCache&);

private:
    HashMap<Shader*> mShaders;
};

#endif /* defined(__Wonderland__ShaderCache__) */
