//
//  PhysicsPolygon.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsPolygon.h"

using namespace ci;

namespace Physics {
#pragma mark - Constructors
    Polygon::Polygon() {}
    Polygon::Polygon(ConstVec &pos, PolyLine2f &points) : Body(pos) {
        mBodyType = BodyTypePolygon;
        
        // This defines a triangle in CCW order.
        int32 count = points.size();
        b2Vec2 *vertices = new b2Vec2[count];
        size_t index = 0;
        for (PolyLine2f::iterator it = points.begin(); it != points.end(); it++) {
            vertices[index] = toBoxVec(*it);
            index++;
        }
        
        b2PolygonShape *shape = new b2PolygonShape;
        shape->Set(vertices, count);
        mFixtureDef.shape = shape;
    };
    
#pragma mark - Destructor
    Polygon::~Polygon() {};
    
#pragma mark - Accessors
    int Polygon::getWidth() {
        return 0;
    }
    
    int Polygon::getHeight() {
        return 0;
    }
    
    b2AABB* Polygon::getAABB() {
        return NULL;
    }
}