//
//  CameraComponent.h
//  Wonderland
//
//  Created by Artur Mazurek on 18/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__CameraComponent__
#define __Wonderland__CameraComponent__

#include "Core/Transform.h"

#include "Math/Matrix.h"

#include "Util/SharedPtr.h"

#include "ComponentBase.h"

class Camera;
class GameObject;
class Renderer;

class CameraComponent : public ComponentBase {
public:
    DEFINE_TYPE;
    
    CameraComponent(Renderer* renderer);
    virtual ~CameraComponent();
    
    virtual void update(float dt, GameObject* owner);
    
    void useCamera();
    
private:
    void updateViewTransform(const Transform& transform);
    
private:
    Renderer*           mRenderer;
    SharedPtr<Camera>   mCamera;
};

#endif /* defined(__Wonderland__CameraComponent__) */
