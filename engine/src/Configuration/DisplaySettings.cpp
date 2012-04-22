
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Configuration/DisplaySettings.hpp>
#include <Utils/Utils.hpp>

namespace dt {
    const QString DisplaySettings::NAME("Display");

    DisplaySettings::DisplaySettings() :
        mRefreshRate(60),
        mGeneralQuality(MEDIUM),
        mAntiAliasingLevel(NONE) {
            mResolution.width = 1024;
            mResolution.height = 768;
        }

    QString DisplaySettings::getName() const {
        return NAME;
    }

    void DisplaySettings::setResolution(uint16_t width, uint16_t height) {
        mResolution.width = width;
        mResolution.height = height;
    }

    void DisplaySettings::setResolution(Resolution resolution) {
        mResolution = resolution;
    }

    DisplaySettings::Resolution DisplaySettings::getResolution() const {
        return mResolution;
    }

    void DisplaySettings::setRefreshRate(uint8_t refresh_rate) {
        mRefreshRate = refresh_rate;
    }

    uint8_t DisplaySettings::getRefreshRate() const {
        return mRefreshRate;
    }

    void DisplaySettings::setGeneralQuality(QualityLevel level) {
        mGeneralQuality = level;
    }

    DisplaySettings::QualityLevel DisplaySettings::getGeneralQuality() const {
        return mGeneralQuality;
    }

    void DisplaySettings::setAntiAliasingLevel(AntiAliasingLevel level) {
        mAntiAliasingLevel = level;
    }

    DisplaySettings::AntiAliasingLevel DisplaySettings::getAntiAliasingLevel() const {
        return mAntiAliasingLevel;
    }

    void DisplaySettings::_onToXML(QDomDocument& doc, QDomElement& parent) const {
        QDomElement resolution = doc.createElement("Resolution");
        QDomElement width = doc.createElement("Width");
        QDomElement height = doc.createElement("Height");
        QDomElement refresh_rate = doc.createElement("Refresh_Rate");
        QDomElement general_quality = doc.createElement("General_Quality_Level");
        QDomElement anti_aliasing = doc.createElement("Anti-Aliasing_Level");

        width.setNodeValue(Utils::toString(mResolution.width));
        height.setNodeValue(Utils::toString(mResolution.height));
        refresh_rate.setNodeValue(Utils::toString(mRefreshRate));
        general_quality.setNodeValue(Utils::toString(mGeneralQuality));
        anti_aliasing.setNodeValue(Utils::toString(mAntiAliasingLevel));

        resolution.appendChild(width);
        resolution.appendChild(height);

        parent.appendChild(resolution);
        parent.appendChild(refresh_rate);
        parent.appendChild(general_quality);
        parent.appendChild(anti_aliasing);
    }

    void DisplaySettings::_onFromXML(const QDomDocument& doc, const QDomElement& parent) {
        if(!parent.isNull()) {
            for(auto iter = parent.firstChildElement() ; !iter.isNull() ; iter = iter.nextSibling()) {
                if(iter.nodeName() == "Resolution") {
                    mResolution.width = iter.firstChildElement("Width").nodeValue().toUShort();
                    mResolution.height = iter.firstChildElement("Height").nodeValue().toUShort();
                }
                else if(iter.nodeName() == "Refresh_Rate") {
                    mRefreshRate = (uint8_t)iter.nodeValue().toUShort();
                }
                else if(iter.nodeName() == "General_Quality_Level") {
                    mGeneralQuality = (QualityLevel)iter.nodeValue().toInt();
                }
                else if(iter.nodeName() == "Anti-Aliasing_Level") {
                    mAntiAliasingLevel = (AntiAliasingLevel)iter.nodeValue().toInt();
                }
            }
        }
    }
}