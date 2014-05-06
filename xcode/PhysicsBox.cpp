//
//  PhysicsBox.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/5/14.
//
//

#include "PhysicsBox.h"

using namespace ci;

namespace Physics {
#pragma mark - Constructors
    Box::Box() : Box(Vec2f(0,0), 10, 10) {};
    Box::Box(const Vec2f &pos) : Box(pos, 10, 10) {};
    Box::Box(const Vec2f &pos, int size) : Box(pos,  size, size) {}
    Box::Box(const Vec2f &pos, int width, int height) : Body(pos) {
        mBodyType = BodyTypeBox;
        mWidth = width;
        mHeight = height;
        
        b2PolygonShape *shape = new b2PolygonShape();
        shape->SetAsBox(mWidth, mHeight);
        mFixtureDef.shape = shape;
    }
    
#pragma mark - Destructor
    Box::~Box() {}
    
#pragma mark - Accessors
    int Box::getWidth() const {
        return mWidth;
    }
    
    int Box::getHeight() const {
        return mHeight;
    }
    
#pragma mark - Helpers

}
