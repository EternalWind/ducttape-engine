
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#ifndef DUCTTAPE_ENGINE_COMPONENT_SOUNDCOMPONENT
#define DUCTTAPE_ENGINE_COMPONENT_SOUNDCOMPONENT

#include <Config.hpp>

#include <Scene/Component.hpp>

#include <QString>

#include <SFML/Audio/Sound.hpp>

#include <memory>

namespace dt {

/**
  * Component for managing sounds in 3D enviroment.
  * @todo Positions should be calculated relatively to position of player, but there is no method to get those now.
  */
class DUCTTAPE_API SoundComponent : public Component {
    Q_OBJECT
public:
    DT_SERIALIZABLE(SoundComponent)
    /**
     * Advanced constructor.
     * @param sound_file The name of the sound resource to play.
     * @param name The name for this Component.
     * @see Component
     */
    SoundComponent(const QString sound_file_name = "", const QString name = "");

    void onInitialize();
    void onDeinitialize();
    void onUpdate(double time_diff);
    void onSerialize(IOPacket& packet);

    /**
     * Plays the sound located in mSound.
     * @param sound_file The name of the sound file to play. To get sound in 3D, the format should be mono.
     */
    void setSoundFileName(const QString sound_file_name);

    /**
     * Returns the name of the sound file.
     * @returns The name of the found file.
     */
    const QString getSoundFileName() const;

    /**
     * Returns the sf::Sound object for default action access.
     * @returns The sf::Sound object.
     */
    sf::Sound& getSound();

public slots:
    /**
     * Tries to play / continue sound located in mSound.
     * @warning The sound will not be played if the component is diabled.
     */
    void playSound();

    /**
     * Pauses the sound if playing.
     */
    void pauseSound();

    /**
     * Stops the sound if playing.
     */
    void stopSound();

    /**
      * Sets the sound volume.
      * @param volume The sound volume. Minimum: 0. Maximum: 100. Default: 100.
      */
    void setVolume(float volume);

    /**
      * Sets the global master sound/music volume.
      * @param volume The global master sound/music volume. Minimum: 0. Maximum: 100. Default: 100.
      */
    void setMasterVolume(float volume);

signals:
    void volumeChanged(float new_volume);
    void masterVolumeChanged(float new_volume);
    void soundPlayed();
    void soundStopped();
    void soundPaused();

private:
    /**
     * Private method. Tries to load sound to buffer and then from buffer to mSound.
     */
    void _loadSound();

    QString mSoundFileName; //!< Name of sound file loaded in component.
    sf::Sound mSound;       //!< SFML Sound. It is set during _LoadSound().

};

}

#endif
