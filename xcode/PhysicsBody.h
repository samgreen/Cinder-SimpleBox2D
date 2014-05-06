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
        BodyTypeCircle,
        BodyTypePolygon,
    } BodyType;
    
    class Body {
    public:
        Body(ConstVec pos);
        Body(ConstVec pos, bool isDynamic);
        ~Body();

        BodyType        getBodyType() const;
        
#pragma mark - Position
        ci::Vec2f       getPosition() const;
        void            setPosition(ConstVec pos);
        
#pragma mark - Rotation
        float           getRotation() const;
        void            setRotation(float radians);
        
        float           getRotationDegrees() const;
        void            setRotationDegrees(float degress);
        
        /// Can this body rotate on the Z axis?
        bool            isRotationLocked() const;
        /// Set this body to allow rotation on the Z axis
        void            setRotationLocked(bool isLocked);
        
        /// Is this body affected by the world gravity?
        bool            isAffectedByGravity() const;
        /// Set this body to be affected by the world's gravity
        void            setAffectedByGravity(bool isAffected);
        
#pragma mark Angular Physics
        float           getAngularVelocity() const;
        void            setAngularVelocity(float angularVelocity);
        
        /// Damping is used to reduce the world velocity of bodies. Damping is different than friction because friction only occurs with contact. Damping is not a replacement for friction and the two effects should be used together.
        float           getAngularDamping() const;
        void            setAngularDamping(float damping);
        
#pragma mark - Forces
        void            applyForce(ConstVec force, ConstVec point);
        void            applyTorque(float torque);
        void            applyLinearImpulse(ConstVec impulse, ConstVec point);
        void            applyAngularImpulse(float impulse);
        
#pragma mark - Collision
        /// ((catA & maskB) != 0 && (catB & maskA) != 0)
        void            setCollisionCategory(uint16 category);
        void            setCollisionMask(uint16 mask);
        
        bool            usesPreciseCollision();
        void            setPreciseCollision(bool isPrecise);
        
#pragma mark - Physical Properties
        float           getDensity() const;
        void            setDensity(float density);
        
        float           getRestitution() const;
        void            setRestitution(float restitution);
        
        float           getFriction() const;
        void            setFriction(float friction);
        
        float           getMass() const;
        void            setMass(float mass);
        
        ci::Vec2f       getVelocity() const;
        void            setVelocity(ConstVec velocity);
        
#pragma mark - Other Helpers
        /// Is this body fixed in place or moving?
        bool            isDynamic() const;
        /// Set this body as fixed or affected by physics
        void            setDynamic(bool isDynamic);
        
        bool            isActive() const;
        void            setActive(bool isActive);
        
        void            setSensor(bool isSensor);
    protected:
        Body() {};
        
        BodyType        mBodyType;
        
        b2Body          *mBody;
        b2BodyDef       mBodyDef;
        b2FixtureDef    mFixtureDef;
        
        friend class Physics::World;
    };
}
