
#include "OffsetOrigin.h"
#include <map>


namespace frameworks {
namespace utility {

const Vec2f& OffsetTextureOrigin(const Origin info) {
  static std::map<Origin, Vec2f> offsetTable = {
    { Origin::LeftTop,      Vec2f(0.0f, 1.0f) },
    { Origin::Left,         Vec2f(0.0f, 0.5f) },
    { Origin::LeftBottom,   Vec2f(0.0f, 0.0f) },
    { Origin::CenterTop,    Vec2f(0.5f, 1.0f) },
    { Origin::Center,       Vec2f(0.5f, 0.5f) },
    { Origin::CenterBottom, Vec2f(0.5f, 0.0f) },
    { Origin::RightTop,     Vec2f(1.0f, 1.0f) },
    { Origin::Right,        Vec2f(1.0f, 0.5f) },
    { Origin::RightBottom,  Vec2f(1.0f, 0.0f) },
  };

  return offsetTable.find(info)->second;
}

bool IsHitRectToRect(const Vec2f& pos1, const Vec2f& size1,
                     const Vec2f& pos2, const Vec2f& size2) {
  const bool hitL = pos1.x() + size1.x() > pos2.x();
  const bool hitR = pos1.x() < pos2.x() + size2.x();
  const bool hitB = pos1.y() + size1.y() > pos2.y();
  const bool hitT = pos1.y() < pos2.y() + size2.y();

  return (hitL && hitR && hitB && hitT);
}

}  // end utility
}  // end frameworks
