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
    void prepareSettings(Settings *settings);
	void setup();
	void update();
	void draw();
    
    void mouseDown(MouseEvent event);
	
	void addBox(ConstVec &pos);
	void addCircle(ConstVec &pos);
    void addTriangle(ConstVec &pos);
    
    World          *mPhysicsWorld;
    vector<Body*>  mBodies;
};

void CinderBoxFunApp::prepareSettings( Settings* settings )
{
	settings->setFrameRate( 60.0f );
	settings->setFullScreen( false );
	settings->setResizable( false );
	settings->setWindowSize( 1280, 650 );
}

void CinderBoxFunApp::setup()
{
    // Create a physics world with Earth's gravity
    ConstVec gravity = Vec2f(0, 9.8f);
    mPhysicsWorld = new World(gravity);
    // Add a solid ground at the bottom of the window
    mPhysicsWorld->addSolidGround(this);
    mPhysicsWorld->enableDebugDraw();
}

void CinderBoxFunApp::addBox( ConstVec &pos )
{
    Box *box = new Box(pos, 10, 20);
    mPhysicsWorld->addBody(box);
    mBodies.push_back(box);
}

void CinderBoxFunApp::addCircle( ConstVec &pos ) {
    Circle *circle = new Circle(pos, BOX_SIZE);
    mPhysicsWorld->addBody(circle);
    mBodies.push_back(circle);
}

void CinderBoxFunApp::mouseDown( MouseEvent event )
{
    ConstVec pos = event.getPos();
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
