
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Configuration/Settings.hpp>

namespace dt {
    void Settings::toXML(QDomDocument& doc) const {
        auto element = doc.createElement(getName());

        _onToXML(doc, element);
        doc.appendChild(element);
    }

    void Settings::fromXML(const QDomDocument& doc) {
        auto element = doc.firstChildElement(getName());

        _onFromXML(doc, element);
    }
}