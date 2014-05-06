//
//  PhysicsWorld.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsWorld.h"
#include "PhysicsBody.h"
#include "PhysicsDebugDraw.h"

#include "cinder/app/AppNative.h"

using namespace ci;

namespace Physics {
    World::World() {
        mWorld = new b2World(b2Vec2());
    }
    
    World::World(ConstVec &gravity) {
        mWorld = new b2World(toBoxVec(gravity));
    }
    
    void World::update() {
        static const float32 TIME_STEP = 1.f / 30.f;
        static const int32 VEL_ITERATIONS = 10;
        static const int32 POS_ITERATIONS = 10;
        
        this->update(TIME_STEP, VEL_ITERATIONS, POS_ITERATIONS);
    }
    
    void World::update(float32 timestep, int32 velocityIterations, int32 positionIterations) {
        for (int32 i = 0; i < 10; ++i) {
            mWorld->Step(timestep, velocityIterations, positionIterations);
        }
    }
    
    void World::draw() {
        mWorld->DrawDebugData();
    }
    
    void World::addBody(Body *body) {
        // Create the body in the world
        const b2BodyDef *bodyDef = &body->mBodyDef;
        body->mBody = mWorld->CreateBody(bodyDef);
        
        // Attach the fixture to this body
        const b2FixtureDef *fixtureDef = &body->mFixtureDef;
        body->mBody->CreateFixture(fixtureDef);
    }
    
    void World::removeBody(Body *body) {
        // Ask the world to destory this body
        mWorld->DestroyBody(body->mBody);
        body->mBody = NULL;
    }
    
    int World::getNumBodies() {
        return mWorld->GetBodyCount();
    }
    
    int World::getNumJoints() {
        return mWorld->GetJointCount();
    }
    
    int World::getNumContacts() {
        return mWorld->GetContactCount();
    }
    
    void World::addSolidGround(const app::AppNative *app) {
        // TODO: Refactor this to use chains, or edges
        
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
    
    Vec2f World::getGravity() const {
        return fromBoxVec(mWorld->GetGravity());
    }
    
    void World::setGravity(ConstVec &gravity) {
        mWorld->SetGravity(toBoxVec(gravity));
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