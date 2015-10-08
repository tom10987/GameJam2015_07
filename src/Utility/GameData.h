
#pragma once
#include "../Common.hpp"


namespace frameworks {

enum StageID {
  Stage1,
  Stage2,
  Stage3,
  All_Stage,
  None,
};

class GameData {
public:
  static GameData& Get() {
    static GameData gameData;
    return gameData;
  }

  // 選択したステージの ID を返す
  const StageID GetStageID() const { return stage; }

  // ステージの ID を保持
  void SetStageID(const StageID id) { stage = id; }

  // ギミック画像の ID リストを返す
  std::vector<u_int>& GimmickID() { return gimmickID; }

  // ギミックを起動した回数を返す
  // TIPS: 各ステージごとのカウンタを返す
  u_int& GimmickCount() { return gimmickCounter[stage]; }

  // ギミックのカウンタをリセットする
  void CountReset() { for (auto& count : gimmickCounter) count = 0; }

  // 前回の記録を更新できるか確認
  void RankingUpdate() {
    if (rankingCounter[stage] < gimmickCounter[stage])
      rankingCounter[stage] = gimmickCounter[stage];
  }

  // メダル獲得条件
  const std::vector<u_int>& GetMedalNum() const { return medalNumber; }

  // 全てのステージの記録を返す
  std::vector<u_int>& RankingCounter() { return rankingCounter; }

private:
  StageID stage;
  std::vector<u_int> gimmickID;

  std::vector<u_int> gimmickCounter;   // リザルトで表示するカウンタ
  std::vector<u_int> rankingCounter;   // タイトルで表示するカウンタ
  std::vector<u_int> medalNumber;      // メダル獲得条件

  GameData() : stage(StageID::Stage1) {
    gimmickCounter.resize(All_Stage);
    for (auto& count : gimmickCounter) { count = 0; }

    rankingCounter.resize(All_Stage);
    for (auto& count : rankingCounter) { count = 0; }

    medalNumber = { 4, 4, 9, };
  }
};

}
