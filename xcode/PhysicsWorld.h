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
#include "PhysicsMacros.h"

namespace Physics {
    
    // Forward Declaration
    class Body;
    
    class World {
    public:
        // Constructors
        World();
        World(ConstVec &gravity);
        // Destructors
        ~World();
        
        void            update();
        void            update(float32 timestep, int32 velocityIterations, int32 positionIterations);
        void            draw();
        
        void            addBody(Body *body);
        void            removeBody(Body *body);
        int             getNumBodies();
        
        int             getNumJoints();
        int             getNumContacts();
        
        void            addSolidGround(const ci::app::AppNative *app);
        void            addSolidEdges(const ci::app::AppNative *app);
        void            addSolidEdge(int x, int y, int width, int height);
        
        ci::Vec2f       getGravity() const;
        void            setGravity(ConstVec &gravity);
        
        void            enableDebugDraw();
        void            disableDebugDraw();
        
        // TODO: Add raycast
        // TODO: Add point check
    protected:
        b2World         *mWorld;
    };
}
