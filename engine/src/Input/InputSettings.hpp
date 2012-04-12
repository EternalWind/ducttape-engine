
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_KEYSETTINGS
#define DUCTTAPE_ENGINE_KEYSETTINGS

#include <Config.hpp>

#include <Input/InputManager.hpp>

#include <QString>

#include <map>
#include <list>

namespace dt {

    /**
      * A class to hold the input settings.
      */
    class DUCTTAPE_API InputSettings {
    public:

        typedef std::list<std::pair<InputManager::InputCode, QString>>::iterator InputMapping;

        /**
          * Constructor.
          */
        InputSettings();

        /**
          * Adds a mapping of a function and a key.
          * @param function The name of the function.
          * @param key The corresponding key. Default value is NONE.
          * @returns Returns false if the function has already been added. Else returns ture.
          */
        bool addFunction(QString function, InputManager::InputCode key = InputManager::NONE);

        /**
          * Removes a mapping of a function and a key.
          * @param function The name of the function.
          * @returns Returns false if the function is not contained in this KeySettings. Otherwise, returns true.
          */
        bool removeFunction(QString function);

        /**
          * Maps a new key to a given function.
          * @param function The name of the function you want to map.
          * @param key The new key.
          * @returns Returns false when the function you are going to map has not been added yet and true if the setting is successful.
          */
        bool setKey(QString function, InputManager::InputCode key);

        /**
          * Gets a mapping pair containing the given function.
          * @param function The function for search.
          * @returns The mapping pair or the location succeeding the last mapping pair if the given function has not yet been added.
          */
        InputMapping getByFunction(QString function);

        /**
          * Gets a mapping pair containing the given key.
          * @param key The key for search.
          * @returns The mapping pair or the location succeeding the last mapping pair if the given key is NONE or has not yet been mapped to any function.
          */
        InputMapping getByKey(InputManager::InputCode key);

        /**
          * Gets a iterator that points to the first element of the key-function mapping.
          * @returns The iterator that points to the first element of the mapping between the function and the key.
          */
        InputMapping begin();

        /**
          * Gets the past-the-end iterator of the key-function mapping.
          * @returns The past-the-end iterator.
          */
        InputMapping end();

        /**
          * Checks if a key has been mapped to a function.
          * @param key The key to check.
          * @returns Whether this key has been mapped.
          */
        bool isMapped(InputManager::InputCode key);

        /**
          * Checks if the Y axis is inversed for the mouse.
          * @returns Whether the Y axis is inversed for the mouse.
          */
        bool isYInversed() const;

        /**
          * Sets the Y axis inversed or not.
          * @param is_inversed Whether the Y axis is inversed for the mouse.
          */
        void setYInversed(bool is_inversed);

        /**
          * Gets the mouse sensitivity.
          * @returns The mouse sensitivity.
          */
        float getMouseSensitivity() const;

        /**
          * Sets the mouse sensitivity.
          * @param sensitivity The mouse sensitivity. If the value of this parameter should be within 0 ~ 1. If the given value is out of this range, it will be clipped.
          */
        void setMouseSensitivity(float sensitivity);

    private:
        std::list<std::pair<InputManager::InputCode, QString>> mMappings;            //!< The container for the mapping of keys and functions.
        bool                                                   mIsMouseYInversed;    //!< Indicates whether the Y axis is inversed for the mouse.
        float                                                  mMouseSensitivity;    //!< The sensitivity for the mouse.
    };
}

#endif