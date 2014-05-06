//
//  PhysicsWorld.h
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
#include "cinder/app/AppNative.h"

namespace Physics {
    
    // Forward Declaration
    class Body;
    
    class World {
    public:
        // Constructors
        World();
        World(const ci::Vec2f &gravity);
        // Destructors
        ~World();
        
        void            update();
        void            update(float32 timestep, int32 velocityIterations, int32 positionIterations);
        void            draw();
        
        void            addBody(Body *body);
        void            removeBody(Body *body);
        void            addSolidGround(const ci::app::AppNative *app);
        
        ci::Vec2f       getGravity();
        void            setGravity(const ci::Vec2f &gravity);
        
        void            enableDebugDraw();
        void            disableDebugDraw();
    protected:
        b2World         *mWorld;
    };
}
