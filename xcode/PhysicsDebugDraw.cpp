//
//  PhysicsDebugDraw.cpp
//  CinderBoxFun
//
//  Created by Sam Green on 5/6/14.
//
//

#include "PhysicsDebugDraw.h"
#include "PhysicsMacros.h"

#include "cinder/Cinder.h"
#include "cinder/CinderMath.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"

using namespace ci;

namespace Physics {
    
    static inline void SetColor( const b2Color &color ) {
        gl::color(color.r, color.g, color.b);
    }
    
    void DebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) {
        SetColor(color);
        gl::drawSolidCircle(toVec(*vertices), 10.f);
    }
    
    
    /// Draw a solid closed polygon provided in CCW order.
    void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
        SetColor(color);
        gl::drawSolidCircle(toVec(*vertices), 10.f);
    }
    
    /// Draw a circle.
    void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
        SetColor(color);
        gl::drawStrokedCircle(toVec(center), radius);
    }
    
    /// Draw a solid circle.
    void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
        SetColor(color);
        // TODO: Axis
        gl::drawSolidCircle(toVec(center), radius);
    }
    
    /// Draw a line segment.
    void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
        SetColor(color);
        gl::drawLine(toVec(p1), toVec(p2));
    }
    
    /// Draw a transform. Choose your own length scale.
    /// @param xf a transform.
    void DebugDraw::DrawTransform(const b2Transform& xf) {
        
    }
}