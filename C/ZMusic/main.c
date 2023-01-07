#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <iocslib.h>
#include <ZMSC3LIB.H>

#include "Common.h"
#include "Sound.h"

//!< In advance
//!< - Run ZMSC3
//!<    $ZMSC -F1
//!< - Create ZMD (compile ZMS)
//!<    $ZMC XXX.ZMS

#pragma region EVENTS
char EventStr[32] = "";
void OnPlay() {  strcpy(EventStr, "OnPlay "); }
void OnStop() {  strcpy(EventStr, "OnStop "); }
void OnCont() {  strcpy(EventStr, "OnCont "); }
void OnEnd() {   strcpy(EventStr, "OnEnd  "); }
void OnLoop() {  strcpy(EventStr, "OnLoop "); }
void OnClock() { strcpy(EventStr, "OnClock");  } 
#pragma endregion

#pragma region ZMD
struct ZMDEntry 
{
  uint8_t* Data;
  fpos_t Size;
};
void OnChange()
{
  B_LOCATE(0, 2);

  printf("Tempo = %d, Timer = %d\n", ZM_TEMPO(zm_tempo(-1, 0)), ZM_TIMER(zm_set_timer_value(-1, 0)));

  #if 1
  //!< TRACK TABLE
  printf("Track table = ");
  const int8_t* TrackTable = zm_get_track_table();
  PrintTable(TrackTable);
  #else
  //!< TRACK TABLE SE
  printf("Track table se = ");
  const int8_t* TrackTableSe = zm_get_track_table_se();
  PrintTable(TrackTableSe);
  #endif
}
void OnZMDChange(const struct ZMDEntry* ZMD)
{
  #if 1
  //!< Play 
  //zm_play_zmd(ZMD->Size, ZMD_HEADER_SKIP(ZMD->Data));
  zm_play_zmd(ZM_TO_INTERNAL_BUFFER, ZMD_HEADER_SKIP(ZMD->Data));
  #else
  //!< Play se
  //zm_se_play(ZMD_HEADER_SKIP(ZMD->Data));
  zm_play_zmd_se(ZMD_HEADER_SKIP(ZMD->Data));
  #endif

  OnChange();
}
#pragma endregion

