//
//  PhysicsBox.h
//  CinderBoxFun
//
//  Created by Sam Green on 5/5/14.
//
//

#pragma once

#include <Box2D/Box2D.h>
#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include "PhysicsBody.h"

namespace Physics {

    class Box : public Physics::Body {
    public:
        Box(ConstVec &pos);
        Box(ConstVec &pos, int size);
        Box(ConstVec &pos, ConstVec &size);
        Box(ConstVec &pos, int width, int height);
        ~Box();
        
        int getWidth() const;
        int getHeight() const;
        
    protected:
        Box() {};
        
    private:
        int     mWidth;
        int     mHeight;
    };

}
