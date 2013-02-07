//
//  SceneNode.h
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SceneNode__
#define __Wonderland__SceneNode__

#include "Transform.h"

class SceneNode {
protected:
    SceneNode();
    virtual ~SceneNode();
    
    void registerChild(SceneNode* child);
    void unregisterChild(SceneNode* child);
    
protected:
    SceneNode*             mParent;
    SceneNode*             mFirstChild;
    SceneNode*             mSiblings;
    
    bool                   mDirty;
    Transform              mTransform;
};

#endif /* defined(__Wonderland__SceneNode__) */
