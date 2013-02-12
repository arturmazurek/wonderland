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

Surface::Surface() : surfaceData(nullptr), mVerts(nullptr), mNumVerts(0) {
    
}

Surface::Surface(Vertex* verts, int numVerts) : surfaceData(nullptr), mVerts(verts), mNumVerts(numVerts) {
    
}

Surface::~Surface() {
    delete[] mVerts;
    delete surfaceData;
}

void Surface::setVertices(Vertex* vertices, int numVerts) {
    delete[] mVerts;
    
    mVerts = vertices;
    mNumVerts = numVerts;
}

const Vertex* Surface::vertices() const {
    return mVerts;
}

int Surface::verticesCount() const {
    return mNumVerts;
}