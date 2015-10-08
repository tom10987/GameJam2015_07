
#pragma once
#include "lib/defines.hpp"
#include "lib/appEnv.hpp"
#include "lib/random.hpp"


namespace frameworks {

enum WindowSize {
  WIDTH  = 1600,
  HEIGHT = 900,
};

// キーボード入力の一覧
enum KeyBind {
  ESCAPE = GLFW_KEY_ESCAPE,
  ENTER  = GLFW_KEY_ENTER,
  KEY_L  = GLFW_KEY_LEFT,
  KEY_R  = GLFW_KEY_RIGHT,
  KEY_U  = GLFW_KEY_UP,
  KEY_D  = GLFW_KEY_DOWN,
  SPACE  = GLFW_KEY_SPACE,
};

// 重力の方向
enum GravityDirection {
  Bottom,
  Right,
  Top,
  Left,
};

// キャラクターの向き
enum PlayerDirection {
  Move_L = -1,
  Move_R = 1,
};

// システム系
enum System {
  FPS = 60,
};

// 座標、サイズ、回転状態、回転速度
struct Transform {
  Vec2f pos, scale;
  float rotate, angle;
};

// 画像 ID、切り出し開始位置、切り取りサイズ、色
struct Sprite {
  u_int id;
  Vec2f start, size;
  Color color;
};

// アプリケーション機能の呼び出し
AppEnv& Env();

// 乱数を得る
Random& Rand();

}  // end frameworks
