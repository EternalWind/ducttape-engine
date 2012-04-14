
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Configuration/InputSettings.hpp>

#include <Utils/Logger.hpp>

namespace dt {
    InputSettings::InputSettings() :
          mMappings(),
          mIsMouseYInversed(false),
          mMouseSensitivity(1.0f) {}

    bool InputSettings::setKey(QString function, InputManager::InputCode key) {
        auto orig_pair = this->getByFunction(function);

        // Check if the function has been added.
        if(orig_pair != mMappings.end()) {
            // No need to map the same key to a function.
            if(orig_pair->first == key) {
                return true;
            }

            auto conflict_pair = this->getByKey(key);

            // Check if the key has been mapped.
            if(conflict_pair != mMappings.end()) {
                // Remove the old mapping.
                conflict_pair->first = InputManager::NONE;
            }

            // Map the new key to the given function.
            orig_pair->first = key;

            return true;
        }
        else {
            return false;
        }
    }

    bool InputSettings::addFunction(QString function, InputManager::InputCode key) {
        // Check if the function has been added.
        auto orig_pair = this->getByFunction(function);
        if(orig_pair != mMappings.end()) {
            return false;
        }

        // Check if this key has been mapped to another function.
        auto conflict_pair = this->getByKey(key);
        if(conflict_pair != mMappings.end()) {
            conflict_pair->first = InputManager::NONE;
        }

        mMappings.push_back(std::pair<InputManager::InputCode, QString>(key, function));

        return true;
    }

    bool InputSettings::removeFunction(QString function) {
        // Check if this function has been added or not.
        auto orig_pair = this->getByFunction(function);
        if(orig_pair == mMappings.end()) {
            return false;
        }

        mMappings.erase(orig_pair);

        return true;
    }

    InputSettings::InputMapping InputSettings::getByFunction(QString function) {
        InputMapping iter;

        for(iter = mMappings.begin() ; iter != mMappings.end() ; ++iter) {
            if(iter->second == function) {
                break;
            }
        }

        return iter;
    }

    InputSettings::InputMapping InputSettings::getByKey(InputManager::InputCode key) {
        InputMapping iter;

        // If the given key is invalid, return the past-the-end iterator of the key-function mapping.
        if(key == InputManager::NONE) {
            return mMappings.end();
        }

        for(iter = mMappings.begin() ; iter != mMappings.end() ; ++iter) {
            if(iter->first == key) {
                break;
            }
        }

        return iter;
    }

    InputSettings::InputMapping InputSettings::begin() {
        return mMappings.begin();
    }

    InputSettings::InputMapping InputSettings::end() {
        return mMappings.end();
    }

    bool InputSettings::isMapped(InputManager::InputCode key) {
        auto iter = getByKey(key);

        return iter != mMappings.end();
    }
}