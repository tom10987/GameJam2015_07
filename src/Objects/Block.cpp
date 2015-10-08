
#include "Block.h"

using namespace frameworks;
using namespace frameworks::object;


void Block::Setup(const StageID stage,
                  const float size) {
  textureID.clear();
  blocks.clear();

  blockSize = std::make_unique<float>(size);
  TextureSetup(stage);
  BlockSetup(stage);
}


void Block::Draw() {
  const float size = 108.0f;
  const auto offset = (*blockSize) * 0.5f;

  for (const auto& block : blocks) {
    const auto pos = block.pos + (Vec2f::Ones() * offset);
    const auto texture = Asset().Find().Texture(block.id);

    drawTextureBox(pos.x(), pos.y(),
                   *blockSize, *blockSize,
                   0, 0, size, size,
                   *texture, Color::white,
                   0, Vec2f::Ones(),
                   Vec2f::Ones() * offset);
  }
}


const std::vector<Vec2f> Block::GetBlocks() {
  std::vector<Vec2f> pos;
  for (const auto& block : blocks) { pos.push_back(block.pos); }
  return std::move(pos);
}


void Block::TextureSetup(const StageID stage) {
  std::vector<std::string> BlockTable;

  switch (stage) {
    default:;
    case StageID::Stage1:
      BlockTable = {
        "res/png/block_dA.png",   // [0]ブロックの上を歩ける
        "res/png/block_dB.png",   // [1]右
        "res/png/block_dC.png",   // [2]下
        "res/png/block_dD.png",   // [3]左
        "res/png/block_dE.png",   // [4]上と右
        "res/png/block_dF.png",   // [5]右と下
        "res/png/block_dG.png",   // [6]下と左
        "res/png/block_dH.png",   // [7]左と上
        "res/png/block_dI.png",   // [8]上下
        "res/png/block_dJ.png",   // [9]左右
        "res/png/block_dK.png",   // [10]上以外
        "res/png/block_dL.png",   // [11]右以外
        "res/png/block_dM.png",   // [12]下以外
        "res/png/block_dN.png",   // [13]左以外
        "res/png/block_dO.png",   // [14]なし
      };
      break;

    case StageID::Stage2:
      BlockTable = {
        "res/png/block_tA.png",   // [0]ブロックの上を歩ける
        "res/png/block_tB.png",   // [1]右
        "res/png/block_tC.png",   // [2]下
        "res/png/block_tD.png",   // [3]左
        "res/png/block_tE.png",   // [4]上と右
        "res/png/block_tF.png",   // [5]右と下
        "res/png/block_tG.png",   // [6]下と左
        "res/png/block_tH.png",   // [7]左と上
        "res/png/block_tI.png",   // [8]上下
        "res/png/block_tJ.png",   // [9]左右
        "res/png/block_tK.png",   // [10]上以外
        "res/png/block_tL.png",   // [11]右以外
        "res/png/block_tM.png",   // [12]下以外
        "res/png/block_tN.png",   // [13]左以外
        "res/png/block_tO.png",   // [14]なし
      };
      break;

    case StageID::Stage3:
      BlockTable = {
        "res/png/block_nA.png",   // [0]ブロックの上を歩ける
        "res/png/block_nB.png",   // [1]右
        "res/png/block_nC.png",   // [2]下
        "res/png/block_nD.png",   // [3]左
        "res/png/block_nE.png",   // [4]上と右
        "res/png/block_nF.png",   // [5]右と下
        "res/png/block_nG.png",   // [6]下と左
        "res/png/block_nH.png",   // [7]左と上
        "res/png/block_nI.png",   // [8]上下
        "res/png/block_nJ.png",   // [9]左右
        "res/png/block_nK.png",   // [10]上以外
        "res/png/block_nL.png",   // [11]右以外
        "res/png/block_nM.png",   // [12]下以外
        "res/png/block_nN.png",   // [13]左以外
        "res/png/block_nO.png",   // [14]なし
      };
      break;
  }

  for (auto& data : BlockTable) {
    textureID.push_back(Asset().Append().Texture(data));
  }
}


