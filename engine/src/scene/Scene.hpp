
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SCENE_SCENE
#define DUCTTAPE_ENGINE_SCENE_SCENE

#include <string>

#include <boost/ptr_container/ptr_map.hpp>

#include <OGRE/OgreSceneManager.h>

#include "Config.hpp"
#include "Node.hpp"

namespace dt {

/**
  * A class to represent a whole scene of the game world.
  */
class DUCTTAPE_API Scene : public Node, public EventListener {
public:
    /**
      * Default constructor.
      */
    Scene(const std::string& name);

    void OnInitialize();

    void OnDeinitialize();

    Ogre::SceneManager* GetSceneManager();

    void HandleEvent(std::shared_ptr<Event> e);

protected:
    bool _IsScene();

};

}

#endif
