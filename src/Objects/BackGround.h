
#pragma once
#include "Object.hpp"
#include "Star.h"
#include <list>


namespace frameworks {
namespace object {

class BackGround {
public:
  BackGround() : texturePosX(0.0f), generateTime(0) {}

  void Setup(const StageID);

  void Update();
  void Draw();

private:
  enum { Stage, Fog, };
  enum { FogSize = 1024, };
  std::vector<u_int> textureID;
  float texturePosX;

  StageID stage;

  enum { StarMax = 30, };
  std::list<ParticleStar> stars;
  int generateTime;
};

}
}
