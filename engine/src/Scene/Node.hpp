
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SCENE_NODE
#define DUCTTAPE_ENGINE_SCENE_NODE

#include <Config.hpp>

#include <Scene/Component.hpp>
#include <Utils/Logger.hpp>
#include <Utils/Utils.hpp>
#include <Logic/IScriptable.hpp>
#include <Network/IOPacket.hpp>

#include <OgreQuaternion.h>
#include <OgreVector3.h>

#include <QObject>
#include <QString>

#include <memory>

namespace dt {

// forward declaration due to circular dependency
class Scene;
class State;

/**
  * Basic scene object class.
  * Any object in a scene is described by a node with a position, scale and rotation
  * and other child nodes. The Node class is also able to have components to control
  * its behaviour, e.g. the look or events.
  * @see Component
  */
class DUCTTAPE_API Node : public QObject, public IScriptable {
    Q_OBJECT
    Q_ENUMS(RelativeTo)

    Q_PROPERTY(QString name READ getName CONSTANT FINAL)
    Q_PROPERTY(QScriptValue parent READ getScriptParent FINAL)
    Q_PROPERTY(QScriptValue scene READ getScriptScene FINAL)
    Q_PROPERTY(QScriptValue state READ getScriptState FINAL)

public:
    
    typedef std::shared_ptr<Node> NodeSP;
    
    /**
      * The coordinates space for getting/setting rotation, position and scale.
      */
    enum RelativeTo {
        PARENT, //!< Relative to the parent node.
        SCENE   //!< Relative to the scene root node (i.e. absolute value).
    };

    /**
      * Constructor.
      * @param name The name of the Node.
      */
    Node(const QString name = "");

    /**
      * Initializer.
      */
    void initialize();

    /**
      * Deinitializer. Cleans up the whole mess :D
      */
    void deinitialize();

    /**
      * Called when the Node is initialized.
      */
    virtual void onInitialize();

    /**
      * Called when the Node is deinitialized.
      */
    virtual void onDeinitialize();

    /**
      * Adds a Node as child.
      * @param child The Node to be added as child
      * @returns A pointer to the Node.
      */
    Node::NodeSP addChildNode(Node* child);

    /**
      * Assigns a component to this node.
      * @param component The Component to be assigned.
      * @returns A pointer to the new component.
      */
    template <typename ComponentType>
    std::shared_ptr<ComponentType> addComponent(ComponentType* component) {
        const QString cname = component->getName();
        if(!hasComponent(cname)) {
            std::shared_ptr<Component> ptr(component);
            ptr->setNode(this);
            ptr->initialize();
            std::pair<QString, std::shared_ptr<Component> > pair(cname, ptr);
            mComponents.insert(pair);
            
            if(!mIsEnabled)
                component->disable();

            _updateAllComponents(0);
        } else {
            Logger::get().error("Cannot add component " + cname + ": a component with this name already exists.");
        }
        return findComponent<ComponentType>(cname);
    }

    /**
      * Searches for a Node with the given name and returns a pointer to the first match.
      * @param name The name of the Node searched.
      * @param recursive Whether to search within child nodes or not.
      * @returns A pointer to the Node with the name or nullptr if none is found.
      */
    Node::NodeSP findChildNode(const QString name, bool recursive = true);

    /**
      * Returns a component.
      * @param name The name of the component to find.
      * @returns A pointer to the component, or nullptr if no component with the specified name exists.
      */
    template <typename ComponentType>
    std::shared_ptr<ComponentType> findComponent(const QString name) {
        if(!hasComponent(name))
            return std::shared_ptr<ComponentType>();
        return std::dynamic_pointer_cast<ComponentType>(mComponents[name]);
    }

    /**
      * Returns whether this node has the component assigned.
      * @param name The name of the Component.
      * @returns true if the component is assigned, otherwise false
      */
    bool hasComponent(const QString name);

    /**
      * Removes a child Node with a specific name.
      * @param name The name of the Node to be removed.
      */
    void removeChildNode(const QString name);

    /**
      * Removes a Component with a specific name.
      * @param name The name of the Component to be removed.
      */
    void removeComponent(const QString name);

    /**
      * Returns the position of the Node.
      * @param rel Reference point.
      * @returns The Node position.
      */
    Ogre::Vector3 getPosition(RelativeTo rel = PARENT) const;

    /**
      * Sets the position of the Node.
      * @param position The new position of the Node.
      * @param rel Reference point.
      */
    void setPosition(Ogre::Vector3 position, RelativeTo rel = PARENT);

    /**
      * Returns the scale of the Node.
      * @param rel Reference scale.
      * @returns The scale of the Node
      */
    Ogre::Vector3 getScale(RelativeTo rel = PARENT) const;

    /**
      * Sets the scale of the Node.
      * @param scale The new scale.
      * @param rel Reference scale.
      */
    void setScale(Ogre::Vector3 scale, RelativeTo rel = PARENT);

    /**
      * Sets the scale of the Node.
      * @param scale The new scale to use for all axis.
      * @param rel Reference scale.
      */
    void setScale(float scale, RelativeTo rel = PARENT);