void main(int argc, char* argv[])
{
  //!< Give ZMD file as argument
  if(argc < 2) {
    B_LOCATE(0, 1);
    puts("Give ZMD file as argument");
    puts("\t$ZMUSIC.X A.ZMD B.ZMD ...");
    return;
  }

  //!< Version
  {
    B_LOCATE(0, 1);
    int ZmVer = zm_check_zmsc();
    if(-1 == ZmVer) {
      puts("Run ZMSC3 in advance\n");
      return;
    }
    printf("ZmVer = 0x%0x, LibVer = %d\n", ZmVer, zm_get_zmlibver());
  }

  //!< Initialize
  zm_init(0);

#pragma region EVENTS
  {
    int Events[] = {
      (int)OnPlay,
      (int)OnStop,
      (int)OnCont,
      (int)OnEnd,
      2, (int)OnLoop,
      500, (int)OnClock, 
    };
    zm_obtain_events(ZM_ON_PLAY | ZM_ON_STOP | ZM_ON_CONT | ZM_ON_END | (ZM_LOOP_COUNT | ZM_ON_LOOP) | (ZM_CLOCK_COUNT | ZM_ON_CLOCK), Events);
  }
#pragma endregion

#pragma region ZMD
  //!< Load ZMD files (arguments)
  struct ZMDEntry* ZMDs = (struct ZMDEntry *)calloc(argc - 1 + 1, sizeof(*ZMDs));
  int ZMDIndexMax = 0;
  for(int i = 1;i < argc;++i) {
    FILE* Fp = fopen(argv[i], "rb");
    if(NULL != Fp) {

      struct ZMDEntry* ZMD = &ZMDs[ZMDIndexMax];
      ZMD->Size = GetFileSize(Fp);
      if(ZMD->Size) {
        ZMD->Data = (uint8_t*)malloc(ZMD->Size);
        if(NULL != ZMD->Data) {
          fread(ZMD->Data, sizeof(*ZMD->Data), ZMD->Size, Fp);
          ++ZMDIndexMax;
        }
      }

      fclose(Fp);
    }
  }
  //!< Sentinel
  ZMDs[ZMDIndexMax].Data = NULL; 
  if(0 == ZMDIndexMax) {
    free(ZMDs);
    return;
  }
  int ZMDIndex = 0, ZMDPrevIndex = 0;
#pragma endregion

  OnZMDChange(&ZMDs[0]);

  int ChannelStatus[16 + 1];
  short TrackStatus[65535 + 1];

  short Track[] = { 0, -1 };
  while(1) {
    if(P_ON) { zm_play_all(); }
    if(S_ON) { zm_stop_all(); }
    if(C_ON) { zm_cont_all(); }
    if(ESC_ON) { zm_stop_all(); break; }

    if(ONE_ON) { Track[0] = 1; zm_play(Track); }
    if(TWO_ON) { Track[0] = 2; zm_play(Track); }
    if(THREE_ON) { Track[0] = 3; zm_play(Track); }
    if(FOUR_ON) { Track[0] = 4; zm_play(Track); }
    if(FIVE_ON) { Track[0] = 5; zm_play(Track); }
    if(SIX_ON) { Track[0] = 6; zm_play(Track); }
    if(SEVEN_ON) { Track[0] = 7; zm_play(Track); }
    if(EIGHT_ON) { Track[0] = 8; zm_play(Track); }
    if(NINE_ON) { Track[0] = 9; zm_play(Track); }
    if(ZERO_ON) { Track[0] = 0; zm_play(Track); }

    //!< Select ZMD
    if(UP_ON) {
      ZMDIndex = MAX(--ZMDIndex, 0);
    }
    if(DOWN_ON) {
      if(NULL != ZMDs[ZMDIndex + 1].Data) {
        ++ZMDIndex;
      }
    }
    if(ZMDPrevIndex != ZMDIndex) {
      ZMDPrevIndex = ZMDIndex;
      OnZMDChange(&ZMDs[ZMDIndex]);
    }

    B_LOCATE(0, 10);

    //!< ZMD index now playing
    printf("ZMDIndex = %d / %d\n", ZMDIndex, ZMDIndexMax - 1);

    //!< Play time
    const int Time = zm_get_play_time();
    printf("%02d:%02d:%02d\n", ZM_HOUR(Time), ZM_MiNUTE(Time), ZM_SECOND(Time));
    puts("");

    //!< ZMSC status cf) ZM_STAT.MAC
    {
      puts("ZMSC status");
      const struct zmusic_stat* Stat = (const struct zmusic_stat*)zm_get_zmsc_status();
      printf("\twk_size = %d\n", Stat->wk_size);
      printf("\tplay_start_time = %02x:%02x:%02x\n", (Stat->play_start_time & 0xff0000) >> 16, (Stat->play_start_time & 0xff00) >> 8, Stat->play_start_time & 0xff);
      printf("\tplay_stop_time = %02x:%02x:%02x\n", (Stat->play_stop_time & 0xff0000) >> 16, (Stat->play_stop_time & 0xff00) >> 8, Stat->play_stop_time & 0xff);
      printf("\tplay_cont_time = %02x:%02x:%02x\n", (Stat->play_cont_time & 0xff0000) >> 16, (Stat->play_cont_time & 0xff00) >> 8, Stat->play_cont_time & 0xff);
      printf("\tmask_opm_ch = %d\n", Stat->mask_opm_ch);
      printf("\tse_tr_max = %d\n", Stat->se_tr_max);
      puts("");
    }

    //!< Track channel info
    {
      puts("Playing");
  
      //!< Channel status
      zm_play_status_all_ch(ChannelStatus);
      printf("\tChannel = { ");
      for(int i=0;i<COUNTOF(ChannelStatus);++i) {
        if(-1 == ChannelStatus[i]) { break; }
        printf("%d(%d), ", ZM_CHANNEL(ChannelStatus[i]), ZM_DEV(ChannelStatus[i]));
      }
      puts("}");

      //!< Track status
      zm_play_status_all_tr(TrackStatus);
      printf("\tTrack = { ");
      for(int i=0;i<COUNTOF(TrackStatus);++i) {
        if(-1 == TrackStatus[i]) { break; }
        printf("%d, ", TrackStatus[i]);
        //zm_atoi(TrackStatus[i]);
      }
      puts("}");
    }

    //!< Events info
    puts("");
    puts(EventStr);
  }

#pragma region ZMD
  //!< Release
  if(NULL != ZMDs) {
    int i = 0;
    while(NULL != ZMDs[i].Data) {
      free(ZMDs[i++].Data);
    }
    free(ZMDs);
  }
#pragma endregion
}

