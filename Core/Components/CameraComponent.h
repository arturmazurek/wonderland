//
//  CameraComponent.h
//  Wonderland
//
//  Created by Artur Mazurek on 18/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__CameraComponent__
#define __Wonderland__CameraComponent__

#include "Math/Matrix.h"

#include "Util/SharedPtr.h"

#include "ComponentBase.h"

class Camera;
class GameObject;

class CameraComponent : ComponentBase {
public:
    DEFINE_TYPE;
    
    CameraComponent();
    virtual ~CameraComponent();
    
    virtual void update(float dt, GameObject* owner);
    
    Camera* camera();
    const Camera* camera() const;
    
    const Matrix& projection() const;
    const Matrix& view() const;
    
private:
    SharedPtr<Camera> mCamera;
};

#endif /* defined(__Wonderland__CameraComponent__) */
