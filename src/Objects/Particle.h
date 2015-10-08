
#pragma once
#include "../Common.hpp"
#include "../Resources/Resource.h"


namespace frameworks {
namespace object {

class Particle {
public:
  Particle(const Transform&,
           const u_int,
           const float);

  void Update();
  void Draw();

  const Vec2f& GetPos() const { return transform.pos; }

private:
  u_int textureID;
  Transform transform;

  float gravity;
};

}
}
