
#include "Result.h"

using namespace frameworks;
using namespace frameworks::scene;
using namespace frameworks::object;


Result::Result() :
  SceneBase(SceneName::Result, SceneName::Title),
  gimmickCount(GameData::Get().GimmickCount()),
  angle(0.0f),
  medalAlpha(0.0f),
  spawnTime(0) {

  Asset().Delete().All();

  TextureSetup();
  MediaSetup();

  auto bgm = Asset().Find().Media(mediaID[BGM]);
  bgm->looping(true);
  bgm->play();
}


void Result::Update() {
  if (Env().isPushKey(SPACE)) {
    isFinish = true;
    Asset().Find().Media(mediaID[BGM])->stop();
    Asset().Find().Media(mediaID[SE])->play();
  }

  ParticleUpdate();
  StarUpdate();

  ParticleSpawn();
}


void Result::Draw() {
  DispBackGround();

  // 落ちるくんパーティクル
  for (auto& particle : particles) { particle.Draw(); }

  DispStageClear();
  DispSwitchCount();
  DispPlayerCount();
  DispBackToTitle();

  const auto& stageID = GameData::Get().GetStageID();
  const auto& medalNum = GameData::Get().GetMedalNum()[stageID];
  const bool isMedal = GameData::Get().GimmickCount() <= medalNum;

  DispMedal(isMedal);
  DispNewton(textureID[isMedal ? MedalGet : MedalNone]);

  // メダル用パーティクル
  for (auto& star : stars) { star.Draw(); }
}


