
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Particle.h"
#include <list>


namespace frameworks {
namespace scene {

class Title : public SceneBase {
public:
  Title();

  void Update() override;
  void Draw() override;

private:
  enum { ParticleMax = 10, };

  // 数字以外の画像 ID の一覧
  enum TextureID {
    Back = 10,
    Logo,
    Icon1,
    Icon2,
    Icon3,
    Cursor,
    Control,

    Red,
    Blue,
    Green,
    Yellow,
  };
  std::vector<u_int> textureID;
  std::vector<u_int> icons;

  enum MediaID {
    BGM,
    Start,
    Select,
  };
  std::vector<u_int> mediaID;

  u_int select;
  float angle;

  std::list<object::Particle> particles;
  int generateTime;

  void ParticleUpdate();

  void TextureSetup();
  void MediaSetup();
};

}  // end scene
}  // end frameworks
