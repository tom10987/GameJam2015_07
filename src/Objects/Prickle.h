
#pragma once
#include "Object.hpp"


namespace frameworks {
namespace object {

class Prickle {
public:
  Prickle() {}

  void Setup();
  void Draw(const int);

private:
  enum { Horizontal, Vertical, };
  std::vector<u_int> textureID;
  const Color GetColor(const int);
};

}
}
