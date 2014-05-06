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
#include "cinder/PolyLine.h"
#include "PhysicsBody.h"

namespace Physics {
    
    class Polygon : public Physics::Body {
    public:
        Polygon();
        Polygon(ConstVec &pos, ci::PolyLine2f &points);
        ~Polygon();
        
        int         getWidth();
        int         getHeight();
        b2AABB      *getAABB();
    };
    
}

