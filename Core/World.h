//
//  World.h
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__World__
#define __Wonderland__World__

#include "Util/List.h"

#include "GameObject.h"

class World {
public:
    World();
    ~World();
    
    void addObject(GameObject* obj);
    
private:
    World(const World&);
    World& operator=(const World&);
    
private:
    LIST_DECLARE(GameObject, mObjectsLink) mObjects;
    Transform mRoot;
};

#endif /* defined(__Wonderland__World__) */
