
#pragma once
#include "SceneBase.hpp"
#include "../Objects/Player.h"
#include "../Objects/BackGround.h"
#include "../Objects/Block.h"
#include "../Objects/GimmickController.h"
#include "../Objects/Goal.h"
#include "../Objects/Prickle.h"


namespace frameworks {
namespace scene {

class MainGame : public SceneBase {
public:
  MainGame();

  void Update() override;
  void Draw() override;

private:
	object::Player player;

  object::BackGround back;
  object::Block block;
  object::GimmickController gimmick;
  object::Goal goal;
  object::Prickle prickle;

  enum {
    BgmStage1,
    BgmStage2,
    BgmStage3,
    SeSwitch,
    SeGoal,
    SeFall,
    SeCrash,
  };
  std::vector<u_int> mediaID;
  bool isFall;
  void MediaSetup();

  const Vec2f GroundPos(const Vec2f&, const Vec2f&);
  const Vec2f WallPos(const Vec2f&, const Vec2f&);
};

}  // end scene
}  // end frameworks
