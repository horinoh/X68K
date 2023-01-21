#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <iocslib.h>
#include <ZMSC3LIB.H>

#include "Common.h"
#include "Sound.h"

//!< 予め ZMSC3 を実行しておくこと (In advance run ZMSC3)
//!<    $ZMSC -F1

//!< ZMD は ZMS をコンパイルして作成しておくこと (Create ZMD by compiling ZMS)
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
  //!< トラックテーブル (Track table)
  printf("Track table = ");
  const int8_t* TrackTable = zm_get_track_table();
  PrintTable(TrackTable);
  #else
  //!< トラックテーブル SE (Track table SE()
  printf("Track table se = ");
  const int8_t* TrackTableSe = zm_get_track_table_se();
  PrintTable(TrackTableSe);
  #endif
}
void OnZMDChange(const struct ZMDEntry* ZMD)
{
  #if 1
  //!< 再生 (Play)
  zm_play_zmd(ZMD->Size, ZMD_HEADER_SKIP(ZMD->Data));
  //zm_play_zmd(ZM_TO_INTERNAL_BUFFER, ZMD_HEADER_SKIP(ZMD->Data));
  #else
  //!< SE再生 (Play SE)
  //zm_se_play(ZMD_HEADER_SKIP(ZMD->Data));
  zm_play_zmd_se(ZMD_HEADER_SKIP(ZMD->Data));
  #endif

  OnChange();
}
#pragma endregion

