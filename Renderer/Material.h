//
//  Material.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Material__
#define __Wonderland__Material__

#include "Util/Array.h"
#include "Util/String.h"
#include "Util/UniquePtr.h"

class MaterialParams;

/**
 * Material is a shader with associated parameters
 * There is one material per surface. Each has its own instance
 * and that allows to tweak material properies to be shown later on.
 */
class Material {
public:
    Material(const String& name);
    virtual ~Material();
    
    const String& name() const;
    
    virtual UniquePtr<MaterialParams> createParams() const = 0;
    virtual void apply(const MaterialParams& params) = 0;
    
    void setDefaults(MaterialParams& param) const;
    
private:
    String     mName;
};

#endif /* defined(__Wonderland__Material__) */