void Result::TextureSetup() {
  const std::string TextureTable[] = {
    "res/png/result_0.png",
    "res/png/result_1.png",
    "res/png/result_2.png",
    "res/png/result_3.png",
    "res/png/result_4.png",
    "res/png/result_5.png",
    "res/png/result_6.png",
    "res/png/result_7.png",
    "res/png/result_8.png",
    "res/png/result_9.png",

    "res/png/result_back.png",         // [10]背景
    "res/png/result_clear.png",        // [11]「ステージクリア！」
    "res/png/result_button.png",       // [12]「タイトルに戻る」
    "res/png/result_switch.png",       // [13]「スイッチの回数」
    "res/png/result_count.png",        // [14]「かい」

    "res/png/result_medal.png",        // [15]メダル
    "res/png/result_medal_get.png",    // [16]メダルあり
    "res/png/result_medal_none.png",   // [17]メダルなし

    "res/png/ochirukun_red.png",       // [18]
    "res/png/ochirukun_blue.png",
    "res/png/ochirukun_green.png",
    "res/png/ochirukun_yellow.png",

    "res/png/stage3_star1.png",        // [22]
    "res/png/stage3_star2.png",
    "res/png/stage3_star3.png",
    "res/png/stage3_star4.png",
  };

  for (const auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void Result::MediaSetup() {
  const std::string MediaTable[] = {
    "res/wav/result.wav",
    "res/wav/start.wav",
  };

  for (const auto& data : MediaTable) {
    mediaID.push_back(Asset().Append().Media(data));
  }

  // 音量を一括で調整
  const float gain = 0.5f;
  for (const auto& id : mediaID) {
    Asset().Find().Media(id)->gain(gain);
  }
}


void Result::ParticleSpawn() {
  spawnTime = spawnTime < FPS ? spawnTime + 1 : 0;
  if (spawnTime % (FPS / 2) != 0) { return; }

  // 落ちるくん追加
  if (particles.size() < ParticleLimit) {
    const Vec2f pos = Vec2f((-WIDTH / 2) + (WIDTH * Rand()()), HEIGHT / 2);
    const Vec2f scale = Vec2f::Ones() * Rand()(30.0f, 80.0f);
    const float speed = Rand()(-1.0f, 1.0f) * 0.2f;
    const float gravity = Rand()() + 1.0f;
    const auto id = textureID[Ochiru_kun + Rand()(4)];
    particles.push_back(Particle({ pos, scale, 0.0f, speed }, id, gravity));
  }

  // メダル獲得してるか確認
  {
    const auto stageID = GameData::Get().GetStageID();
    const auto currentCount = GameData::Get().GimmickCount();
    const auto medalCriteria = GameData::Get().GetMedalNum()[stageID];
    const bool isMedal = currentCount <= medalCriteria;
    if (!isMedal) { return; }
  }

  // メダル用パーティクル追加
  if (stars.size() < ParticleLimit) {
    const auto id = textureID[Star + Rand()(4)];
    const float range = 100.0f;
    const float posX = 50.0f + Rand()(-range, range);
    const float posY = Rand()(-range, range);
    const float size = (Rand()() + 1.0f) * 20.0f;
    stars.push_back(ParticleStar(id, Vec2f(posX, posY), size));
  }
}


void Result::ParticleUpdate() {
  auto itr = particles.begin();
  while (itr != particles.end()) {
    itr->Update();

    const auto isDead = itr->GetPos().y() < -HEIGHT / 2 - 40;
    isDead ? itr = particles.erase(itr) : ++itr;
  }
}


void Result::StarUpdate() {
  auto itr = stars.begin();
  while (itr != stars.end()) {
    itr->Update();
    itr->IsDead() ? itr = stars.erase(itr) : ++itr;
  }
}


void Result::DispBackGround() {
  const Vec2f window(WIDTH, HEIGHT);
  const auto& texture = *Asset().Find().Texture(textureID[Back]);
  drawTextureBox(-window.x() / 2, -window.y() / 2,
                 window.x(), window.y(),
                 0, 0, window.x(), window.y(), texture);
}


void Result::DispStageClear() {
  const Vec2f window(WIDTH, HEIGHT);
  const auto& texture = *Asset().Find().Texture(textureID[StageClear]);
  const Vec2f size(1024, 512);
  drawTextureBox(-window.x() / 2, window.y() / 2 - size.y(),
                 size.x(), size.y(),
                 0, 0, size.x(), size.y(), texture);
}


void Result::DispSwitchCount() {
  const auto& texture = *Asset().Find().Texture(textureID[SwitchCount]);
  const Vec2f size(512, 256);
  const float posX = -600.0f;
  const float posY = -90.0f;
  drawTextureBox(posX, posY, size.x(), size.y(),
                 0, 0, size.x(), size.y(), texture);
}


void Result::DispPlayerCount() {

  // テロップ
  {
    const auto id = textureID[PlayerCount];
    const auto& texture = *Asset().Find().Texture(id);
    const Vec2f size(256, 128);
    const float posX = -340.0f;
    const float posY = -200.0f;

    drawTextureBox(posX, posY, size.x(), size.y(),
                   0, 0, size.x(), size.y(), texture);
  }

  // 回数
  {
    const float cutSize = 256.0f;
    const Vec2f pos(-420.0f, -120.0f);

    const auto id1 = textureID[gimmickCount % 10];
    const auto id2 = textureID[gimmickCount / 10];

    const auto& num1 = *Asset().Find().Texture(id1);
    drawTextureBox(pos.x(), pos.y(), cutSize, cutSize,
                   0, 0, cutSize, cutSize, num1,
                   Color::white, 0,
                   Vec2f::Ones() * 0.9f,
                   Vec2f::Ones() * cutSize * 0.5f);

    // ２桁目
    if (gimmickCount / 10) {
      const auto& num2 = *Asset().Find().Texture(id2);
      drawTextureBox(pos.x() - 180, pos.y(), cutSize, cutSize,
                     0, 0, cutSize, cutSize, num2,
                     Color::white, 0,
                     Vec2f::Ones() * 0.9f,
                     Vec2f::Ones() * cutSize * 0.5f);
    }
  }
}


void Result::DispBackToTitle() {
  const auto& texture = *Asset().Find().Texture(textureID[BackToTitle]);
  const Vec2f size(512, 128);
  const float posX = -550.0f;
  const float posY = -380.0f;
  drawTextureBox(posX, posY, size.x(), size.y(),
                 0, 0, size.x(), size.y(), texture,
                 Color::white, 0,
                 Vec2f::Ones(), Vec2f::Zero());
}


void Result::DispMedal(const bool isMedal) {
  const auto& texture = *Asset().Find().Texture(textureID[Medal]);
  const auto& size = Vec2f::Ones() * 512.0f;
  const float posX = 50.0f;
  const float posY = 0.0f;
  drawTextureBox(posX, posY, size.x(), size.y(),
                 0, 0, size.x(), size.y(), texture,
                 isMedal ? Color::white : Color(0, 0, 0, 0.2f),
                 0, Vec2f::Ones() * 0.8f, size * 0.5f);
}


void Result::DispNewton(const u_int id) {
  const auto& texture = *Asset().Find().Texture(id);
  const float size = 512.0f;
  const float posX = 480.0f;
  const float posY = -50.0f;
  drawTextureBox(posX, posY, size, size,
                 0, 0, size, size, texture,
                 Color::white, 0,
                 Vec2f::Ones() * 1.5f,
                 Vec2f::Ones() * size * 0.5f);
}
