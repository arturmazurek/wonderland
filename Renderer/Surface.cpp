//
//  Surface.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "Surface.h"

#include "Vertex.h"

Surface::Surface() : mVerts(nullptr), mNumVerts(0) {
    
}

Surface::Surface(Vertex* verts, int numVerts) : mVerts(verts), mNumVerts(numVerts) {
    
}

Surface::~Surface() {
    delete[] mVerts;
}

void Surface::setVertices(Vertex* vertices, int numVerts) {
    delete[] mVerts;
    
    mVerts = vertices;
    mNumVerts = numVerts;
}