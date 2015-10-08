
#pragma once
#include "../Common.hpp"


namespace frameworks {
namespace utility {

// 原点の一覧
enum class Origin {
  LeftTop,
  Left,
  LeftBottom,
  CenterTop,
  Center,
  CenterBottom,
  RightTop,
  Right,
  RightBottom,

  All_Info,
};

// 画像の原点を指定、移動量を返す
const Vec2f& OffsetTextureOrigin(const Origin info);

}  // end utility
}  // end frameworks
