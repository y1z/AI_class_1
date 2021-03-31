#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <filesystem>

/**
 * Class used for playing sound.
 */
class SoundPlayer
{
 public:
  SoundPlayer();

  /**
   * Set the volume for the sound
   */
  void
  setVolume(const float newVolume);

  /**
   * Loads the a sound file.
   */
  bool
  loadSoundFile(const std::filesystem::path& soundFilePath);

  /**
   * Plays the sound
   */
  void
  playSound(const bool loopSound = false);


 private:
  sf::Sound m_sound;
  sf::SoundBuffer m_buffer;
};

