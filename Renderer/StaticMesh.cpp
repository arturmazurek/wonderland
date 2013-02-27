//
//  StaticMesh.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "StaticMesh.h"

#include "MaterialInstance.h"
#include "Surface.h"

StaticMesh::StaticMesh() {
    
}

StaticMesh::~StaticMesh() {
    SurfacesIterator iter = surfacesIterator();
    while(iter.hasNext()) {
        SurfaceInfo& si = iter.next();
        delete si.material;
    }
}

void StaticMesh::addSurface(SharedPtr<Surface> surface, UniquePtr<MaterialInstance> material) {
    mSurfaces.add({surface, material.release()});
}

StaticMesh::SurfacesIterator StaticMesh::surfacesIterator() {
    return mSurfaces.iterator();
}

MaterialInstance* StaticMesh::getMaterial(Surface* ofSurface) {
    SurfacesIterator iter = surfacesIterator();
    while(iter.hasNext()) {
        SurfaceInfo& si = iter.next();
        
        if(si.surface == ofSurface) {
            return si.material;
        }
    }
    
    return nullptr;
}