void Block::BlockSetup(const StageID stage) {

  // ブロック配置
  switch (stage) {
    default:;
    case StageID::Stage1:
      blocks = {
        // 左
        { Vec2f(-6, 2.5f), 4 },
        { Vec2f(-6, 1.5f), 1 },
        { Vec2f(-6, 0.5f), 1 },
        { Vec2f(-6, -0.5f), 1 },
        { Vec2f(-6, -1.5f), 1 },
        { Vec2f(-6, -2.5f), 14 },
        { Vec2f(-5, -2.5f), 0 },
        { Vec2f(-4, -2.5f), 0 },
        { Vec2f(-3, -2.5f), 4 },
        { Vec2f(-3, -3.5f), 14 },
        { Vec2f(-2, -3.5f), 0 },
        { Vec2f(-1, -3.5f), 0 },
        { Vec2f(0, -3.5f), 0 },
        { Vec2f(1, -3.5f), 4 },

        // 右
        { Vec2f(4, -3.5f), 6 },
        { Vec2f(4, -2.5f), 3 },
        { Vec2f(4, -1.5f), 3 },
        { Vec2f(4, -0.5f), 3 },
        { Vec2f(4, 0.5f), 3 },
        { Vec2f(4, 1.5f), 3 },
        { Vec2f(4, 2.5f), 14 },
        { Vec2f(3, 2.5f), 2 },
        { Vec2f(2, 2.5f), 2 },
        { Vec2f(1, 2.5f), 2 },
        { Vec2f(0, 2.5f), 6 },
      };
      break;

      case StageID::Stage2:
      blocks = {
        // 左
        { Vec2f(-7.5f, -0.5f), 4 },
        { Vec2f(-7.5f, -1.5f), 1 },
        { Vec2f(-7.5f, -2.5f), 1 },
        { Vec2f(-7.5f, -3.5f), 1 },
        { Vec2f(-7.5f, -4.5f), 14 },
        { Vec2f(-6.5f, -4.5f), 0 },
        { Vec2f(-5.5f, -4.5f), 0 },
        { Vec2f(-4.5f, -4.5f), 4 },
        { Vec2f(-4.5f, -5.5f), 1 },
        { Vec2f(-4.5f, -6.5f), 5 },

        // 真ん中上
        { Vec2f(-4.5f, 3.5f), 6 },
        { Vec2f(-3.5f, 3.5f), 2 },
        { Vec2f(-2.5f, 3.5f), 2 },
        { Vec2f(-1.5f, 3.5f), 2 },
        { Vec2f(-0.5f, 3.5f), 2 },
        { Vec2f(0.5f, 3.5f), 2 },
        { Vec2f(1.5f, 3.5f), 2 },
        { Vec2f(2.5f, 3.5f), 5 },
        { Vec2f(2.5f, 4.5f), 1 },
        { Vec2f(2.5f, 5.5f), 4 },

        // 真ん中
        { Vec2f(0.5f, -0.5f), 12 },
        { Vec2f(0.5f, -1.5f), 9 },
        { Vec2f(0.5f, -2.5f), 9 },
        { Vec2f(0.5f, -3.5f), 9 },
        { Vec2f(0.5f, -4.5f), 10 },

        // 右
        { Vec2f(7.5f, 4.5f), 7 },
        { Vec2f(7.5f, 3.5f), 3 },
        { Vec2f(7.5f, 2.5f), 3 },
        { Vec2f(7.5f, 1.5f), 3 },
        { Vec2f(7.5f, 0.5f), 3 },
        { Vec2f(7.5f, -0.5f), 3 },
        { Vec2f(7.5f, -1.5f), 14 },
        { Vec2f(6.5f, -1.5f), 0 },
        { Vec2f(5.5f, -1.5f), 7 },
        { Vec2f(5.5f, -2.5f), 3 },
        { Vec2f(5.5f, -3.5f), 3 },
        { Vec2f(5.5f, -4.5f), 3 },
        { Vec2f(5.5f, -5.5f), 3 },
        { Vec2f(5.5f, -6.5f), 6 },
      };
      break;

      case StageID::Stage3:
      blocks = {
        // 左上
        { Vec2f(-7, 3), 12 },
        { Vec2f(-7, 2), 9 },
        { Vec2f(-7, 1), 5 },
        { Vec2f(-8, 1), 11 },

        // 左下
        { Vec2f(-5, -3), 10 },
        { Vec2f(-5, -2), 7 },
        { Vec2f(-4, -2), 8 },
        { Vec2f(-3, -2), 13 },

        // 真ん中
        { Vec2f(0, -1), 11 },
        { Vec2f(1, -1), 8 },
        { Vec2f(2, -1), 13 },

        // 右上
        { Vec2f(3, 3), 11 },
        { Vec2f(4, 3), 8 },
        { Vec2f(5, 3), 8 },
        { Vec2f(6, 3), 5 },
        { Vec2f(6, 4), 12 },

        // 右下
        { Vec2f(3, -5), 11 },
        { Vec2f(4, -5), 8 },
        { Vec2f(5, -5), 8 },
        { Vec2f(6, -5), 13 },
      };
      break;
  }

  // 座標と ID を変換
  for (auto& block : blocks) {
    block.pos *= (*blockSize);
    block.id = textureID[block.id];
  }
}
