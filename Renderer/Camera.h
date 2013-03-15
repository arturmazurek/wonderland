//
//  Camera.h
//  Wonderland
//
//  Created by Artur Mazurek on 15/03/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Camera__
#define __Wonderland__Camera__

#include "Math/Matrix.h"
#include "Math/Vector.h"

class Camera {
public:
    Camera();
    ~Camera();
    
    void setClipPlanes(float near, float far);
    void setPerspective(float fovY, float aspect);
    void setOrtho(float width, float height);
    
    const Matrix& projection() const;
    
    bool isPerspective() const;
    float fov() const;
    
private:
    Camera(const Camera&);
    Camera& operator=(const Camera&);
    
    void calculateProjection();
    
private:
    Matrix  mProjection;
    
    float   mNear;
    float   mFar;
    
    bool    mPerspective;
    float   mFovY;
    float   mAspect;
    
    float   mWidth;
    float   mHeight;
};

#endif /* defined(__Wonderland__Camera__) */
