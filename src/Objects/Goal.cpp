
#include "Goal.h"

using namespace frameworks::object;


void Goal::Setup(const Vec2f& pos,
                 const float size,
                 const int direction) {
  this->transform = {
    pos, Vec2f::Ones() * size, direction * (M_PI / 2), 0.0f
  };

  const std::string GoalTable[] = {
    "res/png/newton1.png",
    "res/png/newton2.png",
  };

  for (auto& data : GoalTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void Goal::Update() {
  transform.angle = (transform.angle < M_PI) ?
    transform.angle + 0.05f : 0.0f;
}


void Goal::Draw() {
  const auto id = textureID[isClear ? Clear : Play];
  const auto texture = Asset().Find().Texture(id);

  const auto offset = transform.scale * 0.5f;
  const auto pos = transform.pos + offset;
  const float cutSize = 512.0f;
  const float scale = std::abs(std::sin(transform.angle)) * 0.1f;

  drawTextureBox(pos.x(), pos.y(),
                 transform.scale.x(), transform.scale.y(),
                 0, 0, cutSize, cutSize,
                 *texture, Color::white,
                 transform.rotate,
                 Vec2f::Ones() * (1.0f + scale),
                 offset);
}
