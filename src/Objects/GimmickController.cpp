
#include "GimmickController.h"

using namespace frameworks;
using namespace frameworks::object;


void GimmickController::Setup(const StageID stage,
                              const float size) {
  textureID.clear();
  TextureSetup();

  gimmickSize = std::make_unique<const float>(size);

  switch (stage) {
    default:;
    case StageID::Stage1:
      gimmicks = {
        { GravityDirection::Top, Vec2f(-5, 2.5f) },
        { GravityDirection::Bottom, Vec2f(-5, -0.5f) },
        { GravityDirection::Right, Vec2f(0, -2.5f) },
        { GravityDirection::Top, Vec2f(3, -3.5f) },
        { GravityDirection::Left, Vec2f(0, 1.5f) },
      };
      break;

    case StageID::Stage2:
      gimmicks = {
        { GravityDirection::Right, Vec2f(-6.5f, -0.5f) },
        { GravityDirection::Top, Vec2f(-4.5f, -3.5f) },
        { GravityDirection::Bottom, Vec2f(-1.5f, 2.5f) },
        { GravityDirection::Bottom, Vec2f(-0.5f, -2.5f) },
        { GravityDirection::Right, Vec2f(3.5f, 4.5f) },
        { GravityDirection::Top, Vec2f(1.5f, -2.5f) },
        { GravityDirection::Left, Vec2f(6.5f, -0.5f) },
      };
      break;

    case StageID::Stage3:
      gimmicks = {
        { GravityDirection::Bottom, Vec2f(-6, 2) },
        { GravityDirection::Right, Vec2f(-10, 4) },
        { GravityDirection::Bottom, Vec2f(-4, 4) },
        { GravityDirection::Right, Vec2f(-4, -0) },
        { GravityDirection::Right, Vec2f(-9, -7) },
        { GravityDirection::Left, Vec2f(-2, -7) },
        { GravityDirection::Left, Vec2f(7, 4) },
        { GravityDirection::Left, Vec2f(0, 0) },
        { GravityDirection::Top, Vec2f(6, 0) },
        { GravityDirection::Right, Vec2f(6, -4) },
        { GravityDirection::Bottom, Vec2f(5, 2) },
        { GravityDirection::Top, Vec2f(6, -7) },
      };
      break;
  }

  // サイズを座標に反映
  for (auto& gimmick : gimmicks) { gimmick.OffsetScaleToPos(size); }
}


void GimmickController::Update() {
  for (auto& gimmick : gimmicks) { gimmick.Update(); }
}


void GimmickController::Draw() {
  for (auto& gimmick : gimmicks) {
    gimmick.Draw(textureID, *gimmickSize);
  }
}


// 押されたスイッチの向きを受け取り、スイッチの状態を切り替える
void GimmickController::SwitchPush(const int direction) {
  for (auto& gimmick : gimmicks) {
    const auto nowDirection = gimmick.GetDirection();
    const auto nowIconState = gimmick.IsPushed();

    // 押したスイッチと押されていたスイッチ以外は変更しない
    if (nowDirection != direction && !nowIconState) continue;

    // 同じスイッチを押したときも変更しない
    if (nowDirection == direction && nowIconState) return;

    gimmick.IconStateShift();
  }
}


void GimmickController::TextureSetup() {
  const std::string TextureTable[] = {
    "res/png/button_A.png",    // [0]赤スイッチ
    "res/png/button_D.png",    // [1]青スイッチ
    "res/png/button_B.png",    // [2]黄色スイッチ
    "res/png/button_C.png",    // [3]緑スイッチ
    "res/png/button_Ap.png",   // [4]赤押した
    "res/png/button_Dp.png",   // [5]青押した
    "res/png/button_Bp.png",   // [6]黄色押した
    "res/png/button_Cp.png",   // [7]緑押した
  };

  for (auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}
