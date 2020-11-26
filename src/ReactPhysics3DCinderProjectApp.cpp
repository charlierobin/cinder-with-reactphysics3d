#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include <math.h>

#include "reactphysics3d/reactphysics3d.h"

#include "Item.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

using namespace reactphysics3d;

class ReactPhysics3DCinderProjectApp : public App, public EventListener {
    
public:
    
    void setup() override;
    void update() override;
    void draw() override;
    void resize() override;
    void quit() override;
    
    void keyDown( KeyEvent event ) override;
    
    void onContact( const CollisionCallback::CallbackData& ) override;
    
private:
    
    void createPlatform( vec3, vec3, float );
    void createBall( float, vec3 );
    
    void handleRemovals();
    
    PhysicsCommon physicsCommon_;
    
    PhysicsWorld * physicsWorld_;
    
    CameraPersp camera_;
    
    set< RigidBody * > toRemove_;
    
    const float timestep_ = 1 / 60.0;
    
    chrono::high_resolution_clock::time_point lastTimeSample_;
    float accumulator_;
    
    gl::GlslProgRef shader_;
    gl::TextureRef texture_;
    
    CollisionBody * outOfBounds_;
    
    int total_ = 0;
    int active_ = 0;
    int removed_ = 0;
};

#define CENTRE_OF_THE_WORLD cinder::vec3( 0, 0, 0 )
#define CAMERA_POSITION cinder::vec3( 0, 30, -100 )
#define FAR_CLIP 20000
#define ONE_DEGREE ( M_PI / 180 )

void ReactPhysics3DCinderProjectApp::setup()
{
    setFrameRate( 60 );
    
    camera_.lookAt( CAMERA_POSITION, CENTRE_OF_THE_WORLD );
    camera_.setFarClip( FAR_CLIP );
    
    shader_ = cinder::gl::context()->getStockShader( cinder::gl::ShaderDef().texture().lambert() );
    
    texture_ = gl::Texture::create( loadImage( app::loadResource( "grid_512.png" ) ) );
    
    physicsWorld_ = physicsCommon_.createPhysicsWorld();
    
    createPlatform( vec3( 50, 1, 20 ), vec3( 20, 15, 0 ), 5 * ONE_DEGREE );
    createPlatform( vec3( 10, 1, 20 ), vec3( 45, 24, 0 ), 90 * ONE_DEGREE );
    
    createPlatform( vec3( 50, 1, 20 ), vec3( -20, 3, 0 ), - 5 * ONE_DEGREE );
    createPlatform( vec3( 10, 1, 20 ), vec3( -45, 12, 0 ), 90 * ONE_DEGREE );
    
    createPlatform( vec3( 50, 1, 20 ), vec3( 20, -9, 0 ), 5 * ONE_DEGREE );
    createPlatform( vec3( 10, 1, 20 ), vec3( 45, 0, 0 ), 90 * ONE_DEGREE );
    
    createPlatform( vec3( 50, 1, 20 ), vec3( -20, -21, 0 ), - 5 * ONE_DEGREE );
    createPlatform( vec3( 10, 1, 20 ), vec3( -45, -12, 0 ), 90 * ONE_DEGREE );
    
    outOfBounds_ = physicsWorld_->createCollisionBody( Transform( Vector3( 0, -60, 0 ), Quaternion::identity() ) );
    CollisionShape * boxShape = physicsCommon_.createBoxShape( Vector3( 500, 5, 500 ) );
    outOfBounds_->addCollider( boxShape, Transform::identity() );
    
    physicsWorld_->setEventListener( this );
}

void ReactPhysics3DCinderProjectApp::quit()
{
    physicsCommon_.destroyPhysicsWorld( physicsWorld_ );
}

void ReactPhysics3DCinderProjectApp::onContact( const CollisionCallback::CallbackData& callbackData )
{
    for ( int i = 0; i < callbackData.getNbContactPairs(); ++i )
    {
        CollisionCallback::ContactPair contactPair = callbackData.getContactPair( i );
        
        if ( contactPair.getBody1() == outOfBounds_ || contactPair.getBody2() == outOfBounds_ )
        {
            RigidBody * ball;
            
            if ( contactPair.getBody1() != outOfBounds_ )
            {
                ball = ( RigidBody * )contactPair.getBody1();
            }
            else
            {
                ball = ( RigidBody * )contactPair.getBody2();
            }
            
            toRemove_.insert( ball );
        }
    }
}

