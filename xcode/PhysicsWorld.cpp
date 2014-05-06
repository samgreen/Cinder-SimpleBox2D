//
//  PhysicsWorld.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsWorld.h"
#include "PhysicsMacros.h"
#include "PhysicsBody.h"
#include "PhysicsDebugDraw.h"

#include "cinder/app/AppNative.h"

using namespace ci;

namespace Physics {
    World::World() {
        mWorld = new b2World(b2Vec2());
    }
    
    World::World(const Vec2f &gravity) {
        mWorld = new b2World(toBoxVector(gravity));
    }
    
    void World::update() {
        float32 timestep = 1.f / 60.f;
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        
        for (int32 i = 0; i < 60; ++i) {
            mWorld->Step(timestep, velocityIterations, positionIterations);
        }
    }
    
    void World::draw() {
        mWorld->DrawDebugData();
    }
    
    void World::addBody(Physics::Body *body) {
        // Create the body in the world
        const b2BodyDef *bodyDef = &body->mBodyDef;
        body->mBody = mWorld->CreateBody(bodyDef);
        
        // Attach the fixture to this body
        const b2FixtureDef *fixtureDef = &body->mFixtureDef;
        body->mBody->CreateFixture(fixtureDef);
    }
    
    void World::addSolidGround(const app::AppNative *app) {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set( 0.0f, app->getWindowHeight() );
        b2Body* groundBody = mWorld->CreateBody(&groundBodyDef);
        
        // Define the ground box shape.
        b2PolygonShape groundBox;
        
        // The extents are the half-widths of the box.
        groundBox.SetAsBox( app->getWindowWidth(), 10.0f );
        
        // Add the ground fixture to the ground body.
        groundBody->CreateFixture(&groundBox, 0.0f);
    }
    
    Vec2f World::getGravity() {
        return toVec2f(mWorld->GetGravity());
    }
    
    void World::setGravity(const ci::Vec2f &gravity) {
        mWorld->SetGravity(toBoxVector(gravity));
    }
    
    void World::enableDebugDraw() {
        Physics::DebugDraw *draw = new Physics::DebugDraw();
        
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_centerOfMassBit;
        flags += b2Draw::e_aabbBit;
        flags += b2Draw::e_pairBit;
        draw->SetFlags(flags);
        
        mWorld->SetDebugDraw(draw);
    }
    
    void World::disableDebugDraw() {
        mWorld->SetDebugDraw(NULL);
    }
}