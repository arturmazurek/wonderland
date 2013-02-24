//
//  MaterialInstance.h
//  Wonderland
//
//  Created by Artur Mazurek on 23.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__MaterialInstance__
#define __Wonderland__MaterialInstance__

class Material;

class MaterialInstance {
public:
    MaterialInstance(Material* parent);
    ~MaterialInstance();
    
    Material* parent() const;
    
private:
    Material* mParent;
};

#endif /* defined(__Wonderland__MaterialInstance__) */