    /**
      * Returns the rotation of the Node.
      * @param rel Reference rotation.
      * @returns The Rotation of the Node.
      */
    Ogre::Quaternion getRotation(RelativeTo rel = PARENT) const;

    /**
      * Sets the rotation of the Node.
      * @param rotation The rotation to set.
      * @param rel Reference rotation.
      */
    void setRotation(Ogre::Quaternion rotation, RelativeTo rel = PARENT);

    /**
      * Sets the direction the Node is facing.
      * @param direction The direction the Node is facing.
      * @param front_vector The local direction that specifies the front of the Node (which part of the Node should be facing into the direction).
      */
    void setDirection(Ogre::Vector3 direction, Ogre::Vector3 front_vector = Ogre::Vector3::UNIT_Z);

    /**
      * Rotates the node to look at the target.
      * @param target The point the node should look at.
      * @param front_vector The local direction that specifies the front of the Node (which part of the Node should be facing into the direction).
      * @param rel Reference position.
      */
    void lookAt(Ogre::Vector3 target, Ogre::Vector3 front_vector = Ogre::Vector3::UNIT_Z, RelativeTo rel = PARENT);

    /**
      * Sets the parent Node pointer.
      * @param parent The parent Node pointer.
      */
    void setParent(Node* parent);

    /**
      * Called when the Node is being updated.
      * @param time_diff The frame time.
      */
    virtual void onUpdate(double time_diff);

    void serialize(IOPacket& packet);

    virtual void onSerialize(IOPacket& packet);

    /**
      * Called when the node is enabled.
      */
    virtual void onEnable();

    /**
      * Called when the node is disabled.
      */
    virtual void onDisable();

    /**
      * Returns the current State.
      * @returns The current State.
      */
    State* getState();

    /**
      * Returns a pointer to the parent Node.
      * @returns A pointer to the parent Node.
      */
    Node* getParent();

    /**
      * Returns the Scene this Node is attached to.
      * @returns The Scene this Node is attached to.
      */
    Scene* getScene();

public slots:
    /**
      * Returns the name of the Node.
      * @returns The name of the Node.
      */
    const QString getName() const;

    /**
      * Returns the name of the Node, including all parent names.
      * @returns The name of the Node, including all parent names.
      */
    QString getFullName() const;

    /**
      * Returns the current State. For script use.
      * @returns The current State.
      */
    QScriptValue getScriptState();

    /**
      * Returns the parent of the Node. For script use.
      * @returns The parent of the Node.
      */
    QScriptValue getScriptParent();

    /**
      * Returns the Scene. For script use.
      * @returns The Scene.
      */
    QScriptValue getScriptScene();

    /**
      * Sets the position of the Node.
      * @param x The x position.
      * @param y The y position.
      * @param z The z position.
      * @param rel Reference point.
      */
    void setPosition(float x, float y, float z, RelativeTo rel = PARENT);

    /**
      * Sets the death mark to true. Then the node will be kill when it updates.
      */
    void kill();

    /**
      * Enables the node. If a node is enabled, all of its components and child nodes are enabled but
      * its components and child nodes can be disabled manually by the user.
      */
    void enable();

    /**
      * Disables the node. If a node is disabled, all of its components and child nodes are disabled 
      * and its components or child nodes can't be enabled at this situation.
      */
    void disable();

    /**
      * Returns whether the node is enabled.
      * @returns Whether the node is enabled.
      */
    bool isEnabled();

    QScriptValue toQtScriptObject();

signals:
    void positionChanged();

protected:
    /**
      * Returns whether this Node is a Scene.
      * @internal
      * @returns Whether this Node is a Scene.
      */
    virtual bool _isScene();

    /**
      * Updates all components.
      * @param time_diff The frame time.
      * @see Component::OnUpdate(double time_diff);
      */
    void _updateAllComponents(double time_diff);

    /**
      * Updates all child nodes.
      * @param time_diff The frame time.
      * @see OnUpdate(double time_diff);
      */
    void _updateAllChildren(double time_diff);

    std::map<QString, std::shared_ptr<Component> > mComponents;   //!< The list of Components.
    QString mName;                                                //!< The Node name.
    bool mIsUpdatingAfterChange;                                  //!< Whether the node is just in the process of updating all components after a change occurred. This is to prevent infinite stack loops.

private:
    std::map<QString, NodeSP> mChildren;                          //!< List of child nodes.
    Ogre::Vector3 mPosition;                                      //!< The Node position.
    Ogre::Vector3 mScale;                                         //!< The Node scale.
    Ogre::Quaternion mRotation;                                   //!< The Node rotation.
    Node* mParent;                                                //!< A pointer to the parent Node.
    QUuid mId;                                                    //!< The node's uuid.
    bool mDeathMark;                                              //!< Whether the node is marked to be killed. If it's true, the node will be killed when it updates.
    bool mIsEnabled;                                              //!< Whether the node is enabled or not.
};

} // namespace dt

#endif
