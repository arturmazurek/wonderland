//
//  GameObject.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__GameObject__
#define __Wonderland__GameObject__

#include "Util/LinkedList.h"
#include "Util/List.h"

#include "Components/ComponentBase.h"

#include "SceneNode.h"

class GameObject : public SceneNode {
    friend class World;
public:
    GameObject();
    ~GameObject();
    
    unsigned objectId() const;
    
    void addChild(GameObject* child);
    void removeFromParent();
    
    void update(float timeInSeconds);
    
    void addComponent(ComponentBase* component);
    bool hasComponent(const ComponentBase* component) const;
    void getComponents(LinkedList<ComponentBase*>& result, ComponentBase::Type type);
    
public:
    bool                    toDelete;
    bool                    transformUpdated;
    
private:
    static unsigned         sIdCounter;
    
    unsigned                mId;
    
    LIST_LINK(GameObject)   mObjectsLink;
    
    LIST_DECLARE(ComponentBase, mOwnersLink) mComponents;
};

#endif /* defined(__Wonderland__GameObject__) */
