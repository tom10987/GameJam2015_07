
#pragma once
#include "Common.hpp"
#include "Scene/SceneManager.h"


namespace frameworks {

class GamePlayer {
public:
  GamePlayer(const scene::SceneName scene) : manager(scene) {}

  void Update() {
    manager.Update();
  }

  void Draw() {
    Env().begin();
    manager.Draw();
    Env().end();
  }

  const bool IsRunning() {
    return Env().isOpen() && !Env().isPushKey(ESCAPE);
  }

private:
  SceneManager manager;
};

}  // end frameworks
