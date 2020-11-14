#pragma once
#include "UiManager.h"
#include  "StateScoreCheck.h"
#include "Types.h"


class FSMScoreBord {
public:
  FSMScoreBord();
  ~FSMScoreBord();
public:

  void
  init(UiManager& UI);


  int
  run(UiManager& UI);
public:

  StateScoreBase * m_currentState = nullptr;

  UiManager *ptr_man = nullptr;

  LapCount m_lapCount;

  std::vector<sf::Vector2f> m_positions;


  std::vector<StateScoreBase *> m_states;

};

