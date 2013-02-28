//
//  MaterialInstance.h
//  Wonderland
//
//  Created by Artur Mazurek on 23.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialInstance__
#define __Wonderland__MaterialInstance__

#include "Util/String.h"

#include "Util/Array.h"
#include "Util/SharedPtr.h"

#include "Material.h"

struct MaterialInstanceParams;

class MaterialInstance {
public:
    MaterialInstance(Material* parent);
    ~MaterialInstance();
    
    Material* parent() const;
    
    void setParameter(const String& paramName, void* value, int size);
    void assignParameters(const Array<MaterialParam>& parameters);
    
    const Array<MaterialParam>& getParams() const;
    
    MaterialInstance* clone() const;
    
private:
    bool                                mCopied;
    Material*                           mParent;
    SharedPtr<MaterialInstanceParams>   mParams;
};

#endif /* defined(__Wonderland__MaterialInstance__) */
