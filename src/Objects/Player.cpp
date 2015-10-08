
#include "Player.h"

using namespace frameworks;
using namespace frameworks::object;


Player::Player() :
gravityState(GravityDirection::Bottom),
direction(Move_R),
enableMove(false),
acceleration(0.25f),
velocity(0.0f) {
}


void Player::Setup() {
  transform.rotate = transform.angle = 0.0f;

  const std::string TextureTable[] = {
    "res/png/ochirukun_red.png",
    "res/png/ochirukun_blue.png",
    "res/png/ochirukun_yellow.png",
    "res/png/ochirukun_green.png",
  };

  for (const auto& data : TextureTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void Player::Start(const Vec2f& pos, const float size) {
  transform.pos = pos;
  transform.scale = Vec2f::Ones() * size;
  start = pos;
}


void Player::Update() {

  // 移動できる状況でなければ、キー判定をスキップ
  if (!enableMove) { return; }

  // 移動キーの入力受付
  if (gravityState == GravityDirection::Top ||
      gravityState == GravityDirection::Bottom) {
    if (Env().isPressKey(KEY_L)) { Move(Vec2f(-MoveSpeed, 0)); }
    if (Env().isPressKey(KEY_R)) { Move(Vec2f(MoveSpeed, 0)); }
  }
  if (gravityState == GravityDirection::Left ||
      gravityState == GravityDirection::Right) {
    if (Env().isPressKey(KEY_D)) { Move(Vec2f(0, -MoveSpeed)); }
    if (Env().isPressKey(KEY_U)) { Move(Vec2f(0, MoveSpeed)); }
  }
}


void Player::Draw() {
  const auto texture = Asset().Find().Texture(textureID[gravityState]);

  const auto offset = transform.scale * 0.5f;
  const auto pos = transform.pos + offset;
  const float Size = 512.0f;

  drawTextureBox(pos.x(), pos.y(),
                 transform.scale.x(), transform.scale.y(),
                 0, 0, Size, Size,
                 *texture, Color::white,
                 gravityState * (M_PI / 2),
                 Vec2f(direction, 1), offset);
}


void Player::GravityUpdate() {

  // 落ちる速度が上がりすぎないように抑制
  velocity += acceleration;
  if (velocity > GravityMax) velocity = GravityMax;

  // 重力の向きに合わせて落ちる
  switch (gravityState) {
    case GravityDirection::Top:
      transform.pos.y() += velocity;
      break;

    case GravityDirection::Bottom:
      transform.pos.y() -= velocity;
      break;

    case GravityDirection::Left:
      transform.pos.x() -= velocity;
      break;

    case GravityDirection::Right:
      transform.pos.x() += velocity;
      break;

    default: break;
  }
}


void Player::Move(const Vec2f& moveSpeed) {
  switch (gravityState) {
    default: break;
    case GravityDirection::Bottom:
      direction = moveSpeed.x() > 0 ? Move_R : Move_L;
      break;

    case GravityDirection::Right:
      direction = moveSpeed.y() > 0 ? Move_R : Move_L;
      break;

    case GravityDirection::Top:
      direction = moveSpeed.x() > 0 ? Move_L : Move_R;
      break;

    case GravityDirection::Left:
      direction = moveSpeed.y() > 0 ? Move_L : Move_R;
      break;
  }

  transform.pos += moveSpeed;
}