void ReactPhysics3DCinderProjectApp::createBall( float radius, vec3 position )
{
    auto geometry = geom::Sphere().subdivisions( 24 ).radius( radius );
    
    RigidBody * body = physicsWorld_->createRigidBody( Transform( Vector3( position.x, position.y, position.z ), Quaternion::identity() ) );
    
    CollisionShape * sphereShape = physicsCommon_.createSphereShape( radius );
    
    body->addCollider( sphereShape, Transform::identity() );
    
    cinder::gl::BatchRef ref = gl::Batch::create( geometry, shader_ );
    
    body->setUserData( new Item( ref, texture_ ) );
    
    active_++;
    
    total_++;
}

void ReactPhysics3DCinderProjectApp::createPlatform( vec3 dimensions, vec3 position, float angle )
{
    auto geometry = geom::Cube().size( dimensions );
    
    RigidBody * body = physicsWorld_->createRigidBody( Transform( Vector3( position.x, position.y, position.z ), Quaternion::fromEulerAngles( 0, 0, angle ) ) );
    
    body->setType( BodyType::STATIC );
    
    CollisionShape * boxShape = physicsCommon_.createBoxShape( Vector3( dimensions.x / 2, dimensions.y / 2, dimensions.z / 2 ) );
    
    body->addCollider( boxShape, Transform::identity() );
    
    cinder::gl::BatchRef ref = gl::Batch::create( geometry, shader_ );
    
    body->setUserData( new Item( ref, texture_ ) );
}

void ReactPhysics3DCinderProjectApp::resize()
{
    camera_.setAspectRatio( getWindowAspectRatio() );
}

void ReactPhysics3DCinderProjectApp::keyDown( KeyEvent event )
{
    if ( event.getCode() == KeyEvent::KEY_SPACE )
    {
        createBall( randFloat( 2, 4 ), vec3( randFloat( 15, 20 ), 30, randFloat( -0.5, 0.5 ) ) );
    }
}

void ReactPhysics3DCinderProjectApp::handleRemovals()
{
    for ( auto body : toRemove_ )
    {
        Item * item = ( Item * )body->getUserData();
        
        body->setUserData( nullptr );
        
        delete item;
        
        physicsWorld_->destroyRigidBody( body );
        
        active_--;
        
        removed_++;
    }
    
    toRemove_.clear();
}

void ReactPhysics3DCinderProjectApp::update()
{
    chrono::high_resolution_clock::time_point thisTimeSample = chrono::high_resolution_clock::now();
    
    float nanoseconds = chrono::duration_cast<chrono::nanoseconds>( thisTimeSample - lastTimeSample_ ).count();
    
    float seconds = nanoseconds / 1000000000;
    
    lastTimeSample_ = thisTimeSample;
    
    accumulator_ = accumulator_ + seconds;
    
    while ( accumulator_ >= timestep_ ) {
    
        physicsWorld_->update( timestep_ );
        
        accumulator_ = accumulator_ - timestep_;
    }
    
    handleRemovals();
    
    getWindow()->setTitle( to_string( active_ ) + " active, " + to_string( removed_ ) + " removed (" + to_string( total_ ) + " total)" );
}

void ReactPhysics3DCinderProjectApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
    gl::enableDepthRead();
    gl::enableDepthWrite();
    
    gl::setMatrices( camera_ );
    
    for ( int i = 0; i < physicsWorld_->getNbRigidBodies(); ++i )
    {
        RigidBody * body = physicsWorld_->getRigidBody( i );
        
        if ( body->getUserData() == nullptr ) continue;
        
        Item * item = ( Item * )body->getUserData();
        
        item->draw( body );
    }
    
    gl::setMatricesWindow( getWindowSize() );
}

CINDER_APP( ReactPhysics3DCinderProjectApp, RendererGl )



