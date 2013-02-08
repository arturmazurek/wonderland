//
//  StaticMesh.h
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__StaticMesh__
#define __Wonderland__StaticMesh__

#include "Util/LinkedList.h"

class Surface;
class Material;

class StaticMesh {
public:
    StaticMesh();
    ~StaticMesh();
    
    void addSurface(Surface* surface, Material* material);
    
private:
    struct SurfaceInfo {
        Surface* surface;
        Material* material;
    };
    
    LinkedList<SurfaceInfo> mSurfaces;
};

#endif /* defined(__Wonderland__StaticMesh__) */
