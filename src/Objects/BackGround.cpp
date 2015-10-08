
#include "BackGround.h"

using namespace frameworks;
using namespace frameworks::object;


void BackGround::Setup(const StageID stage) {
  this->stage = stage;

  textureID.clear();
  std::vector<std::string> TextureTable;

  switch (stage) {
    default:;
    case StageID::Stage1:
      TextureTable = {
        "res/png/stage1.png",
        "res/png/stage1_fog.png",
      };
      break;

    case StageID::Stage2:
      TextureTable = {
        "res/png/stage2.png",
        "res/png/stage2_fog.png",
      };
      break;

    case StageID::Stage3:
      TextureTable = {
        "res/png/stage3.png",
        "res/png/stage3_star1.png",
        "res/png/stage3_star2.png",
        "res/png/stage3_star3.png",
        "res/png/stage3_star4.png",
      };
      break;
  }

  for (auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void BackGround::Update() {
  if (stage != StageID::Stage3) {
    texturePosX = (texturePosX < FogSize) ? texturePosX + 0.5f : 0.0f;
  }
  else {
    auto itr = stars.begin();
    while (itr != stars.end()) {
      itr->Update();
      itr->IsDead() ? itr = stars.erase(itr) : ++itr;
    }

    if (generateTime < FPS / 4) { ++generateTime; return; }
    generateTime = 0;

    if (stars.size() > StarMax) { return; }
    const float posX = Rand()(-WIDTH * 0.5f, WIDTH * 0.5f);
    const float posY = Rand()(HEIGHT * 0.25f, HEIGHT * 0.5f);
    const float size = (Rand()() + 1.0f) * 20.0f;
    stars.push_back({ textureID[Rand()(1, 4)], Vec2f(posX, posY), size });
  }
}


void BackGround::Draw() {
  const Vec2f window(WIDTH, HEIGHT);
  const Vec2f fogSize(FogSize, FogSize / 2);

  const auto back = Asset().Find().Texture(textureID[Stage]);
  drawTextureBox(-window.x() / 2, -window.y() / 2, window.x(), window.y(),
                 0, 0, window.x() / 2, window.y() / 2, *back);

  if (stage != StageID::Stage3) {
    const auto fog = Asset().Find().Texture(textureID[Fog]);
    drawTextureBox(-window.x() / 2, 0, window.x(), window.y() / 2,
                   texturePosX, 0, fogSize.x(), fogSize.y(), *fog);
  }
  else {
    for (auto& star : stars) { star.Draw(); }
  }
}
