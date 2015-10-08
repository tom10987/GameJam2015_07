
#pragma once
#include "../Common.hpp"
#include "../Resources/Resource.h"


namespace frameworks {
namespace object {

class ParticleStar {
public:
  ParticleStar(const u_int id,
               const Vec2f& pos,
               const float scale) :
    textureID(id),
    pos(pos),
    scale(scale),
    rotate(0.0f),
    angle(Rand()() * 0.1f + 0.1f),
    alpha(0.0) {}

  void Update();
  void Draw();

  const bool IsDead() const { return alpha > M_PI; }

private:
  u_int textureID;

  Vec2f pos;
  float scale;
  float rotate;
  float angle;

  double alpha;
};

}
}
