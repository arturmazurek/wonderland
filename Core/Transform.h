//
//  Transform.h
//  Wonderland
//
//  Created by Artur Mazurek on 07/02/2013.
//  Copyright (c) 2013 Artur Mazurek. All rights reserved.
//

#ifndef __Wonderland__Transform__
#define __Wonderland__Transform__

#include "Math/Matrix.h"
#include "Math/Vector.h"

#include "Util/List.h"

class Transform {
public:
    Transform(Transform* parent = nullptr);
    ~Transform();
    
    const Vector& pos() const;
    void setPos(const Vector& pos);
    
    float scale() const;
    void setScale(float s);
    
    float scaleX() const;
    float scaleY() const;
    float scaleZ() const;
    
    void setScaleX(float sx);
    void setScaleY(float sy);
    void setScaleZ(float sz);
    
    void addChild(Transform* child);
    void removeFromParent();
    
    void updateTransforms();
    
private:
    void registerChild(Transform* child);
    void unregisterChild(Transform* child);
    
private:
    Transform*  mChildren;
    bool        mDirty;
    Matrix      mFrame;
    Transform*  mParent;
    Vector      mPosition;
    Transform*  mSiblings;
    Vector      mScale;
};

#endif /* defined(__Wonderland__Transform__) */
