#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include "Physics.h"

using namespace ci;
using namespace ci::app;
using namespace Physics;
using namespace std;

static const float BOX_WIDTH                = 40;
static const float BOX_HEIGHT               = 20;
static const float CIRCLE_RADIUS            = 25;
static const float TRIANGLE_EDGE_LENGTH     = 40;

class CinderBoxFunApp : public AppNative {
  public:
    void            prepareSettings(Settings *settings);
	void            setup();
	void            update();
	void            draw();
    void            drawHelpText();
    void            drawGameboyText(std::string text, Vec2f pos, float size = 32.f) const;
    
    void            mouseMove(MouseEvent event);
	void            keyDown(KeyEvent event);
    
    void            addBody(Body *body);
	void            addBox(ConstVec &pos);
	void            addCircle(ConstVec &pos);
    void            addTriangle(ConstVec &pos);
    void            buildTower();
  
private:
    World           *mPhysicsWorld;
    Vec2i           mLastMousePos;
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
    mPhysicsWorld = new World(Vec2f(0, 9.8f));
    // Add walls around the border of the window
    mPhysicsWorld->addSolidEdges(this);
}

void CinderBoxFunApp::addBox(ConstVec &pos)
{
    addBody(new Box(pos, BOX_WIDTH, BOX_HEIGHT));
}

void CinderBoxFunApp::addCircle(ConstVec &pos)
{
    addBody(new Circle(pos, CIRCLE_RADIUS));
}

void CinderBoxFunApp::addTriangle(ConstVec &pos)
{
    PolyLine2f *points = new PolyLine2f();
    points->push_back(Vec2f(TRIANGLE_EDGE_LENGTH * 0.5f, 0));
    points->push_back(Vec2f(TRIANGLE_EDGE_LENGTH, TRIANGLE_EDGE_LENGTH));
    points->push_back(Vec2f( 0, TRIANGLE_EDGE_LENGTH));

    
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
    int TOWER_CENTER_X      = getWindowWidth() * 0.5f;
    int TOWER_MAX_Y         = getWindowHeight();
    int TOWER_BOX_WIDTH     = 100;
    int TOWER_BOX_HEIGHT    = 10;
    
    for (int i = 0; i < 32; i++) {
        int y = TOWER_MAX_Y - (TOWER_BOX_HEIGHT * 2 * i);
        
        Vec2f pos;
        if (i % 2 == 0) {
            addBody(new Box(Vec2f(TOWER_CENTER_X, y), TOWER_BOX_WIDTH, TOWER_BOX_HEIGHT));
        } else {
            static int THIRD_WIDTH = TOWER_BOX_WIDTH * 0.3f;
            static int LEFT_X = TOWER_CENTER_X - THIRD_WIDTH;
            static int MID_X = TOWER_CENTER_X;
            static int RIGHT_X = TOWER_CENTER_X + THIRD_WIDTH;
            
            addBody(new Box(Vec2f(LEFT_X, y), THIRD_WIDTH, TOWER_BOX_HEIGHT));
            addBody(new Box(Vec2f(MID_X, y), THIRD_WIDTH, TOWER_BOX_HEIGHT));
            addBody(new Box(Vec2f(RIGHT_X, y), THIRD_WIDTH, TOWER_BOX_HEIGHT));
        }
    }
}

void CinderBoxFunApp::mouseMove(MouseEvent event)
{
    // Save the mouse position
    mLastMousePos = event.getPos();
}

void CinderBoxFunApp::keyDown(KeyEvent event)
{
    // Cast the mouse position to a constant
    ConstVec pos = mLastMousePos;
    if (event.getCode() == KeyEvent::KEY_b) {
        addBox(pos);
    } else if (event.getCode() == KeyEvent::KEY_c) {
        addCircle(pos);
    } else if (event.getCode() == KeyEvent::KEY_t) {
        addTriangle(pos);
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
            
//            Physics::Polygon *polyBody = (Physics::Polygon *)body;
            
            gl::color(0.5f, 1, 0.25);
            ConstVec pt1 = Vec2f(TRIANGLE_EDGE_LENGTH * 0.5f,  0);
            ConstVec pt2 = Vec2f(TRIANGLE_EDGE_LENGTH, TRIANGLE_EDGE_LENGTH);
            ConstVec pt3 = Vec2f( 0, TRIANGLE_EDGE_LENGTH);
            gl::drawSolidTriangle(pt1, pt2, pt3);
        }
        
		glPopMatrix();	
	}
    
    drawHelpText();
}

void CinderBoxFunApp::drawHelpText() {
    gl::enableAlphaBlending();
    
    // Draw Help
    Vec2f textPosition = Vec2f(getWindowWidth() * 0.5f, 32.f);
    drawGameboyText("B - Box", textPosition);
    textPosition += Vec2f(0, 32.f);
    drawGameboyText("C - Circle", textPosition);
    textPosition += Vec2f(0, 32.f);
    drawGameboyText("T - Triangle", textPosition);
    
    gl::disableAlphaBlending();
}

void CinderBoxFunApp::drawGameboyText(std::string text, Vec2f pos, float size) const {
    gl::drawStringCentered(text, pos, Color::white(), Font("Early-Gameboy", size));
}

CINDER_APP_NATIVE( CinderBoxFunApp, RendererGl )
