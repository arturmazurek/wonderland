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
#include "Util/SharedPtr.h"
#include "Util/UniquePtr.h"

class Surface;
class MaterialInstance;

class StaticMesh {
public:
    StaticMesh();
    ~StaticMesh();
    
    void addSurface(SharedPtr<Surface> surface, UniquePtr<MaterialInstance> material);
    
    struct SurfaceInfo {
        SharedPtr<Surface> surface;
        MaterialInstance* material;
    };
    typedef LinkedList<SurfaceInfo>::Iterator SurfacesIterator;
    SurfacesIterator surfacesIterator();
    
private:
    LinkedList<SurfaceInfo> mSurfaces;
};

#endif /* defined(__Wonderland__StaticMesh__) */
