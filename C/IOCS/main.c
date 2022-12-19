#include <stdio.h>
#include <iocslib.h>

#define COUNTOF(_Array) (sizeof(_Array) / sizeof(_Array[0]))

enum
{
  Mode_1024_512X512_C16_P1_31KHZ,
  Mode_1024_512X512_C16_P1_15KHZ,

  Mode_1024_256X256_C16_P1_31KHZ,
  Mode_1024_256X256_C16_P1_15KHZ,

  Mode_512_512X512_C16_P4_31KHZ,
  Mode_512_512X512_C16_P4_15KHZ,

  Mode_512_256X256_C16_P4_31KHZ,
  Mode_512_256X256_C16_P4_15KHZ,

  Mode_512_512X512_C256_P2_31KHZ,
  Mode_512_512X512_C256_P2_16KHZ,

  Mode_512_256X256_C256_P2_31KHZ,
  Mode_512_256X256_C256_P2_15KHZ,

  Mode_512_512X512_C65536_P1_31KHZ,
  Mode_512_512X512_C65536_P1_15KHZ,

  Mode_512_256X256_C65536_P1_31KHZ,
  Mode_512_256X256_C65536_P1_15KHZ,

  Mode_1024_768X512_C16_P1_31KHZ,
  Mode_1024_1024X424_C16_P1_24KHZ,
  Mode_1024_1024X848_C16_P1_24KHZ,

  Mode_1024_640X480_C16_P1_24KHZ,

  Mode_1024_768X512_C256_P2_31KHZ,
  Mode_1024_1024X848_C256_P2_24KHZ,
  Mode_1024_1024X424_C256_P2_24KHZ,
  Mode_1024_640X480_C256_P2_24KHZ,

  Mode_1024_768X512_C65536_P1_31KHZ,
  Mode_1024_1024X848_C65536_P1_24KHZ,
  Mode_1024_1024X424_C65536_P1_24KHZ,
  Mode_1024_640X480_C65536_P1_24KHZ,
};

//!< Group[0, f], Bit[0, 7]
#define TO_SCANODE(_Group, _Bit) ((_Group << 3) | _Bit)
#define TO_GROUP(_ScanCode) ((_ScanCode & 0xf8) >> 3)
#define TO_BIT(_ScanCode) (_ScanCode & 0x07)

#define TO_SCANCODE(_KeyCode) ((_KeyCode & 0xff00) >> 8)
#define TO_INTERNALCODE(_KeyCode) (_KeyCode & 0xff)

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
    //!< CRT モード変更
    //CRTMOD(Mode_512_256X256_C256_P2_31KHZ);
  }

  printf("CRT mode changed %d -> %d\n", PrevCRTMode, CRTMOD(-1));

  {
    printf("Press any key\n");
    //!< B_KEYINP : ScanCode << 8 | InternalCode を返す
    const int KeyCode = B_KEYINP();
    printf("\"%c\"(0x%x, Group=%d, Bit=%d)\n", TO_INTERNALCODE(KeyCode), KeyCode, TO_GROUP(TO_SCANCODE(KeyCode)), TO_BIT(TO_SCANCODE(KeyCode)));

    printf("Press any key\n");
    B_KEYINP();
  }

 /*
        0   1   2   3   4   5   6   7 (BIT)
    0      ESC  1   2   3   4   5   6     
    1   7   8   9   0   -       \   BS  
    2   TAB q   w   e   r   t   y   u
    3   i   o   p   @   [   CR  a   s
    4   d   f   g   h   j   k   l   ;
    5   :   ]   z   x   c   v   b   n
    6   m   ,   .   /   _   SP  HM  DEL
    7   RUP RDN UND L   U   R   D   CLR
    8   /   *   -   7   8   9   +   4
    9   5   6   =   1   2   3   ENT 0
    a   ,   .
    b
    c       BRK CPY F1  F2  F3  F4  F5
    d   F6  F7  F8  F9  F10
    e   SFT CTL OPT OPT2
    f
    (GROUP)
  */ 
  while(1) {
    //!< ESC (グループ0, ビット (1 << 1)) が押された
    if(BITSNS(0) & (1 << 1)) { break; }
   
    //!< コンソールクリア
    puts("\e[1;1H\e[2J");
    puts("Press ESC to exit");
    //!< 臣下状態の表示
    for(int i = 0; i < 16; ++i) {
      printf("Group=0x%x, Bits=0x%02x\n", i, BITSNS(i));
    }

    #if 0
    //!< ScanCode = Group << 3 | Bit
    //!< B_KEYSNS : 0x10000 | ScanCode << 8 | InternalCode を返す
    B_KEYSNS();
    #endif
  }

  {
    //!< マウスカーソルオン
    B_CURON();
    //!< CRT モード
    CRTMOD(PrevCRTMode);
  }

}

