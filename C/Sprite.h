#pragma once

//!< SP_REGST() 用
enum {
  SP_ON_VBLANK = 0,
  SP_IMMEDIATE = 0x80,
};
//!< SP_REGST() 用
enum {
  //!< 非表示
  SP_PRI_INVISIBLE,
  //!< BG1 よりも後ろ
  SP_PRI_BACK,
  //!< BG0 と BG1 の間
  SP_PRI_MIDDLE,
  //!< BT0 よりも手前
  SP_PRI_FRONT,
};

enum {
  //!< スプライト座標を(0, 0) にすると、実画面の左上にスプライトの右下が来て丁度画面から去る感じになっている
  SP_COORD_OFFSET = 16,
};