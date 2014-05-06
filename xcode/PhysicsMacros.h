//
//  PhysicsMacros.h
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#pragma once

#include <Box2D/Box2D.h>
#include "cinder/Cinder.h"
#include "cinder/Vector.h"

namespace Physics {
    static inline b2Vec2 toBoxVector(const ci::Vec2f &v) {
        return b2Vec2(v.x, v.y);
    }
    
    static inline ci::Vec2f toVec2f(const b2Vec2 &v) {
        return ci::Vec2f(v.x, v.y);
    }
}
