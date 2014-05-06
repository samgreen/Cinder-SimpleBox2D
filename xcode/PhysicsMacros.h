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
    
    typedef ci::Vec2f ConstVec2f;
    typedef ConstVec2f ConstVec;
    
    static inline b2Vec2 toBoxVec(ConstVec &v) {
        return b2Vec2(v.x, v.y);
    }
    
    static inline ci::Vec2f toVec(const b2Vec2 &v) {
        return ci::Vec2f(v.x, v.y);
    }
}
