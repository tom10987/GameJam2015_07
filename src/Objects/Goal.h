
#pragma once
#include "Object.hpp"


namespace frameworks {
namespace object {

class Goal {
public:
  Goal() : isClear(false) {}

  void Setup(const Vec2f& pos,
             const float size,
             const int direction);

  void Update();
  void Draw();

  void StageClear() { isClear = true; }
  const bool IsClear() const { return isClear; }

  const Transform& GetTransform() const { return transform; }

private:
  enum { Play, Clear, };
  std::vector<u_int> textureID;
  Transform transform;

  bool isClear;
};

}
}
