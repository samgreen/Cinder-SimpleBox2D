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

namespace Physics {
    class World;
    
    typedef enum _BodyType {
        BodyTypeUnknown,
        BodyTypeBox,
        BodyTypeCircle,
        BodyTypePolygon,
    } BodyType;
    
    class Body {
        friend class Physics::World;
    public:
        Body();
        Body(const ci::Vec2f &pos);
        Body(const ci::Vec2f &pos, bool isDynamic);
        ~Body();
        
        ci::Vec2f       getPosition();
        float         getRotation();
        float           getRotationDegrees();
        BodyType        getBodyType();
        
        void            setDensity(float32 density);
        void            setRestitution(float32 restitution);
        void            setFriction(float32 friction);
    protected:
        BodyType        mBodyType;
        
        b2Body          *mBody;
        b2BodyDef       mBodyDef;
        b2FixtureDef    mFixtureDef;
    };
}
