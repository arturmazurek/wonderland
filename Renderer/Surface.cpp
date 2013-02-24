//
//  Surface.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Surface.h"

#include "SurfaceData.h"
#include "Vertex.h"

Surface::Surface() : mNumVerts(0) {
    
}

Surface::Surface(UniqueArray<Vertex> verts, int numVerts) : mVerts(verts), mNumVerts(numVerts) {
    
}

Surface::~Surface() {
}

void Surface::setVertices(UniqueArray<Vertex> vertices, int numVerts) {
    mVerts = vertices;
    mNumVerts = numVerts;
}

const Vertex* Surface::vertices() const {
    return mVerts.get();
}

int Surface::verticesCount() const {
    return mNumVerts;
}