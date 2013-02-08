//
//  GameObject.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__GameObject__
#define __Wonderland__GameObject__

#include "SceneNode.h"

#include "Util/List.h"

class GameObject : public SceneNode {
    friend class World;
public:
    GameObject();
    ~GameObject();
    
    unsigned objectId() const;
    
    void addChild(GameObject* child);
    void removeFromParent();
    
    void update(float timeInSeconds);
    
private:
    static unsigned         sIdCounter;
    
    unsigned                mId;
    
    LIST_LINK(GameObject)   mObjectsLink;
};

#endif /* defined(__Wonderland__GameObject__) */
