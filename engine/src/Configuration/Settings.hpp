
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_SETTINGS
#define DUCTTAPE_ENGINE_SETTINGS

#include <Config.hpp>

#include <QtXml/QtXml>
#include <QString>

namespace dt {
    /**
      * The base class for all the settings. If you want to write your own settings class, you should inherit from this class.
      */
    class DUCTTAPE_API Settings {
    public:
        /**
          * Gets the name of this settings.
          * @returns The name of this settings.
          */
        virtual QString getName() const = 0;

        /**
          * Saves the content of this settings to a given XML document.
          * @param doc The given XML document.
          */
        void toXML(QDomDocument& doc) const;

        /**
          * Loads the content of this settings from a given XML document.
          * @param doc The given XML document.
          */
        void fromXML(const QDomDocument& doc);

    protected:
        /**
          * Called when this settings is being saved to an XML document.
          * @param doc The XML document object.
          * @param parent The parent XML element with the name of this settings.
          */
        virtual void _onToXML(QDomDocument& doc, QDomElement& parent) const = 0;

        /**
          * Called when this settings is being loaded from an XML document.
          * @param doc The XML document object.
          * @param parent The parent XML element with the name of this settings. If this node doesn't exist, the value of this parameter will be null. You should call isNull before your other calls.
          */
        virtual void _onFromXML(const QDomDocument& doc, const QDomElement& parent) = 0;
    };
}

#endif