//
//  Surface.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Surface__
#define __Wonderland__Surface__

struct Vertex;

// Surface owns its vertices - there should be just
// one surface with the given vertices anyway
class Surface {
public:
    Surface();
    Surface(Vertex* verts, int numVertices);
    ~Surface();
    
    void setVertices(Vertex* verts, int numVerts);
    
private:
    Surface(const Surface&);
    Surface& operator=(const Surface&);

private:
    Vertex* mVerts;
    int mNumVerts;
};

#endif /* defined(__Wonderland__Surface__) */
