
#include "Star.h"

using namespace frameworks;
using namespace frameworks::object;


void ParticleStar::Update() {
  rotate += angle;
  alpha += M_PI / (FPS * 2);
}


void ParticleStar::Draw() {
  const auto texture = Asset().Find().Texture(textureID);
  const float Size = 256.0f;

  drawTextureBox(pos.x(), pos.y(), 1, 1,
                 0, 0, Size, Size,
                 *texture,
                 Color(1, 1, 1, std::sin(alpha)),
                 rotate,
                 Vec2f::Ones() * scale,
                 Vec2f::Ones() * 0.5f);
}
