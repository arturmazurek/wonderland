//
//  MaterialCacheGL.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialCacheGL__
#define __Wonderland__MaterialCacheGL__

#include <string>

#include "Util/HashMap.h"

class MaterialGL;
class ShaderCacheGL;

class MaterialCacheGL {
public:
    MaterialCacheGL(const std::string& basePath);
    ~MaterialCacheGL();

    MaterialGL* getMaterial(const std::string& name);
    
private:
    MaterialCacheGL(const MaterialCacheGL&);
    MaterialCacheGL& operator=(const MaterialCacheGL&);
    
    MaterialGL* loadMaterial(const std::string& name);

private:
    const std::string       mBasePath;
    HashMap<MaterialGL*>    mMaterials;
    ShaderCacheGL*          mShaderCache;
};

#endif /* defined(__Wonderland__MaterialCacheGL__) */
