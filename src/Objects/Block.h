
#pragma once
#include "Object.hpp"


namespace frameworks {
namespace object {

struct BlockData {
  Vec2f pos;
  u_int id;
};

class Block {
public:
  Block() {}

  void Setup(const StageID, const float);

  void Draw();

  const std::vector<Vec2f> GetBlocks();
  const Vec2f GetBlockSize()
    const { return std::move(Vec2f::Ones() * (*blockSize)); }

private:
  std::vector<u_int> textureID;

  std::vector<BlockData> blocks;
  std::unique_ptr<const float> blockSize;

  void TextureSetup(const StageID);
  void BlockSetup(const StageID);
};

}
}
