#pragma once
#include "UiManager.h"
#include "StateScoreBase.h"
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

  LapCount m_currentLapCount;


  std::vector<StateScoreBase *> m_states;

};

