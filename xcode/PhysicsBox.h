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
        Box();
        Box(const ci::Vec2f &pos);
        Box(const ci::Vec2f &pos, int size);
        Box(const ci::Vec2f &pos, const ci::Vec2f &size);
        Box(const ci::Vec2f &pos, int width, int height);
        ~Box();
        
        int getWidth() const;
        int getHeight() const;
        
    private:
        int     mWidth;
        int     mHeight;
    };

}
