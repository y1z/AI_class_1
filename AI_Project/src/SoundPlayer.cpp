#include "SoundPlayer.h"
#include <iostream>

namespace fs = std::filesystem;

void
SoundPlayer::setVolume(const float newVolume) {
  m_sound.setVolume(newVolume);
}

bool
SoundPlayer::loadSoundFile(const std::filesystem::path& soundFilePath) {
  const bool canLoadFile = m_buffer.loadFromFile(soundFilePath.generic_string());

  if (!canLoadFile) {
    std::wcerr << "cannot load from file" << soundFilePath << '\n';
  }

  return canLoadFile;
}

void
SoundPlayer::playSound(const bool loopSound) {
  m_sound.setLoop(loopSound);
  m_sound.play();
}

