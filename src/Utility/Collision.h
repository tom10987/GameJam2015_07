
#pragma once
#include "../Common.hpp"


namespace frameworks {
namespace utility {

/*
// �}�E�X�J�[�\���Ǝl�p
bool OnMouseRect(const Vec2f& mouse_pos,
                 const Vec2f& pos,
                 const Vec2f& size);
*/

/*
// �_�Ɖ~�i�^�~�j
bool IsHitPointToCircle(const Vec2f& point,
                        const Vec2f& pos,
                        const float radius);
*/

// �l�p�Ǝl�p
bool IsHitRectToRect(const Vec2f&, const Vec2f&,
                     const Vec2f&, const Vec2f&);

}  // end utility
}  // end frameworks
