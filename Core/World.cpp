//
//  World.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "World.h"

#include "Util/Log.h"

#include "SceneNode.h"

World::World() {
    
}

World::~World() {
    mObjects.DeleteAll();
}

void World::addObject(GameObject* obj) {
    mRoot.registerChild(obj);
    mObjects.InsertTail(obj);
}

void World::update(float timeInSeconds) {
    GameObject* obj = mObjects.Head();
    while(obj) {
        obj->update(timeInSeconds);
        obj = obj->mObjectsLink.Next();
    }
}