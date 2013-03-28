//
//  ComponentBase.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__ComponentBase__
#define __Wonderland__ComponentBase__

#include "Util/List.h"

#include "ComponentType.h"

class GameObject;

class ComponentBase {
    friend class GameObject;
public:
    virtual ~ComponentBase();
    
    typedef int Type;
    virtual Type type() const = 0;
    
    virtual void update(float dt) = 0;
    
    LIST_LINK(ComponentBase) mOwnersLink;
protected:
    ComponentBase();
    
    GameObject* owner();
    
private:
    ComponentBase(const ComponentBase&);
    ComponentBase& operator=(const ComponentBase&);
    
    void setOwner(GameObject* owner);
    
private:
    GameObject* mOwner;
};

#endif /* defined(__Wonderland__ComponentBase__) */
