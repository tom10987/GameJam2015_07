
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Particle.h"
#include "../Objects/Star.h"
#include <list>


namespace frameworks {
namespace scene {

class Result : public SceneBase {
public:
  Result();

  void Update() override;
  void Draw() override;

private:
  enum {
    Back = 10,
    StageClear,
    BackToTitle,
    SwitchCount,
    PlayerCount,
    Medal,
    MedalGet,
    MedalNone,

    Ochiru_kun,
    Star = 22,
  };
  std::vector<u_int> textureID;

  enum { BGM, SE, };
  std::vector<u_int> mediaID;

  const u_int gimmickCount;

  float angle;
  float medalAlpha;

  enum { ParticleLimit = 20, };
  int spawnTime;
  std::list<object::Particle> particles;
  std::list<object::ParticleStar> stars;

  void TextureSetup();
  void MediaSetup();

  void ParticleSpawn();
  void ParticleUpdate();
  void StarUpdate();

  void DispBackGround();
  void DispStageClear();
  void DispSwitchCount();
  void DispPlayerCount();
  void DispBackToTitle();
  void DispMedal(const bool);
  void DispNewton(const u_int);
};

}  // end scene
}  // end frameworks
