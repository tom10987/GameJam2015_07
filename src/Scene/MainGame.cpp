
#include "MainGame.h"

using namespace frameworks;
using namespace frameworks::scene;
using namespace frameworks::object;
using namespace frameworks::utility;


MainGame::MainGame() :
  SceneBase(SceneName::Main, SceneName::Result),
  isFall(false) {
  const auto stageID = GameData::Get().GetStageID();

  Asset().Delete().All();
  GameData::Get().CountReset();

  float stageScale = 0.0f;

  player.Setup();

  back.Setup(stageID);
  prickle.Setup();

  switch (stageID) {
    default:;
    case StageID::Stage1:
      stageScale = 80.0f;

      player.Start(Vec2f(-1, -1) * stageScale, 60.0f);
      goal.Setup(Vec2f(-3.6f, -1.6f) * stageScale, stageScale * 1.5f,
                 GravityDirection::Bottom);
      break;

    case StageID::Stage2:
      stageScale = 50.0f;

      player.Start(Vec2f(-6, -3) * stageScale, 40.0f);
      goal.Setup(Vec2f(4.1f, -3) * stageScale, stageScale * 1.5f,
                 GravityDirection::Right);
      break;

    case StageID::Stage3:
      stageScale = 50.0f;

      player.Start(Vec2f(1, 1) * stageScale, 40.0f);
      goal.Setup(Vec2f(0.25f, -2.4f) * stageScale, stageScale * 1.5f,
                 GravityDirection::Top);
      break;
  }

  block.Setup(stageID, stageScale);
  gimmick.Setup(stageID, stageScale);

  MediaSetup();
  Asset().Find().Media(mediaID[stageID])->play();
}


void MainGame::Update() {
  back.Update();
  gimmick.Update();
  goal.Update();

  // ステージクリア
  if (goal.IsClear()) {
    auto& se = *Asset().Find().Media(mediaID[SeGoal]);
    if (!se.isPlaying()) { isFinish = true; }
    return;
  }

  // 重力の方向に落とす
  player.GravityUpdate();

  const auto& playerPos = player.GetTransform().pos;
  const auto& playerSize = player.GetTransform().scale;

  const auto& blockSize = block.GetBlockSize();
  const auto& gimmickSize = gimmick.GetSize();

  const auto& goalPos = goal.GetTransform().pos;
  const auto& goalSize = goal.GetTransform().scale;

  // 画面外に行ったらスタート地点に戻る
  {
    const auto window = Vec2f(WIDTH - 100, HEIGHT - 100) * 0.5f;

    if (playerPos.x() < -window.x() ||
        playerPos.x() + playerSize.x() > window.x() ||
        playerPos.y() < -window.y() ||
        playerPos.y() + playerSize.y() > window.y()) {
      const auto offset = player.GetStartPos() - playerPos;
      const auto bottom = GravityDirection::Bottom;
      player.GravityReset();
      player.Translate(offset);
      player.SetGravityDirection(bottom);
      gimmick.SwitchPush(bottom);
      Asset().Find().Media(mediaID[SeCrash])->play();
    }
  }

  // 地面に当たっているか確認
  {
    if (player.EnableMove()) { player.SetMoveState(false); }
    bool isHit = false;

    const auto blocks = block.GetBlocks();
    for (auto& blockPos : blocks) {
      isHit = IsHitRectToRect(playerPos, playerSize,
                              blockPos, blockSize);
      if (!isHit) { continue; }

      // 当たっていたら地面の上に戻す
      player.SetMoveState(true);
      player.GravityReset();
      player.Translate(GroundPos(blockPos, blockSize));
      Asset().Find().Media(mediaID[SeFall])->stop();
      isFall = false;
      break;
    }

    // 当たってなければ SE 再生
    auto& se = *Asset().Find().Media(mediaID[SeFall]);
    if (!isHit && !isFall) { se.play(); isFall = true; }
  }

  player.Update();

  // 壁に当たっているか確認
  {
    const auto blocks = block.GetBlocks();
    for (auto& blockPos : blocks) {
      const auto isHit = IsHitRectToRect(playerPos, playerSize,
                                         blockPos, blockSize);
      if (!isHit) { continue; }

      // 当たっていたら押し返す
      player.Translate(WallPos(blockPos, blockSize));
      break;
    }
  }

  // ギミック操作の判定
  {
    const auto gimmickSize = Vec2f::Ones() * gimmick.GetSize();

    for (auto& it : gimmick.GetGimmicks()) {
      const auto& gimmickPos = it.GetPos();

      const auto isHit = IsHitRectToRect(playerPos, playerSize,
                                         gimmickPos, gimmickSize);

      if (!isHit) { continue; }

      const auto isSame = player.GetDirection() == it.GetDirection();
      if (!player.IsKeyActive() || isSame) { break; }

      player.GravityReset();
      player.SetGravityDirection(it.GetDirection());
      gimmick.SwitchPush(it.GetDirection());
      Asset().Find().Media(mediaID[SeSwitch])->play();

      ++GameData::Get().GimmickCount();
      break;
    }
  }

  // ゴールに到達
  {
    const auto& goalPos = goal.GetTransform().pos;
    const auto& goalSize = goal.GetTransform().scale;

    if (IsHitRectToRect(playerPos, playerSize, goalPos, goalSize)) {
      goal.StageClear();
      Asset().Find().Media(mediaID[SeGoal])->play();
      Asset().Find().Media(mediaID[BgmStage1])->stop();
      Asset().Find().Media(mediaID[BgmStage2])->stop();
      Asset().Find().Media(mediaID[BgmStage3])->stop();
    }
  }

  // タイトルに戻る
  const auto Enter = Env().isPressKey(ENTER);
  if (Env().isPushKey('R') && Enter) {
    next = SceneName::Title;
    isFinish = true;
    Asset().Find().Media(mediaID[0])->stop();
    Asset().Find().Media(mediaID[1])->stop();
    Asset().Find().Media(mediaID[2])->stop();
  }
}


