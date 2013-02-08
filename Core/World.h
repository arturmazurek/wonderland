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
#include "SceneNode.h"

class World {
public:
    World();
    ~World();
    
    void addObject(GameObject* obj);
    
    void update(float timeInSeconds);
    
private:
    World(const World&);
    World& operator=(const World&);
    
private:
    LIST_DECLARE(GameObject, mObjectsLink) mObjects;
    SceneNode mRoot;
};

#endif /* defined(__Wonderland__World__) */