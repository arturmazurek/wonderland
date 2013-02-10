//
//  World.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "World.h"

#include "Util/Log.h"

#include "Renderer/Renderer.h"

World::World() {
    
}

World::~World() {
    mObjects.DeleteAll();
}

void World::addObject(GameObject* object) {
    addObject(object, nullptr);
}

void World::addObject(GameObject* object, SceneNode* toNode) {
    if(!toNode) {
        toNode = &mRoot;
    }
    
    toNode->registerChild(object);
    mObjects.InsertTail(object);
    mSpawnedObjects.add(object);
}

void World::update(float timeInSeconds) {
    GameObject* obj = mObjects.Head();
    while(obj) {
        obj->update(timeInSeconds);
        obj = mObjects.Next(obj);
    }
    
    obj = mObjects.Head();
    while(obj) {
        if(obj->toDelete) {
            GameObject* temp = obj;
            obj = mObjects.Next(obj);
            mDeletedObjects.InsertTail(temp);
            continue;
        }
        
        if(obj->transform.dirty()) {
            updateTransform(obj);
        }
        obj = mObjects.Next(obj);
    }
}

void World::updateTransform(SceneNode* object) {
    if(object->getParent()->transform.dirty()) {
        updateTransform(object->getParent());
    }
    object->transform.update(&object->getParent()->transform);
}

void World::prepareRender(Renderer *renderer) {
    GameObject* obj = mDeletedObjects.Head();
    while(obj) {
        // remove static meshes from renderer
        obj = mDeletedObjects.Next(obj);
    }
    mDeletedObjects.DeleteAll();
    
    LinkedList<GameObject*>::Iterator addedIterator = mSpawnedObjects.iterator();
    while(addedIterator.hasNext()) {
        GameObject* obj = addedIterator.next();
        // add static meshes to the renderer
    }
    mSpawnedObjects.eraseAll();
}
