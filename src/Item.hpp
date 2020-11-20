#ifndef Item_hpp
#define Item_hpp

#include "reactphysics3d/reactphysics3d.h"

class Item {
    
public:
    
    Item( cinder::gl::BatchRef, cinder::gl::TextureRef );
    
    void draw( reactphysics3d::RigidBody * );
    
private:
    
    cinder::gl::BatchRef batchRef;
    cinder::gl::TextureRef textureRef;
    
};

#endif /* Item_hpp */
