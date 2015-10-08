
#pragma once
#include "Gimmick.h"


namespace frameworks {
namespace object {

class GimmickController {
public:
  GimmickController() {}
  void Setup(const StageID, const float);

  void Update();
  void Draw();

  void SwitchPush(const int);
  const std::vector<Gimmick>& GetGimmicks() const { return gimmicks; }
  const float GetSize() const { return *gimmickSize; }

private:
  std::vector<u_int> textureID;
  std::vector<Gimmick> gimmicks;
  std::unique_ptr<const float> gimmickSize;

  void TextureSetup();
};

}
}
