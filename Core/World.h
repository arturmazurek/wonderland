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

class Renderer;

class World {
public:
    World();
    ~World();
    
    void addObject(GameObject* object);
    void addObject(GameObject* object, SceneNode* toNode);
    
    void prepareRender(Renderer* renderer);
    
    void update(float timeInSeconds);
    
private:
    World(const World&);
    World& operator=(const World&);
    
    void updateTransform(SceneNode* object);
    
    void removeDeleted(Renderer* renderer);
    void addSpawned(Renderer* renderer);
    
private:
    LIST_DECLARE(GameObject, mObjectsLink)  mObjects;
    LIST_DECLARE(GameObject, mObjectsLink)  mDeletedObjects;
    LinkedList<GameObject*>                 mSpawnedObjects;
    
    SceneNode mRoot;
};

#endif /* defined(__Wonderland__World__) */
