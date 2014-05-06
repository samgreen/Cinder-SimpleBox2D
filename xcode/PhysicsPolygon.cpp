//
//  PhysicsPolygon.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsPolygon.h"

namespace Physics {
#pragma mark - Constructors
    Polygon::Polygon() {}
    Polygon::Polygon(const ci::Vec2f &pos) : Body(pos) {
        // This defines a triangle in CCW order.
        b2Vec2 vertices[3];
        vertices[0].Set(0.0f, 0.0f);
        vertices[1].Set(1.0f, 0.0f);
        vertices[2].Set(0.0f, 1.0f);
        int32 count = 3;
        
        b2PolygonShape *shape = new b2PolygonShape;
        shape->Set(vertices, count);
        mFixtureDef.shape = shape;
    };
    
#pragma mark - Destructor
    Polygon::~Polygon() {};
    
#pragma mark - Accessors
    int Polygon::getWidth() {
        
    }
    
    int Polygon::getHeight() {
        
    }
    
    b2AABB* Polygon::getAABB() {
        
    }
}