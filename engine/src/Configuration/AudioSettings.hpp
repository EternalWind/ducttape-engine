
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_AUDIOSETTINGS
#define DUCTTAPE_ENGINE_AUDIOSETTINGS

#include <Config.hpp>

#include <Configuration/Settings.hpp>

namespace dt {
    /**
      * A class to hold the audio settings.
      */
    class DUCTTAPE_API AudioSettings : public Settings {
    public:
        /**
          * The constructor.
          */
        AudioSettings();

        /**
          * Gets the name of this settings.
          * @returns The name of this settings. It's "Audio" for the AudioSettings.
          * @see Settings
          */
        QString getName() const;

        /**
          * Sets the master volume.
          * @param master_volume The master volume to set which should between 0 to 100. It will be clipped if it is out of this range.
          */
        void setMasterVolume(float master_volume);

        /**
          * Gets the master volume.
          * @returns The master volume.
          */
        float getMasterVolume() const;

        /**
          * Sets the volume for music.
          * @param music_volume The volume for music to set which should between 0 to 100. It will be clipped if it is out of this range.
          */
        void setMusicVolume(float music_volume);

        /**
          * Gets the volume for music.
          * @returns The volume for music.
          */
        float getMusicVolume() const;

        /**
          * Sets the volume for sound.
          * @param sound_volume The volume for sound to set which should between 0 to 100. It will be clipped if it is out of this range.
          */
        void setSoundVolume(float sound_volume);

        /**
          * Gets the volume for sound.
          * @returns The volume for sound.
          */
        float getSoundVolume() const;

    protected:
        /**
          * Clip the volume so that it's within the range between 0 to 100.
          * @param volume The volume to clip.
          */
        void _clipVolume(float& volume);

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
        static const QString NAME;                                                   //!< The name of the AudioSettings.


    private:
        float mMasterVolume;             //!< The master volume.
        float mMusicVolume;              //!< The volume for music.
        float mSoundVolume;              //!< The volume for sound.
    };
}

#endif