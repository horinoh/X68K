#include <stdio.h>
#include <iocslib.h>

#define ESC_ON (BITSNS(0) & (1 << 1))

#define JOY_UP (1 << 0)
#define JOY_DOWN (1 << 1)
#define JOY_LEFT (1 << 2)
#define JOY_RIGHT (1 << 3)
#define JOY_A (1 << 5)
#define JOY_B (1 << 6)

void main()
{
  const short PrevCRTMode = CRTMOD(-1);
  {
    //!< スーパーバイザーモード
    B_SUPER(0);
    //!< マウスカーソルオフ
    B_CUROFF();
    //!< グラフィックスクリア
    G_CLR_ON();
  }

  while(1) {
    B_LOCATE(0, 0);
    puts("Press ESC to exit");
    
     //!< ESC (グループ0, ビット (1 << 1)) が押された
    if(ESC_ON) { break; }
   
    //!< 0 の時に ON なので注意
    const int Joy = JOYGET(0);
    printf(" %s\n", (Joy & JOY_UP) ? "-" : "o");
    printf("%s  %s\n", (Joy & JOY_LEFT) ? "-" : "o", (Joy & JOY_RIGHT) ? "-" : "o");
    printf(" %s      %s %s\n", (Joy & JOY_DOWN) ? "-" : "o", (Joy & JOY_B) ? "-" : "o", (Joy & JOY_A) ? "-" : "o");
  }

  {
    //!< マウスカーソルオン
    B_CURON();
    //!< CRT モード
    CRTMOD(PrevCRTMode);
  }
}

