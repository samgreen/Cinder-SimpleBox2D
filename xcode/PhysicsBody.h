//
//  PhysicsBody.h
//  CinderBoxFun
//
//  Created by Sam Green on 5/5/14.
//
//

#pragma once

#include <Box2D/Box2D.h>
#include "cinder/Cinder.h"
#include "cinder/Vector.h"
#include "PhysicsMacros.h"

namespace Physics {
    class World;
    
    typedef enum _BodyType {
        BodyTypeUnknown,
        BodyTypeBox,
        BodyTypeCircle
    } BodyType;
    
    class Body {
    public:
        Body();
        Body(const ci::Vec2f &pos);
        Body(const ci::Vec2f &pos, bool isDynamic);
        ~Body();

        BodyType        getBodyType();
        
        ci::Vec2f       getPosition();
        void            setPosition(const ci::Vec2f &pos);
        
        float           getRotation();
        void            setRotation(float radians);
        
        float           getRotationDegrees();
        void            setRotationDegrees(float degress);
        
        /// Can this body rotate on the Z axis?
        bool            isRotationLocked();
        /// Set this body to allow rotation on the Z axis
        void            setRotationLocked(bool isLocked);
        
        /// Is this body affected by the world gravity?
        bool            isAffectedByGravity();
        /// Set this body to be affected by the world's gravity
        void            setAffectedByGravity(bool isAffected);
        
        /// Is this body fixed in place or moving?
        bool            isDynamic();
        /// Set this body as fixed or affected by physics
        void            setDynamic(bool isDynamic);
        
        bool            isActive();
        void            setActive(bool isActive);
        
        float           getDensity();
        void            setDensity(float density);
        
        float           getRestitution();
        void            setRestitution(float restitution);
        
        float           getFriction();
        void            setFriction(float friction);
        
        /// Damping is used to reduce the world velocity of bodies. Damping is different than friction because friction only occurs with contact. Damping is not a replacement for friction and the two effects should be used together.
        float           getAngularDamping();
        void            setAngularDamping(float damping);
        
        ci::Vec2f       getVelocity();
        void            setVelocity(ConstVec &velocity);
        
        float           getAngularVelocity();
        void            setAngularVelocity(float angularVelocity);
        
        /// ((catA & maskB) != 0 && (catB & maskA) != 0)
        void            setCollisionCategory(uint16 category);
        void            setCollisionMask(uint16 mask);
    protected:
        BodyType        mBodyType;
        
        b2Body          *mBody;
        b2BodyDef       mBodyDef;
        b2FixtureDef    mFixtureDef;
        
        friend class Physics::World;
    };
}
