
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_MANAGER
#define DUCTTAPE_ENGINE_MANAGER

#include "Config.hpp"

namespace dt {

// Manager interface class
class DUCTTAPE_API Manager {
public:
    virtual ~Manager() = 0;
    virtual void Initialize() = 0;
    virtual void Deinitialize() = 0;

    // remember to implement the "static Manager_T Get();" shortcut

};

}

#endif
