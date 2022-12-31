#include <stdio.h>
#include <stdint.h>
#include <iocslib.h>
#include <ZMSC3LIB.H>

#include "Common.h"
#include "Sound.h"

//!< Run ZMSC3 in advance

//!<  .OPM
//!<  .ZMS (Text)
//!<  .ZMD (Binary)
void main()
{
  const int Ver = zm_check_zmsc();
  if(-1 == Ver) {
    puts("Run ZMSC3 in advance\n");
    return;
  }

  printf("Ver = 0x%0x\n", Ver);
  zm_init(0);

  if(0 != zm_assign(ZM_DEVICE(ZM_DEV_FM, 0), 0)) {
    puts("zm_assign() failed");
  }

  B_LOCATE(0, 2);
  printf("TEMPO=%d\n", ZM_TEMPO(zm_tempo(-1, 0)));
  printf("TIMER=%d\n", ZM_TIMER(zm_set_timer_value(-1, 0)));

  zm_play_all();
  // uint8_t ZMD[] = {};
  // if(0 != zm_play_zmd(sizeof(ZMD), ZMD)) {
  // }
  //zm_play();
  //zm_stop();

  int Channels[16 + 1];
  short Tracks[65535 + 1];
  while(1) {
    if(ESC_ON) { break; }

    const int Time = zm_get_play_time();
    B_LOCATE(0, 10);
    printf("%d:%d:%d\n", ZM_HOUR(Time), ZM_MiNUTE(Time), ZM_SECOND(Time));

    zm_play_status_all_ch(Channels);
    for(int i=0;i<COUNTOF(Channels);++i) {
      if(-1 == Channels[i]) { break; }
       printf("Channel %d (Dev %d) playing\n", ZM_CHANNEL(Channels[i]), ZM_DEV(Channels[i]));

       if(zm_play_status_ch(Channels[i])){ }
    }
    zm_play_status_all_tr(Tracks);
    for(int i=0;i<COUNTOF(Tracks);++i) {
      if(-1 == Tracks[i]) { break; }
      printf("Track %d playing\n", Tracks[i]);

      if(zm_play_status_tr(Tracks[i])) { }

      //zm_atoi(Tracks[i]);
    }
  }
}

