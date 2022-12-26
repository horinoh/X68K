#include <stdio.h>
#include <iocslib.h>

#include "../Common.h"
#include "../Joy.h"

void main()
{
  //!< CRT mode
  const int PrevCRT = CRTMOD(-1);
  //B_SUPER(0);
  //!< Cursor off
  B_CUROFF();
  //!< Clear graphics
  G_CLR_ON();

  while(1) 
  {    
    if(ESC_ON) { break; }
   
    //!< 0 ‚ÌŽž‚É ON ‚È‚Ì‚Å’ˆÓ
    const int Joy = JOYGET(0);
    B_LOCATE(0, 2);
    printf(" %s\n", (Joy & JOY_UP) ? "-" : "o");
    printf("%s  %s\n", (Joy & JOY_LEFT) ? "-" : "o", (Joy & JOY_RIGHT) ? "-" : "o");
    printf(" %s      %s %s\n", (Joy & JOY_DOWN) ? "-" : "o", (Joy & JOY_B) ? "-" : "o", (Joy & JOY_A) ? "-" : "o");
  }

  //!< Cursor on
  B_CURON();
  //!< CRT mode
  CRTMOD(PrevCRT);
}

