
#include "Particle.h"

using namespace frameworks;
using namespace frameworks::object;


Particle::Particle(const Transform& transform,
                   const u_int textureID,
                   const float gravity) :
transform(transform),
textureID(textureID),
gravity(gravity) {
}


void Particle::Update() {
  transform.pos.y() -= gravity;
  transform.rotate += transform.angle;
}


void Particle::Draw() {
  const float Size = 512.0f;
  const auto texture = Asset().Find().Texture(textureID);
  drawTextureBox(transform.pos.x(), transform.pos.y(),
                 transform.scale.x(), transform.scale.y(),
                 0, 0, Size, Size,
                 *texture, Color::white,
                 transform.rotate,
                 Vec2f::Ones(),
                 transform.scale * 0.5f);
}