void MainGame::Draw() {
  back.Draw();
  prickle.Draw(player.GetDirection());
  block.Draw();
  gimmick.Draw();
  goal.Draw();
  player.Draw();
}


void MainGame::MediaSetup() {
  const std::string MediaTable[] = {
    "res/wav/stage1.wav",
    "res/wav/stage2.wav",
    "res/wav/stage3.wav",
    "res/wav/switch.wav",
    "res/wav/goal.wav",
    "res/wav/fall.wav",
    "res/wav/crash.wav",
  };

  // テーブルからデータを登録、関連付けされた ID を保持
  for (auto& data : MediaTable) {
    mediaID.push_back(Asset().Append().Media(data));
  }

  // 音量を一括で調整
  const float gain = 0.5f;
  for (auto& id : mediaID) { Asset().Find().Media(id)->gain(gain); }

  // BGM のみ、ループ再生を許可
  auto bgm1 = Asset().Find().Media(mediaID[0]);
  bgm1->looping(true);
  auto bgm2 = Asset().Find().Media(mediaID[1]);
  bgm2->looping(true);
  auto bgm3 = Asset().Find().Media(mediaID[2]);
  bgm3->looping(true);
}


const Vec2f MainGame::GroundPos(const Vec2f& blockPos,
                                const Vec2f& blockSize) {
  const auto gravity = player.GetDirection();
  const float offset = 0.01f;

  const auto& playerPos = player.GetTransform().pos;
  const auto& playerSize = player.GetTransform().scale;

  float temp;
  Vec2f result;

  switch (gravity) {
    default:;
    case GravityDirection::Bottom:
      temp = blockPos.y() + blockSize.y() - playerPos.y();
      result = Vec2f(0, temp + offset);
      break;

    case GravityDirection::Right:
      temp = playerPos.x() + playerSize.x() - blockPos.x();
      result = Vec2f(-temp - offset, 0);
      break;

    case GravityDirection::Top:
      temp = playerPos.y() + playerSize.y() - blockPos.y();
      result = Vec2f(0, -temp - offset);
      break;

    case GravityDirection::Left:
      temp = blockPos.x() + blockSize.x() - playerPos.x();
      result = Vec2f(temp + offset, 0);
      break;
  }

  return result;
}


const Vec2f MainGame::WallPos(const Vec2f& blockPos,
                              const Vec2f& blockSize) {
  const auto gravity = player.GetDirection();
  const float offset = 0.01f;

  const auto& playerPos = player.GetTransform().pos;
  const auto& playerSize = player.GetTransform().scale;

  bool isLeftWall;
  bool isBottomWall;
  bool isHit;
  float playerCollision;
  float blockCollision;

  float temp;
  Vec2f result;

  switch (gravity) {
    default:;
    case GravityDirection::Bottom:
    case GravityDirection::Top:
      playerCollision = playerPos.x() + playerSize.x();
      blockCollision = blockPos.x() + blockSize.x();

      isLeftWall = playerPos.x() > blockPos.x();
      isHit = isLeftWall
        ? blockCollision > playerPos.x()
        : playerCollision > blockPos.x();

      temp = isHit ?
        isLeftWall
        ? blockCollision - playerPos.x() + offset
        : blockPos.x() - playerCollision - offset
        : 0.0f;
      result = Vec2f(temp, 0);
      break;

    case GravityDirection::Right:
    case GravityDirection::Left:
      playerCollision = playerPos.y() + playerSize.y();
      blockCollision = blockPos.y() + blockSize.y();

      isBottomWall = playerPos.y() > blockPos.y();
      isHit = isBottomWall
        ? blockCollision > playerPos.y()
        : playerCollision > blockPos.y();

      temp = isHit ?
        isBottomWall
        ? blockCollision - playerPos.y() + offset
        : blockPos.y() - playerCollision - offset
        : 0.0f;
      result = Vec2f(0, temp);
      break;
  }

  return result;
}
