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

}

void StaticMesh::addSurface(Surface* surface, Material* material) {
    mSurfaces.add({surface, material});
}

StaticMesh::SurfacesIterator StaticMesh::surfacesIterator() {
    return mSurfaces.iterator();
}