//
//  PhysicsCircle.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsCircle.h"

using namespace ci;

namespace Physics {
#pragma mark - Default Constructor
    Circle::Circle() : Circle(Vec2f(0,0), 10) {}
    
#pragma mark Other Constructors
    Circle::Circle(const Vec2f &pos) : Circle(pos, 10) {}
    Circle::Circle(const Vec2f &pos, int radius) : Body(pos) {
        mBodyType = BodyTypeCircle;
        mRadius = radius;
        
        // Create circle shape
        b2CircleShape circle;
        circle.m_radius = radius;
        mFixtureDef.shape = new b2CircleShape(circle);
    }
    
#pragma mark - Destructor
    Circle::~Circle() {
        
    }
    
#pragma mark - Accessors
    int Circle::getRadius() {
        return mRadius;
    }
}