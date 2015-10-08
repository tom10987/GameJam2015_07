
#include "Gimmick.h"

using namespace frameworks::object;


Gimmick::Gimmick(const int direction,
                 const Vec2f& pos) :
direction(direction),
pos(pos) {
  pushState = (direction == GravityDirection::Bottom);
}


void Gimmick::Update() {
  if (alpha > 0.0f) alpha -= 0.05f;
}


void Gimmick::Draw(const std::vector<u_int>& idList,
                   const float gimmickSize) {
  const auto id = idList[pushState ? direction + 4 : direction];
  const auto texture = Asset().Find().Texture(id);

  const float offset = gimmickSize * 0.5f;
  const Vec2f drawPos = pos + (Vec2f::Ones() * offset);
  const float cutSize = 128.0f;

  if (alpha > 0.0f) {
    const float drawSize = gimmickSize * (1 - (alpha * alpha));
    drawCircle(drawPos.x(), drawPos.y(), drawSize, drawSize,
               30, 6, GetColor());
  }

  drawTextureBox(drawPos.x(), drawPos.y(),
                 gimmickSize, gimmickSize,
                 0, 0, cutSize, cutSize,
                 *texture, Color::white,
                 0, Vec2f::Ones(),
                 Vec2f::Ones() * offset);
}


void Gimmick::IconStateShift() {
  pushState = !pushState;
  if (pushState) { alpha = 1.0f; }
}


const Color Gimmick::GetColor() {
  return
    direction == GravityDirection::Bottom ? Color(1, 0, 0, alpha) :
    direction == GravityDirection::Right ? Color(0, 0, 1, alpha) :
    direction == GravityDirection::Top ? Color(1, 1, 0, alpha) :
    Color(0, 1, 0, alpha);
}
