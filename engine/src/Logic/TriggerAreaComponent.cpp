#include <Logic/TriggerAreaComponent.hpp>
#include <Scene/Node.hpp>
#include <Scene/Scene.hpp>
#include <Scene/Component.hpp>

namespace dt
{

TriggerAreaComponent::TriggerAreaComponent(btCollisionShape* areaShape,
                                           const QString name) : 
    Component(name),
    mArea(areaShape) { }

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
        Component* collidingComponent = static_cast<Component*>(mObject->getOverlappingObject(i)->getUserPointer());
        emit triggered(this, collidingComponent);
    }
}

void TriggerAreaComponent::onInitialize() {
    btTransform transform;
    transform.setIdentity();
    transform.setOrigin(BtOgre::Convert::toBullet(getNode()->getPosition(Node::SCENE)));
    transform.setRotation(BtOgre::Convert::toBullet(getNode()->getRotation(Node::SCENE)));
    
    mObject.reset(new btGhostObject());
    mObject->setCollisionShape(mArea.get());
    mObject->setWorldTransform(transform);
    mObject->setCollisionFlags(mObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    getNode()->getScene()->getPhysicsWorld()->getBulletWorld()->addCollisionObject(mObject.get());
}

void TriggerAreaComponent::setAreaShape(btCollisionShape* areaShape)
{
    mArea.reset(areaShape);
    mObject->setCollisionShape(mArea.get());
}

void TriggerAreaComponent::onDeinitialize() {}
void TriggerAreaComponent::onEnable(){}
void TriggerAreaComponent::onDisable(){}

}