#include "Item.hpp"

using namespace ci;
using namespace reactphysics3d;

Item::Item( gl::BatchRef batch, gl::TextureRef texture )
{
    batchRef = batch;
    textureRef = texture;
}

void Item::draw( RigidBody * body )
{
    const Transform& transform = body->getTransform();
    
    const Vector3& position = transform.getPosition();
    
    const Quaternion& orientation = transform.getOrientation();
    
    gl::ScopedModelMatrix scope;
    
    gl::translate( position.x, position.y, position.z );
    
    gl::rotate( quat( orientation.w, orientation.x, orientation.y, orientation.z ) );
    
    gl::ScopedTextureBind tex0( textureRef );
    
    batchRef->draw();
}