void main(int argc, char* argv[])
{
  //!< 引数として ZMD ファイルを与えてください (Give ZMD file as argument)
  if(argc < 2) {
    B_LOCATE(0, 1);
    puts("Give ZMD file as argument");
    puts("\t$ZMUSIC.X A.ZMD B.ZMD ...");
    return;
  }

  //!< バージョン (Version)
  B_LOCATE(0, 1);
  if(-1 == zm_check_zmsc()) {
    puts("Run ZMSC3 in advance\n");
    return;
  }
  printf("ZmVer = 0x%0x, LibVer = %d\n", zm_ver(), zm_get_zmlibver());

  //!< 初期化 (Initialize)
  zm_init(0);

  //!< イベントコールバック (Event callback)
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
  //!< ZMD ファイル読込 (Load ZMD files)
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
  //!< 末尾に版兵 (Sentinel)
  ZMDs[ZMDIndexMax].Data = NULL; 
  if(0 == ZMDIndexMax) {
    free(ZMDs);
    return;
  }
  int ZMDIndex = 0, ZMDPrevIndex = 0;
  #pragma endregion

  // #pragma region MASK
  // short ChannelMask[] = {
  //   ZM_SET_DEVICE_CHANNEL(ZM_DEV_FM, 1),
  //   ZM_SET_DEVICE_CHANNEL(ZM_DEV_FM, 3),
  //   ZM_SET_DEVICE_CHANNEL(ZM_DEV_FM, 5),
  //   ZM_SET_DEVICE_CHANNEL(ZM_DEV_FM, 7),
  //   -1,
  // };
  // zm_mask_channels(ChannelMask); 

  // short TrackMask[] = {
  //   ZM_TRACK_MASK(0, ZM_TRACK_MASK_ON),
  //   ZM_TRACK_MASK(2, ZM_TRACK_MASK_ON),
  //   ZM_TRACK_MASK(4, ZM_TRACK_MASK_ON),
  //   ZM_TRACK_MASK(6, ZM_TRACK_MASK_ON),
  //   -1,
  // };
  // zm_mask_tracks(TrackMask);
  // #pragma endregion

  OnZMDChange(&ZMDs[0]);

  while(1) {
    if(P_ON) { zm_play_all(); }
    if(S_ON) { zm_stop_all(); }
    if(C_ON) { zm_cont_all(); }
    if(ESC_ON) { zm_stop_all(); break; }

    #if 1
    if(ONE_ON) { zm_solo_track(1); }
    if(TWO_ON) { zm_solo_track(2); }
    if(THREE_ON) { zm_solo_track(3); }
    if(FOUR_ON) { zm_solo_track(4); }
    if(FIVE_ON) { zm_solo_track(5); }
    if(SIX_ON) { zm_solo_track(6); }
    if(SEVEN_ON) { zm_solo_track(7); }
    if(EIGHT_ON) { zm_solo_track(8); }
    if(NINE_ON) { zm_solo_track(9); }
    if(ZERO_ON) { zm_solo_track(0); }
    #else
    if(ONE_ON || TWO_ON || THREE_ON || FOUR_ON || FIVE_ON || SIX_ON || SEVEN_ON || EIGHT_ON || NINE_ON || ZERO_ON) { zm_stop_all(); }
    if(ONE_ON) { short Track[] = { 1, -1 }; zm_play(Track); }
    if(TWO_ON) { short Track[] = { 2, -1 }; zm_play(Track); }
    if(THREE_ON) { short Track[] = { 3, -1 }; zm_play(Track); }
    if(FOUR_ON) { short Track[] = { 4, -1 }; zm_play(Track); }
    if(FIVE_ON) { short Track[] = { 5, -1 }; zm_play(Track); }
    if(SIX_ON) { short Track[] = { 6, -1 }; zm_play(Track); }
    if(SEVEN_ON) { short Track[] = { 7, -1 }; zm_play(Track); }
    if(EIGHT_ON) { short Track[] = { 8, -1 }; zm_play(Track); }
    if(NINE_ON) { short Track[] = { 9, -1 }; zm_play(Track); }
    if(ZERO_ON) { short Track[] = { 0, -1 }; zm_play(Track); } 
    #endif

    //!< 上下で ZMD 選択 (Select ZMD bu up down)
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

    B_LOCATE(0, 5);

    //!< 再生中の ZMD インデックス (ZMD index now playing)
    printf("ZMDIndex = %d / %d\n", ZMDIndex, ZMDIndexMax - 1);

    //!< 再生時間 (Play time)
    const int Time = zm_get_play_time();
    printf("%02d:%02d:%02d\n", ZM_HOUR(Time), ZM_MiNUTE(Time), ZM_SECOND(Time));
    puts("");

    //!< ZMSC の状態 (ZMSC status) cf) ZM_STAT.MAC
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

    //!< トラックワーク (Track work)
    {
      puts("Track work");
      #if 1
      const struct track_work* Work = (const struct track_work*)zm_get_play_work(0);
      #else
      const struct track_work* Work = (const struct track_work*)zm_get_play_work_se(0);
      #endif
      if(NULL != Work) {
        printf("\tp_step_time = %d\n", Work->p_step_time);
        printf("\tp_track_stat = %d\n", Work->p_track_stat);
        puts("");
      }
    }

    //!< バッファ情報 (Buffer information)
    {
      puts("Buffer information");
      const struct buffer_information* Buffer = (const struct buffer_information*)zm_get_buffer_information();
       if(NULL != Buffer) {
        printf("\ttrk_buffer_top = %d\n", Buffer->trk_buffer_top);
        printf("\ttrk_buffer_size = %d\n", Buffer->trk_buffer_size);
        printf("\ttrk_buffer_end = %d\n", Buffer->trk_buffer_end);
        puts("");
      }
    }

    //!< トラックチャンネル情報 (Track channel info)
    {
      puts("Playing");

      //!< Channel status
      int ChannelStatus[16 + 1];  
      zm_play_status_all_ch(ChannelStatus);
      printf("\tChannel = { ");
      for(int i=0;i<COUNTOF(ChannelStatus);++i) {
        if(-1 == ChannelStatus[i]) { break; }
        printf("%d(%d), ", ZM_GET_CHANNEL(ChannelStatus[i]), ZM_GET_DEVICE(ChannelStatus[i]));
      }
      puts("}");

      //!< トラック状態 (Track status)
      short TrackStatus[65535 + 1];
      zm_play_status_all_tr(TrackStatus);
      printf("\tTrack = { ");
      for(int i=0;i<COUNTOF(TrackStatus);++i) {
        if(-1 == TrackStatus[i]) { break; }
        printf("%d, ", TrackStatus[i]);
        //zm_atoi(TrackStatus[i]);
      }
      puts("}");
    }

    //!< イベントコールバック情報 (Events info)
    puts("");
    puts(EventStr);
  }

#pragma region ZMD
  //!< 解放 (Release)
  if(NULL != ZMDs) {
    int i = 0;
    while(NULL != ZMDs[i].Data) {
      free(ZMDs[i++].Data);
    }
    free(ZMDs);
  }
#pragma endregion
}

