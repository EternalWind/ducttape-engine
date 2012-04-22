
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_DISPLAYSETTINGS
#define DUCTTAPE_ENGINE_DISPLAYSETTINGS

#include <Config.hpp>

#include <Configuration/Settings.hpp>

#include <cstdint>

namespace dt {
    /**
      * A class to hold the display settings.
      */
    class DisplaySettings : public Settings {
    public:
        /**
          * A structure to hold the width and the height for a resolution.
          */
        struct Resolution {
            uint16_t width;
            uint16_t height;
        };

        /**
          * The quality level.
          */
        enum QualityLevel {
            NONE,
            LOW,
            MEDIUM,
            HIGH,
            ULTRA
        };

        /**
          * The anti-aliasing level.
          */
        enum AntiAliasingLevel {
            NONE,
            X2,
            X4,
            X8,
            X16
        };

        /**
          * The constructor.
          */
        DisplaySettings();

        /**
          * Gets the name of this settings.
          * @returns The name of this settings. It's "Display" for the DisplaySettings.
          * @see Settings
          */
        QString getName() const;

        /**
          * Sets the resolution
          * @param width The width of the resolution.
          * @param height The height of the resolution.
          */
        void setResolution(uint16_t width, uint16_t height);

        /**
          * Sets the resolution.
          * @param resolution The resolution to set.
          */
        void setResolution(Resolution resolution);

        /**
          * Gets the resolution.
          * @returns The resolution.
          */
        Resolution getResolution() const;

        /**
          * Sets the refresh rate.
          * @param refresh_rate The refresh rate to set.
          */
        void setRefreshRate(uint8_t refresh_rate);

        /**
          * Gets the refresh rate.
          * @returns The refresh rate.
          */
        uint8_t getRefreshRate() const;

        /**
          * Sets the general quality level.
          * @param level The quality level for the general quality.
          */
        void setGeneralQuality(QualityLevel level);

        /**
          * Gets the general quality level.
          * @returns The general quality level.
          */
        QualityLevel getGeneralQuality() const;

        /**
          * Sets the AA level.
          * @param level The AA level to set.
          */
        void setAntiAliasingLevel(AntiAliasingLevel level);

        /**
          * Gets the AA level.
          * @returns The AA level.
          */
        AntiAliasingLevel getAntiAliasingLevel() const;

    protected:
        /**
          * Called when this settings is being saved to an XML document.
          * @param doc The XML document object.
          * @param parent The parent XML element with the name of this settings. All your sub-nodes should be attached to this node.
          * @see Settings
          */
        void _onToXML(QDomDocument& doc, QDomElement& parent) const;

        /**
          * Called when this settings is being loaded from an XML document.
          * @param doc The XML document object.
          * @param parent The parent XML element with the name of this settings. If this node doesn't exist, the value of this parameter will be null. You should call isNull before your other calls.
          * @see Settings
          */
        void _onFromXML(const QDomDocument& doc, const QDomElement& parent);

    public:
        static const QString NAME;                                   //!< The name of the DisplaySettings.

    private:
        Resolution mResolution;                                      //!< The resolution.
        uint8_t mRefreshRate;                                        //!< The refresh rate.
        QualityLevel mGeneralQuality;                                //!< The general quality.
        AntiAliasingLevel mAntiAliasingLevel;                        //!< The AA level.
    };
}

#endif