
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Logic/RaycastComponent.hpp>
#include <Physics/PhysicsWorld.hpp>
#include <Physics/PhysicsBodyComponent.hpp>
#include <Scene/Scene.hpp>

#include <BtOgreGP.h>

namespace dt {

RaycastComponent::RaycastComponent(const QString name)
    : InteractionComponent(name) {}

void RaycastComponent::onCheck(const Vector3& start, const Vector3& end) {
    btVector3 bt_start, bt_end;
    bt_start = BtOgre::Convert::toBullet(start.getOgreVector3());
    bt_end = BtOgre::Convert::toBullet(end.getOgreVector3());

    btCollisionWorld::ClosestRayResultCallback raycast_callback(bt_start, bt_end);

    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->rayTest(bt_start, bt_end, raycast_callback);

    if(raycast_callback.hasHit()) {
        btCollisionObject* collision_object = raycast_callback.m_collisionObject;
        PhysicsBodyComponent* hit_object = static_cast<PhysicsBodyComponent*>(collision_object->getUserPointer());
        
        emit sHit(hit_object);
    }
}

}
