//
//  PhysicsBody.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/5/14.
//
//

#include "PhysicsBody.h"
#include "PhysicsMacros.h"

using namespace ci;

namespace Physics {
#pragma mark - Default Constructor
    Body::Body() : Body(Vec2f(0,0), true) {};
    
#pragma mark Other Constructors
    Body::Body(const Vec2f &pos) : Body(pos, true) {}
    Body::Body(const Vec2f &pos, bool isDynamic) {
        // Body Def Defaults
        mBodyDef.position = toBoxVec(pos);
        mBodyDef.type = (isDynamic ? b2_dynamicBody : b2_staticBody);
        
        // Fixture Def defaults
        mFixtureDef.density = 0.1f;
        mFixtureDef.friction = 0.1f;
        mFixtureDef.restitution = 0.1f;
    }
    
#pragma mark - Destructor
    Body::~Body() {
        
    }
    
#pragma mark - Body Type
    BodyType Body::getBodyType() {
        return mBodyType;
    }
    
#pragma mark - Position
    Vec2f Body::getPosition() {
        if (mBody) {
            return toVec(mBody->GetPosition());
        }
        
        return toVec(mBodyDef.position);
    }
    
    void Body::setPosition(const ci::Vec2f &pos) {
        if (mBody) {
            mBody->SetTransform(toBoxVec(pos), mBody->GetAngle());
        }
        
        mBodyDef.position = toBoxVec(pos);
    }
    
#pragma mark - Velocity
    Vec2f Body::getVelocity() {
        if (mBody) {
            return toVec(mBody->GetLinearVelocity());
        }
        return toVec(mBodyDef.linearVelocity);
    }
    
    void Body::setVelocity(const ci::Vec2f &velocity) {
        if (mBody) {
            return mBody->SetLinearVelocity(toBoxVec(velocity));
        }
        mBodyDef.linearVelocity = toBoxVec(velocity);
    }
    
#pragma mark - Rotation
    float Body::getRotation() {
        if (mBody) {
            return mBody->GetAngle();
        }
        
        return mBodyDef.angle;
    }
    
    void Body::setRotation(float radians) {
        if (mBody) {
            return mBody->SetTransform(mBody->GetPosition(), radians);
        }
        
        mBodyDef.angle = radians;
    }
    
    float Body::getRotationDegrees() {
        return toDegrees(getRotation());
    }
    
    void Body::setRotationDegrees(float degrees) {
        float32 rotation = toRadians(degrees);
        if (mBody) {
            return mBody->SetTransform(mBody->GetPosition(), rotation);
        }
        
        mBodyDef.angle = rotation;
    }
    
    bool Body::isRotationLocked() {
        return mBodyDef.fixedRotation;
    }
    
    void Body::setRotationLocked(bool isLocked) {
        if (mBody) {
            return mBody->SetFixedRotation(isLocked);
        }
        mBodyDef.fixedRotation = isLocked;
    }
    
#pragma mark - Other Physics
    bool Body::isAffectedByGravity() {
        if (mBody) {
            return (mBody->GetGravityScale() > FLT_EPSILON);
        }
        return (mBodyDef.gravityScale > FLT_EPSILON);
    }
    
    void Body::setAffectedByGravity(bool isAffected) {
        float32 scale = (isAffected ? 1.f : 0.f);
        if (mBody) {
            return mBody->SetGravityScale(scale);
        }
        
        mBodyDef.gravityScale = scale;
    }
    
    bool Body::isDynamic() {
        if (mBody) {
            return (mBody->GetType() != b2_staticBody);
        }
        
        return (mBodyDef.type != b2_staticBody);
    }
    
    void Body::setDynamic(bool isDynamic) {
        b2BodyType type = (isDynamic ? b2_dynamicBody : b2_staticBody);
        if (mBody) {
            return mBody->SetType(type);
        }
        
        mBodyDef.type = type;
    }
    
    bool Body::isActive() {
        if (mBody) {
            return mBody->IsActive();
        }
        
        return mBodyDef.active;
    }
    
    void Body::setActive(bool isActive) {
        if (mBody) {
            return mBody->SetActive(isActive);
        }
        
        mBodyDef.active = isActive;
    }
    
    void Body::setDensity(float density) {
        mFixtureDef.density = density;
    }
    
    void Body::setFriction(float friction) {
        mFixtureDef.friction = friction;
    }
    
    void Body::setRestitution(float restitution) {
        mFixtureDef.restitution = restitution;
    }
    
    void Body::setAngularDamping(float damping) {
        if (mBody) {
            return mBody->SetAngularDamping(damping);
        }
        
        mBodyDef.angularDamping = damping;
    }
    
    float Body::getAngularDamping() {
        if (mBody) {
            return mBody->GetAngularDamping();
        }
        
        return mBodyDef.angularDamping;
    }
}

