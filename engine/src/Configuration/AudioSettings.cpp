
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <Configuration/AudioSettings.hpp>
#include <Utils/Utils.hpp>

namespace dt {
    const QString AudioSettings::NAME("Audio");

    AudioSettings::AudioSettings() : 
        mMasterVolume(0.0f),
        mMusicVolume(0.0f),
        mSoundVolume(0.0f) {}

    QString AudioSettings::getName() const {
        return NAME;
    }

    void AudioSettings::setMasterVolume(float master_volume) {
        _clipVolume(master_volume);
        mMasterVolume = master_volume;
    }

    float AudioSettings::getMasterVolume() const {
        return mMasterVolume;
    }

    void AudioSettings::setMusicVolume(float music_volume) {
        _clipVolume(music_volume);
        mMusicVolume = music_volume;
    }

    float AudioSettings::getMusicVolume() const {
        return mMusicVolume;
    }

    void AudioSettings::setSoundVolume(float sound_volume) {
        _clipVolume(sound_volume);
        mSoundVolume = sound_volume;
    }

    float AudioSettings::getSoundVolume() const {
        return mSoundVolume;
    }

    void AudioSettings::_clipVolume(float& volume) {
        if(volume > 100.0f) {
            volume = 100.0f;
        }
        else if(volume < 0.0f) {
            volume = 0.0f;
        }
    }

    void AudioSettings::_onToXML(QDomDocument& doc, QDomElement& parent) const {
        QDomElement master_volume = doc.createElement("Master_Volume");
        QDomElement music_volume = doc.createElement("Music_Volume");
        QDomElement sound_volume = doc.createElement("Sound_Volume");

        master_volume.setNodeValue(Utils::toString(mMasterVolume));
        music_volume.setNodeValue(Utils::toString(mMusicVolume));
        sound_volume.setNodeValue(Utils::toString(mSoundVolume));

        parent.appendChild(master_volume);
        parent.appendChild(music_volume);
        parent.appendChild(sound_volume);
    }

    void AudioSettings::_onFromXML(const QDomDocument& doc, const QDomElement& parent) {
        if(!parent.isNull()) {
            for(auto iter = parent.firstChildElement() ; !iter.isNull() ; iter = iter.nextSibling()) {
                if(iter.nodeName() == "Master_Volume") {
                    mMasterVolume = iter.nodeValue().toFloat();
                }
                else if(iter.nodeName() == "Music_Volume") {
                    mMusicVolume = iter.nodeValue().toFloat();
                }
                else if(iter.nodeName() == "Sound_Volume") {
                    mSoundVolume = iter.nodeValue().toFloat();
                }
            }
        }
    }
}