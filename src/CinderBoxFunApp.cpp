#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Physics.h"

using namespace ci;
using namespace ci::app;
using namespace Physics;
using namespace std;

const float BOX_SIZE = 25;

class CinderBoxFunApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	void addBox( const Vec2f &pos );
	void addCircle( const Vec2f &pos );
    
    World          *mPhysicsWorld;
    vector<Body*>  mBodies;
};

void CinderBoxFunApp::setup()
{
    // Create a physics world with Earth's gravity
    mPhysicsWorld = new World( Vec2f(0, 9.8f) );
    // Add a solid ground at the bottom of the window
    mPhysicsWorld->addSolidGround(this);
    mPhysicsWorld->enableDebugDraw();
}

void CinderBoxFunApp::addBox( const Vec2f &pos )
{
    // Add a box at (100,200) position that is 10x20
    Box *box = new Box(Vec2f(100, 200), 10, 20);
    mPhysicsWorld->addBody(box);
    mBodies.push_back(box);
}

void CinderBoxFunApp::addCircle( const Vec2f &pos ) {
    Circle *circle = new Circle(pos, BOX_SIZE);
    float32 randRestitution = (float32)arc4random_uniform(10) / 10;
    circle->setRestitution(randRestitution);
    mPhysicsWorld->addBody(circle);
    mBodies.push_back(circle);
}

void CinderBoxFunApp::mouseDown( MouseEvent event )
{
    Vec2i pos = event.getPos();
    if ( event.isShiftDown() ) {
        addCircle( pos );
    } else {
        addBox( pos );
    }
}

void CinderBoxFunApp::update()
{
    mPhysicsWorld->update();
}

void CinderBoxFunApp::draw()
{
    // clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
//    mPhysicsWorld->draw();
    
	for( vector<Body*>::const_iterator boxIt = mBodies.begin(); boxIt != mBodies.end(); ++boxIt ) {
        Body *body = *boxIt;
        Vec2f pos = body->getPosition();
        float t = toDegrees(body->getRotation());
        
		glPushMatrix();
		gl::translate( pos );
		gl::rotate( t );

        if (body->getBodyType() == BodyTypeBox) {
            Box *boxBody = (Box *)body;
            Rectf rect( -boxBody->getWidth(), -boxBody->getHeight(), boxBody->getWidth(), boxBody->getHeight() );
            gl::color( Color( 1, 0.5f, 0.25f ) );
            gl::drawSolidRect( rect );
        } else {
            Circle *circleBody = (Circle *)body;
            gl::color( Color( 0.25, 0.5f, 1.f ) );
            gl::drawSolidCircle(Vec2f(0,0), circleBody->getRadius());
        }
        
		glPopMatrix();	
	}
}

CINDER_APP_NATIVE( CinderBoxFunApp, RendererGl )
