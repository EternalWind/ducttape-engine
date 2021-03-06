
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_COMPONENT_ADVANCEDPLAYERCOMPONENT
#define DUCTTAPE_ENGINE_COMPONENT_ADVANCEDPLAYERCOMPONENT

#include <Config.hpp>

#include <Scene/Component.hpp>
#include <Input/InputManager.hpp>

#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btHeightfieldTerrainShape.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>
#include <BulletDynamics/Character/btKinematicCharacterController.h>

#define OIS_DYNAMIC_LIB
#include <OIS.h>

#include <QString>

namespace dt {

/**
  * A component to deal with the input using bullet's built-in character controller.
  */
class DUCTTAPE_API AdvancedPlayerComponent : public Component {
    Q_OBJECT
public:
    DT_SERIALIZABLE(AdvancedPlayerComponent)
    /**
      * Advanced constructor.
      * @param name The name of the Component.
      * @see Component
      */
    AdvancedPlayerComponent(const QString name = "");

    virtual void onInitialize();
    virtual void onDeinitialize();
    virtual void onEnable();
    virtual void onDisable();
    virtual void onUpdate(double time_diff);

    /**
      * Sets whether the keyboard is enabled or not.
      * @param is_keyboard_enabled Whether the keyboard is enabled or not.
      */
    void setKeyboardEnabled(bool is_keyboard_enabled);

    /**
      * Gets whether the keyboard is enabled or not.
      * @returns Whether the keyboard is enabled or not.
      */
    bool getKeyboardEnabled() const;

    /**
      * Sets the speed the player moves at.
      * @param move_speed The maximum speed, in units per second.
      */
    void setMoveSpeed(float move_speed);

    /**
      * Gets the speed the player moves at.
      * @returns The player speed, in units per second.
      */
    float getMoveSpeed() const;

    /**
      * Sets whether the mouse is enabled for looking around.
      * @param mouse_enabled Whether the mouse is enabled for looking around.
      */
    void setMouseEnabled(bool mouse_enabled);

    /**
      * Gets whether the mouse is enabled for looking around.
      * @returns Whether the mouse is enabled for looking around.
      */
    bool getMouseEnabled() const;

    /**
      * Sets the mouse sensitivity. Default: 1.0.
      * @param mouse_sensitivity The mouse sensitivity. Default: 1.0.
      */
    void setMouseSensitivity(float mouse_sensitivity);

    /**
      * Gets the mouse sensitivity. Default: 1.0.
      * @returns The mouse sensitivity. Default: 1.0.
      */
    float getMouseSensitivity() const;

    /**
      * Sets whether the mouse y-axis should be inversed.
      * @param mouse_y_inversed Whether the mouse y-axis should be inversed.
      */
    void setMouseYInversed(bool mouse_y_inversed);

    /**
      * Gets whether the mouse y-axis should be inversed.
      * @returns Whether the mouse y-axis should be inversed.
      */
    bool getMouseYInversed() const;

    /**
      * Sets whether the character can jump or not.
      * @param jump_enabled Whether the character can jump or not.
      */
    void setJumpEnabled(bool jump_enabled);

    /**
      * Gets whether the character can jump or not.
      * @returns Whether the character can jump or not.
      */
    bool getJumpEnabled() const;

    /**
      * Gets whether the mouse's key pressing effect is one-shot or not.
      * @param mouse_button Specify which mouse button. Only accept MB_Left and MB_Right. 
      * If none of them is given, it will treat it as MB_Right.
      * @returns Whether the mouse's key pressing effect is one-shot or not.
      */
    bool getIsOneShot(OIS::MouseButtonID mouse_button) const;

    /**
      * Sets whether the mouse's key pressing effect is one-shot or not.
      * @param is_one_shot Whether the mouse's key pressing effect is one-shot or not.
      * @param mouse_button Specify which mouse button. Only accept MB_Left and MB_Right.
      * * If none of them is given, it will treat it as MB_Right.
      */
    void setIsOneShot(bool is_one_shot, OIS::MouseButtonID mouse_button);

protected:
    /**
      * Called every frame if the mouse event is triggered. Override it to use your own handling logic.
      * A mouse event is triggered once when you push down the mouse button under the one-shot mode.
      * Otherwise, it is triggered every frame if you've pushed down the mouse button and havn't released it yet.
      */
    virtual void _onMouseTriggered() {}

private slots:
    /**
      * Handles the events triggered by pressing a key or a mouse button.
      * @param input_code The input code.
      * @param event The event argument.
      */
    void _handleButtonDown(dt::InputManager::InputCode input_code, const OIS::EventArg& event);

    /**
      * Handles the events triggered by moving the mouse.
      * @param event The mouse-moving event.
      */
    void _handleMouseMove(const OIS::MouseEvent& event);

    /**
      * Handles the events triggered by releasing a key or a mouse button.
      * @param input_code The input code.
      * @param event The event argument.
      */
    void _handleButtonUp(dt::InputManager::InputCode input_code, const OIS::EventArg& event);

signals:
    /**
      * A signal which will be emitted when the player starts to move when he's stopping or has done jumping.
      */
    void sMove();

    /**
      * A signal which will be emitted when the player starts to stop or jump when he's walking.
      */
    void sStop();

    /**
      * A signal which will be emitted when the player jumps.
      */
    void sJump();

private:
    std::shared_ptr<btKinematicCharacterController> mBtController;       //!< The bullet's built-in character controller.
    std::shared_ptr<btPairCachingGhostObject> mBtGhostObject;            //!< The bullet's ghost object.;
    bool mMouseEnabled;         //!< Whether the Mouse is enabled for looking around or not.
    float mMouseSensitivity;    //!< The sensitivity of the mouse. Default: 1.0.
    bool mMouseYInversed;       //!< True if the mouse's y-axis should be inversed.
    btVector3 mMove;            //!< Used to keep track of the movement.
    float mMoveSpeed;           //!< The speed to move at. Default: 5.0. In units per second.
    bool mKeyboardEnabled;      //!< Whether the keyboard is enabled or not.
    bool mJumpEnabled;          //!< Whether the character can jump or not.
    bool mIsLeftOneShot;        //!< Whether the mouse's left button pressing effect is one-shot or not.
    bool mIsRightOneShot;       //!< Whether the mouse's right button pressing effect is one-shot or not.
    bool mIsMoving;             //!< Whether the player is moving or not.

protected:
    bool mIsLeftMouseDown;      //!< Whether the mouse's left button is down or not.
    bool mIsRightMouseDown;     //!< Whether the mouse's right button is down or not.
};
}

#endif
