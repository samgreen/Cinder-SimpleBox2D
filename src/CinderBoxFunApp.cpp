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
	void            setup();
	void            update();
	void            draw();
    
    void            mouseDown(MouseEvent event);
	
    void            addBody(Body *body);
	void            addBox(ConstVec &pos);
	void            addCircle(ConstVec &pos);
    void            addTriangle(ConstVec &pos);
    void            buildTower();
    
    World           *mPhysicsWorld;
    vector<Body*>   mBodies;
};

void CinderBoxFunApp::prepareSettings( Settings* settings )
{
	settings->setFrameRate( 60.0f );
	settings->setFullScreen( false );
	settings->setResizable( false );
	settings->setWindowSize( 1280, 700 );
}

void CinderBoxFunApp::setup()
{
    // Create a physics world with Earth's gravity
    ConstVec gravity = Vec2f(0, 9.8f);
    mPhysicsWorld = new World(gravity);
    // Add a solid ground at the bottom of the window
    mPhysicsWorld->addSolidGround(this);
    mPhysicsWorld->enableDebugDraw();
    
    buildTower();
}

void CinderBoxFunApp::addBox(ConstVec &pos)
{
    Box *box = new Box(pos, 20, 10);
    addBody(box);
}

void CinderBoxFunApp::addCircle(ConstVec &pos)
{
    Circle *circle = new Circle(pos, BOX_SIZE);
    addBody(circle);
}

void CinderBoxFunApp::addTriangle(ConstVec &pos)
{
    PolyLine2f *points = new PolyLine2f();
    points->push_back(Vec2f(10, 0));
    points->push_back(Vec2f(20, 20));
    points->push_back(Vec2f(0, 20));

    
    Physics::Polygon *triangle = new Physics::Polygon(pos, points);
    addBody(triangle);
}

void CinderBoxFunApp::addBody(Body *body)
{
    mPhysicsWorld->addBody(body);
    mBodies.push_back(body);
}

void CinderBoxFunApp::buildTower()
{
    int CENTER_X = getWindowWidth() * 0.5f;
    int MAX_Y = getWindowHeight();
    int BOX_WIDTH = 100;
    int BOX_HEIGHT = 10;
    
    for (int i = 0; i < 32; i++) {
        int y = MAX_Y - (BOX_HEIGHT * 2 * i);
        ConstVec *pos = new Vec2f(CENTER_X, y);
        
        Box *box = NULL;
        if (i % 2 == 0) {
            box = new Box(*pos, BOX_WIDTH, BOX_HEIGHT);
        } else {
            box = new Box(*pos, BOX_WIDTH, BOX_HEIGHT);
        }
        addBody(box);
    }
}

void CinderBoxFunApp::mouseDown(MouseEvent event)
{
    ConstVec pos = event.getPos();
    
    if (event.isShiftDown()) {
        addTriangle(pos);
    } else if (event.isControlDown()) {
        addCircle(pos);
    } else {
        addBox(pos);
        ConstVec *gravity = new ConstVec(5, 2.5);
        mPhysicsWorld->setGravity(*gravity);
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
        } else if (body->getBodyType() == BodyTypeCircle) {
            
            Circle *circleBody = (Circle *)body;
            
            gl::color( Color( 0.25, 0.5f, 1.f ) );
            gl::drawSolidCircle(Vec2f(0,0), circleBody->getRadius());
        } else if (body->getBodyType() == BodyTypePolygon) {
            
            Physics::Polygon *polyBody = (Physics::Polygon *)body;
            
            gl::color(0.5f, 1, 0.25);
            ConstVec pt1 = Vec2f(10,  0);
            ConstVec pt2 = Vec2f(20, 20);
            ConstVec pt3 = Vec2f( 0, 20);
            gl::drawSolidTriangle(pt1, pt2, pt3);
        }
        
		glPopMatrix();	
	}
}

CINDER_APP_NATIVE( CinderBoxFunApp, RendererGl )
