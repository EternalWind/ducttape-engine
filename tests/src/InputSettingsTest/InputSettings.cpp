
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include "InputSettingsTest/InputSettings.hpp"

#include <Utils/Logger.hpp>

namespace InputSettingsTest {

    bool InputSettingsTest::run(int argc, char** argv) {
        dt::InputSettings input_settings;
        QString name = "TestFunction";

        dt::Logger::get().info("Checking for adding a function...");

        if(!input_settings.addFunction(name)) {
            dt::Logger::get().error("Failed to add a function.");

            return false;
        }

        dt::Logger::get().info("Checking for adding a duplicate function...");

        if(input_settings.addFunction(name)) {
            dt::Logger::get().error("Duplicate function has been added.");

            return false;
        }

        dt::Logger::get().info("Checking for function mapping...");

        if(!input_settings.setKey(name, dt::InputManager::KC_0)) {
            dt::Logger::get().error("Failed to find an existing function.");

            return false;
        }
        if(input_settings.getByFunction(name)->first != dt::InputManager::KC_0 || input_settings.getByKey(dt::InputManager::KC_0)->second != name) {
            dt::Logger::get().error("Failed to map a key to a function.");

            return false;
        }

        input_settings.setKey(name, dt::InputManager::NONE);
        if(input_settings.getByKey(dt::InputManager::NONE) != input_settings.end()) {
            dt::Logger::get().error("Got a function mapping with an invalid input code.");

            return false;
        }

        if(input_settings.isMapped(dt::InputManager::KC_0) && input_settings.isMapped(dt::InputManager::NONE)) {
            dt::Logger::get().error("Detected a not mapped input code or an invalid input code mapped.");

            return false;
        }

        if(!input_settings.removeFunction(name) || input_settings.removeFunction(name)) {
            dt::Logger::get().error("Failed to remove a function.");

            return false;
        }

        return true;
    }

    QString InputSettingsTest::getTestName() {
        return "InputSettings";
    }
}