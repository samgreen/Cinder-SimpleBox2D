//
//  PhysicsCircle.h
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
    
    class Circle : public Physics::Body {
    public:
        Circle(ConstVec &pos);
        Circle(ConstVec &pos, int radius);
        ~Circle();
        
        int getRadius() const;
    protected:
        Circle() {};
    };
    
}
