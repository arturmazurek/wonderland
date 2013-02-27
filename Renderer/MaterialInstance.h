//
//  MaterialInstance.h
//  Wonderland
//
//  Created by Artur Mazurek on 23.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialInstance__
#define __Wonderland__MaterialInstance__

#include <string>

#include "Util/SharedPtr.h"

class Material;
struct MaterialInstanceParams;

class MaterialInstance {
public:
    MaterialInstance(Material* parent);
    ~MaterialInstance();
    
    Material* parent() const;
    
    void setParameter(const std::string& paramName, float* value, int size);
    
    MaterialInstance* clone() const;
    
private:
    bool                                mCopied;
    Material*                           mParent;
    SharedPtr<MaterialInstanceParams>   mParams;
};

#endif /* defined(__Wonderland__MaterialInstance__) */
