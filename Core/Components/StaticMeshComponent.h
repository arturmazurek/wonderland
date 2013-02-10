//
//  StaticMeshComponent.h
//  Wonderland
//
//  Created by Artur Mazurek on 09.02.2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__StaticMeshComponent__
#define __Wonderland__StaticMeshComponent__

#include "ComponentBase.h"

class StaticMesh;
struct Vertex;

class StaticMeshComponent : public ComponentBase {
public:
    DEFINE_TYPE;
    
    StaticMeshComponent();
    ~StaticMeshComponent();
    
    virtual void update(float dt, GameObject* owner) override;
    
    StaticMesh* getMesh();

private:
    StaticMesh* mStaticMesh;
};

#endif /* defined(__Wonderland__StaticMeshComponent__) */
