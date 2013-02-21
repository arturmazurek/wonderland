//
//  Material.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Material__
#define __Wonderland__Material__

#include <string>

struct RendererData;

/**
 * Material is a shader with associated parameters
 * There is one material per surface. Each has its own instance
 * and that allows to tweak material properies to be shown later on.
 */
class Material {
public:
    Material(const std::string& name);
    virtual ~Material();
    
    RendererData*   rendererData;
    
    const std::string& name() const;
    
private:
    std::string mName;
};

#endif /* defined(__Wonderland__Material__) */
