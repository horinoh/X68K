#include <stdio.h>
#include <iocslib.h>

#include "Common.h"

void main()
{  
  TPALET(0, COL_GRAY); //!< BG color
  TPALET(3, COL_GREEN); //!< FG color 

  puts("hello world.\n");
  getchar();
  
  TPALET(0, COL_BLACK);
  TPALET(3, COL_WHITE);
}

