//
//  SceneNode.h
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__SceneNode__
#define __Wonderland__SceneNode__

#include "Util/LinkedList.h"

#include "Transform.h"

class SceneNode {
public:
    Transform              transform;
    
public:
    SceneNode();
    virtual ~SceneNode();
    
    void registerChild(SceneNode* child);
    void unregisterChild(SceneNode* child);
    
    SceneNode* getParent();
    
protected:
    LinkedList<SceneNode*>  mChildren;
    SceneNode*              mParent;
};

#endif /* defined(__Wonderland__SceneNode__) */
