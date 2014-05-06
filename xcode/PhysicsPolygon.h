//
//  PhysicsPolygon.h
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#pragma once

#include <Box2D/Box2D.h>
#include "cinder/Cinder.h"
#include "cinder/CinderMath.h"
#include "cinder/Vector.h"
#include "PhysicsBody.h"

namespace Physics {
    
    class Polygon : public Physics::Body {
    public:
        Polygon();
        Polygon(const ci::Vec2f &pos);
        ~Polygon();
        
        int         getWidth();
        int         getHeight();
        b2AABB      *getAABB();
    };
    
}

