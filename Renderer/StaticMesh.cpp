//
//  StaticMesh.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 08/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "StaticMesh.h"

#include "Surface.h"

StaticMesh::StaticMesh() {
    
}

StaticMesh::~StaticMesh() {
    LinkedList<SurfaceInfo>::Iterator iterator = mSurfaces.iterator();
    while(iterator.hasNext()) {
        SurfaceInfo& si = iterator.next();
        if(si.own) {
            delete si.surface;
        }
    }
}

void StaticMesh::addSurface(Surface* surface, Material* material) {
    mSurfaces.add({surface, material, false});
}

void StaticMesh::addSurface(Surface* surface, Material* material, bool willOwnSurface) {
    mSurfaces.add({surface, material});
}