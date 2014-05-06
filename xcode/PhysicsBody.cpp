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
        mBodyDef.position = toBoxVector(pos);
        mBodyDef.type = (isDynamic ? b2_dynamicBody : b2_staticBody);
        
        // Fixture Def defaults
        mFixtureDef.density = 0.1f;
        mFixtureDef.friction = 0.1f;
    }
    
#pragma mark - Destructor
    Body::~Body() {
        
    }
    
#pragma mark - Accessors
    BodyType Body::getBodyType() {
        return mBodyType;
    }
    
    Vec2f Body::getPosition() {
        return toVec2f(mBody->GetPosition());
    }
    
    float Body::getRotation() {
        return mBody->GetAngle();
    }
    
    float Body::getRotationDegrees() {
        return toDegrees(getRotation());
    }
    
#pragma mark - Setters
    void Body::setDensity(float32 density) {
        mFixtureDef.density = density;
    }
    
    void Body::setFriction(float32 friction) {
        mFixtureDef.friction = friction;
    }
    
    void Body::setRestitution(float32 restitution) {
        mFixtureDef.restitution = restitution;
    }
}

