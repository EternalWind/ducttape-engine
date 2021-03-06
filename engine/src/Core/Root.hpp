
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

/**
  * \mainpage
  * \section About
  * Welcome to the documentation for the Ducttape Engine - a universal free and open-source game engine
  * \section License
  * Ducttape itself is licensed under the Lesser GNU Public License version 3.0 (LGPL3). However, it directly and indirectly uses many libraries and media files with different licenses. For a complete list including related license files, please see docs/licenses/.
  * \section Goals
  * \li Compatibility
  * \li Maintainability
  * \li Usability
  * \li Performance
  * \li Features
  * \li Extensibility
  * \section Credits
  * \subsection Programming
  * \li Paul \a 'opatut' Bienkowski
  * \li Sven-Hendrik \a 'Svenstaro' Haase
  * \li Matz-Jona \a 'Timesqueezer' Radloff
  * \li Fabian \a 'zetaron' Stegemann
  * \li Thomas \a 'tomt610' Fiedor
  * \li Antonio \a 'amalvagomes' MalvaGomes
  * \subsection Media
  * \li Darren \a 'visionseeker' Cullen (http://www.deliciousmusic.co.nz/artists/visionseeker)
  * \li Lasse \a 'lazzly' Bienkowski
  */

#ifndef DUCTTAPE_ENGINE_ROOT
#define DUCTTAPE_ENGINE_ROOT

#include <Config.hpp>

#include <SFML/System/Clock.hpp>

#include <QCoreApplication>

namespace dt {

class LogManager;
class ResourceManager;
class InputManager;
class DisplayManager;
class StateManager;
class NetworkManager;
class PhysicsManager;
class TerrainManager;
class ScriptManager;

/**
  * Engine Root class holding various Manager instances. This class is designed to be the only singleton in the whole engine,
  * so the creation order can be controlled.
  * @see LogManager
  * @see StateManager
  */
class DUCTTAPE_API Root {
    
    Q_DISABLE_COPY(Root)
    
public:
    static QString _VERSION;  //!< Metadata: engine version number (Format: "0.0.0")

    /**
      * Destructor. All instances are deleted here.
      */
    ~Root();

    /**
     * Gets singleton instance reference.
     * @returns singleton instance reference to itself
     */
    static Root& getInstance();

    /**
      * Initializes all managers.
      */
    void initialize(int argc, char** argv);

    /**
      * Deinitializes all managers.
      */
    void deinitialize();

    /**
      * Gets time since calling Initialize().
      * @returns The time in seconds since calling Initialize()
      */
    double getTimeSinceInitialize() const;

    /**
      * Gets whether the game has been paused or not.
      * @returns Whether the game has been paused or not.
      */
    bool hasPaused() const;

    /**
      * Pause the game.
      */
    void pause();

    /**
      * Resume the game.
      */
    void resume();

    /**
      * Returns the LogManager.
      * @returns the LogManager
      */
    LogManager* getLogManager();

    /**
      * Returns the StateManager.
      * @returns the StateManager
      */
    StateManager* getStateManager();

    /**
      * Returns the NetworkManager.
      * @returns the NetworkManager
      */
    NetworkManager* getNetworkManager();

    /**
      * Returns the DisplayManager.
      * @returns the DisplayManager
      */
    DisplayManager* getDisplayManager();

    /**
      * Returns the InputManager.
      * @returns the InputManager
      */
    InputManager* getInputManager();

    /**
      * Returns the ResourceManager.
      * @returns the ResourceManager
      */
    ResourceManager* getResourceManager();

    /**
      * Returns the PhysicsManager.
      * @returns the PhysicsManager
      */
    PhysicsManager* getPhysicsManager();

    /**
      * Returns the ScriptManager.
      * @returns the ScriptManager
      */
    ScriptManager* getScriptManager();

    /**
      * Returns the TerrainManager.
      * @returns the TerrainManager
      */
    TerrainManager* getTerrainManager();

private:
    /**
      * Private default constructor (for singleton). All instances are created here.
      */
    Root();

    sf::Clock mSfClock;                 //!< Clock for keeping time since Initialize() was called.
    QCoreApplication* mCoreApplication; //!< Pointer to the Qt Core Application (required for QScriptEngine and command line parameter parsing).

    LogManager* mLogManager;            //!< Pointer to the LogManager.
    ResourceManager* mResourceManager;  //!< Pointer to the ResourceManager.
    InputManager* mInputManager;        //!< Pointer to the InputManager.
    DisplayManager* mDisplayManager;    //!< Pointer to the DisplayManager.
    StateManager* mStateManager;        //!< Pointer to the StateManager.
    NetworkManager* mNetworkManager;    //!< Pointer to the NetworkManager.
    PhysicsManager* mPhysicsManager;    //!< Pointer to the PhysicsManager.
    TerrainManager* mTerrainManager;    //!< Pointer to the TerrainManager.
    ScriptManager* mScriptManager;      //!< Pointer to the ScriptManager.

    bool mHasPaused;                    //!< Specify whether the game has been paused or not.
};

}

#endif
