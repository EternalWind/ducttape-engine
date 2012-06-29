#include <Logic/TriggerAreaComponent.hpp>
#include <Scene/Node.hpp>
#include <Scene/Scene.hpp>
#include <Scene/Component.hpp>

namespace dt
{

TriggerAreaComponent::TriggerAreaComponent(btCollisionShape* areaShape,
                                           const QString name) : 
    Component(name),
    mArea(areaShape),
    mObject(nullptr) { }

void TriggerAreaComponent::onUpdate(double time_diff) {
    if(!isEnabled()) {
        return;
    }

    //// TODO: Update only on node position change
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(BtOgre::Convert::toBullet(getNode()->getPosition(Node::SCENE)));
    transform.setRotation(BtOgre::Convert::toBullet(getNode()->getRotation(Node::SCENE)));
    mObject->setWorldTransform(transform);

    for(int32_t i = 0; i < mObject->getNumOverlappingObjects(); ++i)
    {
        void* user_pointer = mObject->getOverlappingObject(i)->getUserPointer();

        if (user_pointer != nullptr) {
            Component* collidingComponent = static_cast<Component*>(user_pointer);

            if (collidingComponent == nullptr)
                continue;

            if (collidingComponent->getNode() == nullptr)
                continue;

            emit triggered(this, collidingComponent);
        }
    }
}

void TriggerAreaComponent::onInitialize() {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(BtOgre::Convert::toBullet(getNode()->getPosition(Node::SCENE)));
    transform.setRotation(BtOgre::Convert::toBullet(getNode()->getRotation(Node::SCENE)));
    
    mObject = new btGhostObject();
    mObject->setCollisionShape(mArea);
    mObject->setWorldTransform(transform);
    mObject->setCollisionFlags(mObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    mObject->setUserPointer(nullptr);
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mObject);
}

void TriggerAreaComponent::setAreaShape(btCollisionShape* areaShape)
{
    mArea = areaShape;
    mObject->setCollisionShape(mArea);
}

void TriggerAreaComponent::onDeinitialize() {
    //elete mObject;
    //delete mArea;
}
void TriggerAreaComponent::onEnable(){
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mObject);
}
void TriggerAreaComponent::onDisable(){
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->getCollisionWorld()->removeCollisionObject(mObject);
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->removeCollisionObject(mObject);
    this->setAreaShape(new btBoxShape(btVector3(0, 0, 0)));
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mObject);
}

}