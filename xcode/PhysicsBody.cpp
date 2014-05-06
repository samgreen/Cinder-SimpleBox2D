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
#pragma mark Other Constructors
    Body::Body(ConstVec &pos) : Body(pos, true) {}
    Body::Body(ConstVec &pos, bool isDynamic) {
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
    BodyType Body::getBodyType() const {
        return mBodyType;
    }
    
#pragma mark - Position
    Vec2f Body::getPosition() const {
        if (mBody) {
            return fromBoxVec(mBody->GetPosition());
        }
        
        return fromBoxVec(mBodyDef.position);
    }
    
    void Body::setPosition(ConstVec &pos) {
        if (mBody) {
            mBody->SetTransform(toBoxVec(pos), mBody->GetAngle());
        }
        
        mBodyDef.position = toBoxVec(pos);
    }
    
#pragma mark - Velocity
    Vec2f Body::getVelocity() const {
        if (mBody) {
            return fromBoxVec(mBody->GetLinearVelocity());
        }
        return fromBoxVec(mBodyDef.linearVelocity);
    }
    
    void Body::setVelocity(ConstVec &velocity) {
        if (mBody) {
            return mBody->SetLinearVelocity(toBoxVec(velocity));
        }
        mBodyDef.linearVelocity = toBoxVec(velocity);
    }
    
#pragma mark - Rotation
    float Body::getRotation() const {
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
    
    float Body::getRotationDegrees() const {
        return toDegrees(getRotation());
    }
    
    void Body::setRotationDegrees(float degrees) {
        float32 rotation = toRadians(degrees);
        if (mBody) {
            return mBody->SetTransform(mBody->GetPosition(), rotation);
        }
        
        mBodyDef.angle = rotation;
    }
    
    bool Body::isRotationLocked() const {
        return mBodyDef.fixedRotation;
    }
    
    void Body::setRotationLocked(bool isLocked) {
        if (mBody) {
            return mBody->SetFixedRotation(isLocked);
        }
        mBodyDef.fixedRotation = isLocked;
    }
    
#pragma mark - Forces
    void Body::applyForce(ConstVec &force, ConstVec &point) {
        mBody->ApplyForce(toBoxVec(force), toBoxVec(point));
    }
    
    void Body::applyTorque(float torque) {
        mBody->ApplyTorque(torque);
    }
    
    void Body::applyLinearImpulse(ConstVec &impulse, ConstVec &point) {
        mBody->ApplyLinearImpulse(toBoxVec(impulse), toBoxVec(point));
    }
    
    void Body::applyAngularImpulse(float impulse) {
        mBody->ApplyAngularImpulse(impulse);
    }
    
#pragma mark - Other Physics
    bool Body::isAffectedByGravity() const {
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
    
    bool Body::isDynamic() const {
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
    
    bool Body::isActive() const {
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
    
    float Body::getMass() const {
        if (mBody) {
            return mBody->GetMass();
        }
        
        return 0;
    }
    
    void Body::setMass(float mass) {
        if (mBody) {
            b2MassData *massData;
            mBody->GetMassData(massData);
            massData->mass = mass;
            
            const b2MassData *newData = massData;
            return mBody->SetMassData(newData);
        }
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
    
    float Body::getAngularDamping() const {
        if (mBody) {
            return mBody->GetAngularDamping();
        }
        
        return mBodyDef.angularDamping;
    }
    
    bool Body::usesPreciseCollision() {
        if (mBody) {
            return mBody->IsBullet();
        }
        
        return mBodyDef.bullet;
    }
    
    void Body::setPreciseCollision(bool isPrecise) {
        if (mBody) {
            return mBody->SetBullet(isPrecise);
        }
        
        return mBody->SetBullet(isPrecise);
    }
    
    void Body::setCollisionCategory(uint16 category) {
        mFixtureDef.filter.categoryBits = category;
    }
    
    void Body::setCollisionMask(uint16 mask) {
        mFixtureDef.filter.maskBits = mask;
    }
    
    void Body::setSensor(bool isSensor) {
        mFixtureDef.isSensor = isSensor;
    }
}

