//
//  World.cpp
//  Wonderland
//
//  Created by Artur Mazurek on 07.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#include "World.h"

#include "Core/Components/StaticMeshComponent.h"

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
            obj->transformUpdated = true;
        } else {
            obj->transformUpdated = false;
        }
        obj = mObjects.Next(obj);
    }
}

void World::updateTransform(SceneNode* object) {
    if(object->getParent()->transform.dirty()) {
        updateTransform(object->getParent());
    }
    object->transform.update(object->getParent()->transform);
}

void World::prepareRender(Renderer *renderer) {
    removeDeleted(renderer);
    addSpawned(renderer);
}

void World::addSpawned(Renderer* renderer) {
    LinkedList<GameObject*>::Iterator addedIterator = mSpawnedObjects.iterator();
    while(addedIterator.hasNext()) {
        GameObject* obj = addedIterator.next();
        
        LinkedList<ComponentBase*> staticMeshComponents;
        obj->getComponents(staticMeshComponents, StaticMeshComponent::TYPE);
        
        LinkedList<ComponentBase*>::Iterator it = staticMeshComponents.iterator();
        while(it.hasNext()) {
            StaticMeshComponent* staticMeshComponent = static_cast<StaticMeshComponent*>(it.next());
            renderer->drawStaticMesh(staticMeshComponent->getMesh(), obj);
        }
    }
    
    mSpawnedObjects.eraseAll();
}

void World::removeDeleted(Renderer* renderer) {
    GameObject* obj = mDeletedObjects.Head();
    while(obj) {
        LinkedList<ComponentBase*> staticMeshComponents;
        obj->getComponents(staticMeshComponents, StaticMeshComponent::TYPE);
        
        LinkedList<ComponentBase*>::Iterator it = staticMeshComponents.iterator();
        while(it.hasNext()) {
            StaticMeshComponent* staticMeshComponent = static_cast<StaticMeshComponent*>(it.next());
            renderer->dropStaticMesh(staticMeshComponent->getMesh(), obj);
        }
        
        obj = mDeletedObjects.Next(obj);
    }
    
    mDeletedObjects.DeleteAll();
}
