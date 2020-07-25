#pragma once
#include "soModule.h"

/**
* @brief keeps track of manages global data related with the game must be initialized(start up)
* and ended (shut down) manually.
*/
class GameManager final : public soModule<GameManager>
{
public: // constructors 
  GameManager(const GameManager&) = delete;
  GameManager(GameManager&&) = delete;

  ~GameManager() = default;
public: // operators

  GameManager& 
  operator=(const GameManager&) = delete;

  GameManager&
  operator=(GameManager&&) = delete;

public:// functions
	void 
  OnShutDown() override;


	int 
  OnStartUp(void* _Desc) override;

};

