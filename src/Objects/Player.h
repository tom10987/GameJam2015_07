
#pragma once
#include "Object.hpp"
#include <vector>


namespace frameworks {
namespace object {

class Player : public Object {
public:
  Player();
  void Setup();

  void Update() override;
  void Draw() override;

  void Start(const Vec2f&, const float);
  const Vec2f& GetStartPos() const { return start; }

  void GravityUpdate();
  void GravityReset() { velocity = 0.0f; }
  void SetGravityDirection(const int dir) { gravityState = dir; }

  const bool IsKeyActive() const { return Env().isPushKey(SPACE); }
  const int GetDirection() const { return gravityState; }

  void SetMoveState(const bool state) { enableMove = state; }
  const bool EnableMove() const { return enableMove; }

  void Translate(const Vec2f& translate) { transform.pos += translate; }

private:
  enum {
    MoveSpeed = 5,
    GravityMax = 8,
  };

  Vec2f start;
	
  int gravityState;
	int direction;
  bool enableMove;

  float acceleration;
	float velocity;

  std::vector<u_int> textureID;

  void Move(const Vec2f&);
};

}  // end object
}  // end frameworks
