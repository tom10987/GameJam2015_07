
#include "Prickle.h"

using namespace frameworks::object;


void Prickle::Setup() {
  textureID.clear();

  const std::string TextureTable[] = {
    "res/png/prickle_h.png",
    "res/png/prickle_v.png",
  };

  for (const auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void Prickle::Draw(const int direction) {
  const Vec2f sizeH(WIDTH, 64);
  const Vec2f sizeV(64, HEIGHT);
  const Vec2f window(WIDTH, HEIGHT);

  // â∫
  {
    const auto texture = Asset().Find().Texture(textureID[Horizontal]);
    const auto color = direction == GravityDirection::Bottom ?
      GetColor(direction) : Color::gray;

    drawTextureBox(-window.x() / 2, -window.y() / 2,
                   sizeH.x(), sizeH.y(),
                   0, 0, sizeH.x(), sizeH.y(),
                   *texture, color);
  }

  // âE
  {
    const auto texture = Asset().Find().Texture(textureID[Vertical]);
    const auto color = direction == GravityDirection::Right ?
      GetColor(direction) : Color::gray;

    drawTextureBox(window.x() / 2 - sizeV.x(), -window.y() / 2,
                   sizeV.x(), sizeV.y(),
                   sizeV.x(), 0, -sizeV.x(), sizeV.y(),
                   *texture, color);
  }

  // è„
  {
    const auto texture = Asset().Find().Texture(textureID[Horizontal]);
    const auto color = direction == GravityDirection::Top ?
      GetColor(direction) : Color::gray;

    drawTextureBox(-window.x() / 2, window.y() / 2 - sizeH.y(),
                   sizeH.x(), sizeH.y(),
                   0, sizeH.y(), sizeH.x(), -sizeH.y(),
                   *texture, color);
  }

  // ç∂
  {
    const auto texture = Asset().Find().Texture(textureID[Vertical]);
    const auto color = direction == GravityDirection::Left ?
      GetColor(direction) : Color::gray;

    drawTextureBox(-window.x() / 2, -window.y() / 2,
                   sizeV.x(), sizeV.y(),
                   0, 0, sizeV.x(), sizeV.y(),
                   *texture, color);
  }
}


const Color Prickle::GetColor(const int direction) {
  return
    direction == GravityDirection::Bottom ? Color::red :
    direction == GravityDirection::Right ? Color::blue :
    direction == GravityDirection::Top ? Color::yellow :
    Color::green;
}
