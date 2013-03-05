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
#include "Util/UniquePtr.h"

#include "HMaterial.h"

class MaterialParams;

class MaterialInstance {
public:
    MaterialInstance(const HMaterial& parent);
    ~MaterialInstance();
    
    const HMaterial& parent() const;
    
    void setParameter(const String& paramName, void* value, int size);
    void assignParameters(UniquePtr<MaterialParams> parameters);
    
    const MaterialParams& getParams() const;
    
    UniquePtr<MaterialInstance> clone() const;
    
private:
    bool                        mCopied;
    HMaterial                   mParent;
    SharedPtr<MaterialParams>   mParams;
};
		
#endif /* defined(__Wonderland__MaterialInstance__) */
