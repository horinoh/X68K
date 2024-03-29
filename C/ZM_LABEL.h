#pragma once

#include <stdint.h>

//			.nlist
enum {
	n_of_split = 8	//!< 音色スプリットの最大ブロック数
};

//	.offset	0
//!< ---------------ARCC(AMOD)/ENHANCED VELOCITY SEQUENCE関連----------------------
struct arcc_param
{
	int16_t p_arcc_wf;		//!< .w ARCC波形タイプ					##
							//!< 　 プリセット波形:0〜7
							//!<    ユーザー波形:$8000+(0-32767))[2]
//!< #TODO
#if 0 
p_arcc_dpndpt:	ds.b	1	//!< .b ARCC振幅増減モードの加算量(-128〜[0]〜127)		##
p_arcc_dpt_tbl:	ds.b	8	//!< .b ARCC振幅値ﾃｰﾌﾞﾙ//!< 8 [0]				##
		ds.b	1
p_arcc_dpnspd:	ds.w	1	//!< .w ARECC振幅増減モードの振幅値加算周期([0]-32767)	!!
p_arcc_spd_tbl:	ds.w	8	//!< .w ARCCｽﾋﾟｰﾄﾞ値テーブル [mod_dflt]			!!
p_arcc_dpt_now:	ds.b	1	//!< .b ARCC現在の実行振幅値[0]
p_arcc_flg2:	ds.b	1	//!< .b ARCC動作フラグワーク 2
b_arcc_phase:	equ	0	//!< d0 ARCC波形位相([0]:Normal,[1]:Reverse)
b_arcc_syncok:	equ	7	//!< d7 ARCC波形接続可能か([0]:No,1:Yes)
p_arcc_mode:	ds.b	1	//!< .b MIDI ARCCモード([-1]:通常,0〜127:拡張)
p_arcc_omt:	ds.b	1	//!< .b 1/8 MODE,OPTIONAL MODEの省略ビットパターン[$01]
p_arcc_1st_dly:	ds.w	1	//!< .w ARCC初期ディレイ [0]
p_arcc_8st_tbl:	ds.w	8	//!< .w ARCCの振幅変化ディレイ
p_arcc_stp_tbl:	ds.w	8	//!< .w 各ポイントに置けるARCCステップ保存ワーク//!< 8(Fixed)
p_arcc_step2:	ds.w	1	//!< .w ARCC実行ｽﾃｯﾌﾟ
p_arcc_spd:	ds.w	1	//!< .w ARCCｽﾋﾟｰﾄﾞ
p_arcc_spd2:	ds.w	1	//!< .w ARCCﾋﾟｰﾄﾞﾜｰｸ
p_arcc_dly2:	ds.w	1	//!< .w ARCCﾃﾞｨﾚｲﾜｰｸ
p_arcc_level:	ds.w	1	//!< .w ARCCﾎﾟｲﾝﾄﾜｰｸ
p_arcc_o:	ds.w	1	//!< .w ARCC波形スタート値(ノコギリ波,三角波専用)
p_arcc_sw:	ds.b	1	//!< .b ARCCスイッチ					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_arcc_sw2:	ds.b	1	//!< .b ARCCスイッチ保存					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_arcc_chain:	ds.b	1	//!< .b ARCCの接続ﾌﾗｸﾞ
				//!<    (-1:波形接続完了,0:即接続可能,1:接続待機中,[2]:初回)
p_arcc_flg:	ds.b	1	//!< .b ARCC動作フラグワーク
b_arcc_first:	equ	0	//!< d0 ARCC初めてか違うか([0]:はじめて,1:違う)
b_arcc_dpn:	equ	1	//!< d1 ARCC振幅を増加減衰させるモード([0]:OFF,1:ON)
b_arcc_reset:	equ	2	//!< d2 ARCCのリセット要請([0]:No [1]:Yes)
b_arcc_wvsqrst:	equ	3	//!< d3 ARCC波形の値を休符の時も更新([0]:No,1:Yes)
b_arcc_wvsq:	equ	4	//!< d4 ARCC波形の値をキーオン毎に更新するモード([0]:OFF,1:ON)
b_arcc_rstsync:	equ	5	//!< d5 ARCC 休符時に同期するか(1:Yes,[0]:No)
b_vseq_gvnsync:	equ	6	//!< d6 VSEQ VELOCITYを与えられてる時も進行させるか([0]:no,1:yes)
b_arcc_tiesync:	equ	6	//!< d6 ARCC タイ時に同期するか(1:Yes,[0]:No)
b_arcc_sync:	equ	7	//!< d7 ARCC キーオン毎に同期するか([1]:Yes,0:No)
b_vseq_msrsync:	equ	7	//!< d7 VSEQ 小節線発見時にリセットするか(1:Yes,[0]:No)
p_arcc_last:	ds.b	1	//!< .b 前回出力したARCC値(MIDI)[-1]
p_arcc_reset:	ds.b	1	//!< .b ARCCのリセット値([0])
p_arcc_origin:	ds.b	1	//!< .b ARCC基準値([127])
p_arcc:		ds.b	1	//!< .b ARCCのコントロールナンバー([11]=Expression)
p_arcc_o_next:	ds.w	1	//!< .w 次にくる予定の波形開始点
p_arcc_step_next: ds.w	1	//!< .w 次にくる予定のステップ
p_arcc_spd_next:  ds.w	1	//!< .w 次にくる予定のスピード
p_wvam_start:	ds.l	1	//!< .l 波形メモリ開始アドレス
p_wvam_point:	ds.l	1	//!< .l 波形メモリ現在のポインタ
p_wvam_end:	ds.l	1	//!< .l 波形メモリ終了アドレス
		ds.b	1
p_wvam_lpmd:	ds.b	1	//!< .b 波形メモリループモード
p_wvam_lpst:	ds.l	1	//!< .l 波形メモリループ開始アドレス
p_wvam_lped:	ds.l	1	//!< .l 波形メモリループ終了アドレス
p_wvam_lptm:	ds.l	1	//!< .l 波形メモリループ回数(0=∞)
p_wvam_lptm2:	ds.l	1	//!< .l 波形メモリループ回数実行ワーク(0=∞)
p_alta_flg:	ds.b	1	//!< .b 波形メモリ反復モードフラグ
p_arcc_n:	ds.b	1	//!< .b ARCCﾃｰﾌﾞﾙﾎﾟｲﾝﾀ(-1,0〜7)
p_arcc_wf2:	ds.w	1	//!< .w 次にくる予定の波形タイプ[2]			!!
p_arcc_dpnrpt:	ds.w	1	//!< .w 振幅増減処理を何回行うか			!!
				//!<    (0〜32767,[0]:∞)
p_arcc_rndcnt:	ds.w	1	//!< .w 波形が何周したか(0-32767)		!!
p_arcc_dpntime:	ds.w	1	//!< .w 増減処理を何回行ったか(0-65535)	!!
p_arcc_syncnt:	ds.w	1	//!< .w 同期カウント	([1]〜65535)	##
p_arcc_syncnt2:	ds.w	1	//!< .w 同期カウント実行ワーク([1]〜65535)	##
		ds.l	16
		.even
#endif
};

// __arcc_len:	equ	arcc_param_end-arcc_param	//!< ARCC関連のワーク長
// //!< ---------------演奏トラックワークエリア--------------------------------------
// 	.offset	-128
// p_note:		ds.b	4//!< 16	//!< ノートオンテーブル
// 	.offset	0

struct track_work
{
//!< ---------------基本パラメータ------------------------------------------------
	int16_t p_step_time;			//!< .w ステップタイム
	int8_t 	p_track_stat;			//!< .b トラックステータス					$
									//!< ($00:演奏中 $80:死亡 $01:終了
									//!<  $02:停止中 $40:同期待ち)
#if 0
p_track_mode:	ds.b	1	//!< .b トラックモード($80:Keyoff無し $00:通常)		$
p_trkfrq:	ds.b	1	//!< .b 割り込み頻度(マスタワーク)				$
p_trkfrq_wk:	ds.b	1	//!< .b 割り込み頻度(実行ワーク)				$
p_type:		ds.w	1	//!< .w 音源種別					!!
				//!< (FM:0 ADPCM:1 MIDI1〜4:$8000〜$8003
				//!<  PATTERN:$7fff)
p_ch:		ds.w	1	//!< .w チャンネル番号(0〜32767)			!!
p_data_pointer:	ds.l	1	//!< .l 現在のコマンドポインタアドレス	#
p_now_pointer:	ds.l	1	//!< .l 現在実行中のCMDのアドレス		#
//!< ---------------アフタータッチシーケンス関連----------------------------------
p_trk_seq_flg:	ds.b	1	//!< .b [0]
b_vseq_done:	equ	7	//!< d7 vseqを一度の割り込み処理で何度もしないためのフラグ[0]
b_loop_done:	equ	6	//!< d6 [do]-[loop]を無限に繰り返すのを防止するフラグ[0]
p_aftc_n:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽのポインタ(-1,0〜7)
p_aftc_omt:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ省略フラグ[0]		##
p_aftc_rltv:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ相対値フラグ[0]		##
p_aftc_flg:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ動作フラグ[0]		##
b_aftc_first:	equ	0	//!< d0 ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ 初めてか違うか([0]:はじめて 1:違う)
b_aftc_rstsync:	equ	5	//!< d5 ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ 休符時に同期するか(1:Yes,[0]:No)
b_aftc_tiesync:	equ	6	//!< d6 ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ タイ時に同期するか(1:Yes,[0]:No)
b_aftc_sync:	equ	7	//!< d7 ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ キーオン毎に同期するか([1]:Yes,0:No)
p_aftc_level:	ds.b	1	//!< .b 現在実行中のアフタータッチ値[-1]	##
p_aftc_tbl:	ds.b	8	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ値テーブル//!< 8
p_aftc_sw:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽのｽｲｯﾁ
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)	!!
p_aftc_sw2:	ds.b	1	//!< .b ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽのｽｲｯﾁ保存ワーク
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONALMODE ON)	!!
p_aftc_1st_dly:	ds.w	1	//!< .w ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽ初期ディレイ[0]				!!
p_aftc_8st_tbl:	ds.w	8	//!< .w ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽﾃﾞｨﾚｲ値//!< 8
p_aftc_dly2:	ds.w	1	//!< .w ｱﾌﾀｰﾀｯﾁｼｰｹﾝｽﾃﾞｨﾚｲﾜｰｸ
p_aftc_syncnt:	ds.w	1	//!< .w 同期カウント	([1]〜65535)	##
p_aftc_syncnt2:	ds.w	1	//!< .w 同期カウント実行ワーク([1]〜65535)	##
		ds.l	1
//!< ---------------ピッチモジュレーション関連----------------------------------
pmod_param:
p_pmod_dpndpt:	ds.w	1	//!< .w PMOD振幅増減モードの加算量(-32768〜[0]〜32767)	##
p_pmod_dpt_tbl:	ds.w	8	//!< 8w PMOD振幅値ﾃｰﾌﾞﾙ [0]					##
p_pmod_dpnspd:	ds.w	1	//!< .w PMOD振幅増減モードの振幅値加算周期([0]-32767)	!!
p_pmod_spd_tbl:	ds.w	8	//!< 8w PMODｽﾋﾟｰﾄﾞ値ﾃｰﾌﾞﾙ[mod_dflt]				!!
p_pmod_dpt_now:	ds.w	1	//!< .w PMOD現在の実行振幅値[0]
p_pmod_wf:	ds.w	1	//!< .w PMOD波形タイプ[2]				%%
				//!<    プリセット波形:0〜7
				//!<    ユーザー波形:$8000+(0-32767)
p_pmod_1st_dly:	ds.w	1	//!< .w PMOD初期ディレイ [0]			%%
p_pmod_8st_tbl:	ds.w	8	//!< 8w PMODの振幅変化ディレイ			%%
p_pmod_stp_tbl:	ds.l	8	//!< 8l PMOD加算ステップ値ﾃｰﾌﾞﾙ
				//!<    (波形タイプ=矩形波,ノイズ,波形メモリでは
				//!<     振幅値が格納される)
p_pmod_sw:	ds.b	1	//!< .b PMOD･ｽｲｯﾁ						!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_pmod_sw2:	ds.b	1	//!< .b PMOD･ｽｲｯﾁ保存					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_pmod_chain:	ds.b	1	//!< .b PMODの接続ﾌﾗｸﾞ
				//!<    (-1:波形接続完了,0:即接続可能,1:接続待機中,[2]:初回)
p_pmod_flg:	ds.b	1	//!< .b PMODの動作フラグ[0]
b_pmod_first:	equ	0	//!< d0 PMOD 初めてか違うか([0]:はじめて,1:違う)
b_pmod_dpn:	equ	1	//!< d1 PMOD 振幅を増加減衰させるモード([0]:OFF,1:ON)
b_pmod_syncok:	equ	2	//!< d2 PMOD 波形接続可能か([0]:No,1:Yes)
b_pmod_wvsqrst:	equ	3	//!< d3 PMOD 波形の値を休符の時も更新([0]:NO,1:YES)
b_pmod_wvsq:	equ	4	//!< d4 PMOD 波形の値をキーオン毎に更新するモード([0]:OFF,1:ON)
b_pmod_rstsync:	equ	5	//!< d5 PMOD 休符時に同期するか(1:Yes,[0]:No)
b_pmod_tiesync:	equ	6	//!< d6 PMOD タイ時に同期するか(1:Yes,[0]:No)
b_pmod_sync:	equ	7	//!< d7 PMOD キーオン毎に同期するか([1]:Yes,0:No)
p_pmod_mode:	ds.b	1	//!< .b MIDI PMODモード
				//!<    ([-1]:通常,0:FM互換拡張,1:MIDI互換拡張)
p_pmod_omt:	ds.b	1	//!< .b 1/8 MODE,OPTIONAL MODEの省略ビットパターン
				//!<    (振幅一個の時は[$01])
p_pitch_last:	ds.w	1	//!< .w 前回出力したベンダー値 [-1]
p_pmod_step2:	ds.l	1	//!< .l PMOD実行ｽﾃｯﾌﾟ(Fixed)
p_pmod_dly2:	ds.w	1	//!< .w PMOD･ﾃﾞｨﾚｲ実行ﾜｰｸ
p_pmod_spd:	ds.w	1	//!< .w PMOD･ｽﾋﾟｰﾄﾞ
p_pmod_spd2:	ds.w	1	//!< .w PMOD･ｽﾋﾟｰﾄﾞﾜｰｸ
p_pmod_pitch:	ds.l	1	//!< .l PMOD･ﾋﾟｯﾁﾜｰｸ(Fixed)
p_pmod_step_next: ds.l	1	//!< .l 次にくる予定のステップ
p_pmod_spd_next:  ds.w	1	//!< .w 次にくる予定のスピード
p_wvpm_start:	ds.l	1	//!< .l 波形メモリ開始アドレス
p_wvpm_point:	ds.l	1	//!< .l 波形メモリ現在のポインタ
p_wvpm_end:	ds.l	1	//!< .l 波形メモリ終了アドレス
		ds.b	1
p_wvpm_lpmd:	ds.b	1	//!< .b 波形メモリループモード
p_wvpm_lpst:	ds.l	1	//!< .l 波形メモリループ開始アドレス
p_wvpm_lped:	ds.l	1	//!< .l 波形メモリループ終了アドレス
p_wvpm_lptm:	ds.l	1	//!< .l 波形メモリループ回数(0=∞)
p_wvpm_lptm2:	ds.l	1	//!< .l 波形メモリループ回数実行ワーク(0=∞)
p_altp_flg:	ds.b	1	//!< .b 波形メモリ反復モードフラグ
p_pmod_n:	ds.b	1	//!< .b 8ﾎﾟｲﾝﾄ･PMOD･ﾃｰﾌﾞﾙﾎﾟｲﾝﾀ(-1,0〜7)
p_pmod_wf2:	ds.w	1	//!< .w PMOD実行波形タイプ					!!
				//!< プリセット波形:0〜7
				//!< ユーザー波形:$8000+(0-32767))[2]
p_pmod_dpnrpt:	ds.w	1	//!< .w 振幅増減処理を何回行うか(0〜32767,[0]:∞)		!!
p_pmod_rndcnt:	ds.w	1	//!< .w 波形が何周したか(0-32767)		!!
p_pmod_dpntime:	ds.w	1	//!< .w 増減処理を何回行ったか(0-65535)	!!
p_pmod_syncnt:	ds.w	1	//!< .w 同期カウント	([1]〜65535)	##
p_pmod_syncnt2:	ds.w	1	//!< .w 同期カウント実行ワーク([1]〜65535)	##
		ds.l	16
	.even
pmod_param_end:	ds.b	0
__pmod_len:	equ	pmod_param_end-pmod_param

p_arcc_param:	ds.b	__arcc_len//!< 4
p_vseq_param:	ds.b	__arcc_len
//!< ---------------ポルタメント&ディチューン関係----------------------------------
p_detune:	ds.w	1	//!< .w デチューン(オートベンドの開始値にもなる)[0]	!!
p_special_tie:	ds.w	1	//!< .w MIDI専用のスペシャル・タイ用ピッチワーク[0]	!!
p_port_dly:	ds.w	1	//!< .w ポルタメントディレイ[0]		!!
p_port_cnt:	ds.w	1	//!< .w ポルタメント継続時間[0]		!!
p_bend_dly:	ds.w	1	//!< .w ベンドディレイ値[0]				!!
p_bend_cnt:	ds.w	1	//!< .w ベンドテイル/ベンドタイム[0]		!!
p_port2_dly:	ds.w	1	//!< .w ｵｰﾄﾎﾟﾙﾀﾒﾝﾄディレイ[0]		!!
p_port2_cnt:	ds.w	1	//!< .w ｵｰﾄﾎﾟﾙﾀﾒﾝﾄテイル/ｵｰﾄﾎﾟﾙﾀﾒﾝﾄタイム[0]!!
p_port_pitch:	ds.l	1	//!< .l ﾎﾟﾙﾀﾒﾝﾄ/ｵｰﾄﾍﾞﾝﾄﾞ用
				//!<    現在のベンド値//!< 65536(Fixed)[0]
p_port_flg:	ds.b	1	//!< .b ﾎﾟﾙﾀﾒﾝﾄｵﾝかｵﾌか
				//!<    ([0]=OFF,1=Normal Delay,-1=Minus Delay)
p_port2_flg:	ds.b	1	//!< .b ｵｰﾄﾎﾟﾙﾀﾒﾝﾄｽｲｯﾁ([0]=OFF,1=ON)
p_bend_sw:	ds.b	1	//!< .b ｵｰﾄﾍﾞﾝﾄﾞがｵﾝかｵﾌか([0]=OFF,1=ON)
				//!<    d7:初めてか(bit=0:初めて)
p_agogik_flg:	ds.b	1	//!< .b アゴーギクビットワーク[0]
b_agogik_trmk:	equ	0	//!< d0 Agogik主導権フラグ([0]=No/1=Yes)
b_agogik_msrsync: equ	2	//!< d2 Agogik 小節線発見時にリセットするか(1:Yes,[0]:No)
b_agogik_wvsqrst: equ	3	//!< d3 Agogik 波形の値を休符の時も更新
				//!<    ([0]:No,1:Yes)
b_agogik_wvsq:	  equ	4	//!< d4 Agogik 波形の値をキーオン毎に更新するモード
				//!<    ([0]:OFF,1:ON)
b_agogik_rstsync: equ	5	//!< d5 Agogik 休符時に同期するか(1:Yes,[0]:No)
b_agogik_tiesync: equ	6	//!< d6 Agogik タイ時に同期するか(1:Yes,[0]:No)
b_agogik_sync:	equ	7	//!< d7 Agogik キーオン毎に同期するか(1:Yes,[0]:No)
p_bend_dst:	ds.w	1	//!< .w オートベンドのレンジ(オートベンドの目的値となる)[0]
		ds.w	1	//!< .w 
p_port_step:	ds.l	1	//!< .l ポルタメント用実行ステップ//!< 65536
		ds.l	16
//!< ----------------一般パラメータ-------------------------------------------------
p_measure:	ds.l	1	//!< .l 現在の小節番号[0]

p_voice_rsv:	ds.w	1	//!< .w FM/ADPCM音源トラックのボイスリザーブ数
				//!<    ([0]〜7)
p_next_on:	ds.b	1	//!< .b FM/ADPCM音源トラックの次回の発音チャンネル
				//!<    [0]
p_timbre_set:
pts_bank:	equ	7	//!< d7:Bank Selectの設定が行われたか(MIDI)
pts_program:	equ	6	//!< d6:Programチェンジが行われたか(MIDI)
pts_volume:	equ	5	//!< d5:Volume設定が行われたか(MIDI)
pts_panpot:	equ	4	//!< d4:Panpot設定が行われたか(MIDI)
pts_damper:	equ	3	//!< d3:Damper設定が行われたか(MIDI)
p_tone_set:	ds.b	1	//!< .b 第nﾋﾞｯﾄをチャンネルnとして
				//!<    音色を設定したかどうかのフラグ(FM)[0]

p_return:	ds.l	1	//!< .l gosubの次のアドレス[0]

p_transpose:	ds.b	1	//!< .b キートランスポーズ[0]
p_mask_mode:	ds.b	1	//!< .b Mask Modeかどうか([0]=Normal,1=Masked)			!!
p_damper:	ds.b	1	//!< .b damper on or off ([0]〜63:OFF/64〜127:ON)
p_seq_flag:	ds.b	1	//!< .b []コマンド系の処理フラグビットパターン[0]
				//!< d0:[D.C.]処理をしたことがあるか([0]=no/1=yes)
				//!< d1:[FINE]処理をすべきかどうか([0]=no/1=yes)
				//!< d2:[!]フラグ([0]=OFF/1=実行中)
p_bank_msb:	ds.b	1	//!< .b MIDI Bank MSB [-1]	!!
p_bank_lsb:	ds.b	1	//!< .b MIDI Bank LSB [-1]	!!
p_pgm:		ds.w	1	//!< .w Program Number([0]-32767)	!!

p_sync_wk:	ds.b	1	//!< .b 強制同期コマンド用ワーク[1]
p_@b_range:	ds.b	1	//!< .b ベンドレンジ[12]
p_vol16:	ds.b	1	//!< .b 16段階音量(0-16),[-1]=無効(127段階音量モード)
p_velo16:	ds.b	1	//!< .b 16段階ベロシティ(0-16),[-1]=無効
				//!<    (127段階ベロシティモード)
p_do_loop_flag:	ds.b	1	//!< .b [DO]が以前に設定されているか
				//!<    [0]=NO/ループ回数(1〜255)
p_md_flg:	ds.b	1	//!< .b 各種ビットワーク[0]
b_bend_reset:	equ	0	//!< d0 @B:ﾍﾞﾝﾄﾞ値をﾘｾｯﾄすべきかどうか
				//!<    (MIDI専用 [0]=No/1=Yes)
b_pmod_reset:	equ	1	//!< d1 @M:ﾓｼﾞｭﾚｰｼｮﾝ値をﾘｾｯﾄするかしないか
				//!<    (MIDI専用 [0]=No/1=Yes)
				//!<    ↑(それぞれ関係CTRLに0以外の値を
				//!<       出力した時にビットが1になる)
b_vtune_mode:	equ	2	//!< d2 ADPCM Variable Tuning Mode ([0]:NOT)
b_slot_mask:	equ	3	//!< d3 OPMスロットマスクの切り換え
b_tie_mode:	equ	4	//!< d4 MIDI Tie Mode([0]:Normal,1:Special)
b_voice_rsv:	equ	5	//!< d5 FM/ADPCMでVoice Reserveを行ったか([0]:No/1:Yes)
b_split_mode:	equ	7	//!< d7 音色スプリットモード([0]:OFF,1:ON
p_how_many:	ds.b	1	//!< .b 今何音キーオンしているか
				//!<    ([-1]:None/0〜7:1〜8)
p_last_note:	ds.b	1	//!< .b 前回発音したノート番号([-1])
//!< ---------------MIDI専用関係----------------
p_maker:	ds.b	1	//!< .b ﾒｰｶｰID(MIDI)[-1]
p_device:	ds.b	1	//!< .b ﾃﾞﾊﾞｲｽID(MIDI)[-1]
p_module:	ds.b	1	//!< .b ﾓｼﾞｭｰﾙID(MIDI)[-1]
p_effect1:	ds.b	1	//!< .b Effect Parameter 1(GS:RVB)	[-1]
p_effect3:	ds.b	1	//!< .b Effect Parameter 3(GS:CHO)	[-1]
p_effect4:	ds.b	1	//!< .b Effect Parameter 4(GS:DLY)	[-1]
p_effect2:	ds.b	1	//!< .b Effect Parameter 2	[-1]
p_effect5:	ds.b	1	//!< .b Effect Parameter 5	[-1]
//!< ----------------一般パラメータ-------------
p_timbre_src:	ds.b	1	//!< .b 音色のコピー元チャンネルオフセット(FM:0-7)
p_sync:		ds.b	1	//!< .b OPM-LFOのシンクスイッチ(0=off,1=on)		!!
p_om:		ds.b	1	//!< .b オペレータマスク(&b0000-&b1111)		!!
		ds.b	1

p_vol:		ds.b	1	//!< .b 127段階音量(0-127)	[??]		!
p_velo:		ds.b	1	//!< .b ベロシティ(0-[127])			!
p_frq:		ds.b	1	//!< .b ADPCMの周波数(0-6)	[4]		!
p_pan:		ds.b	1	//!< .b Last PANPOT(0〜127,-1=MUTE)[64]	!

p_onoff_bit:	ds.b	1	//!< キーオン／オフビットワーク
b_keyon:	equ	7	//!< d7:Key ONのときにbit=1が上書きされる
b_keyoff:	equ	6	//!< d6:Key OFFのときにbit=1が上書きされる
p_om_bak:	ds.b	1	//!< .b p_omのバックアップ
p_Q_gate:	ds.w	1	//!< .w Qコマンドの値(CONVERTER専用)
				//!<    (0-256:NORMAL Q,負値:@Q)
p_midi_if:	ds.w	1	//!< .w ユーザからみたMIDIインターフェース番号(0-3)

p_do_loop_ptr:	ds.l	1	//!< .l [do]のある位置
p_int_play_ope:	ds.l	1	//!< .l 演奏処理ﾙｰﾁﾝｱﾄﾞﾚｽ
				//!<    通常はソースZMSC2.HAS中のint_play_ope_fm,
				//!<    int_play_ope_ad,int_play_ope_midi
p_opmset:			//!< .l OPMアクセスルーチン(FM)
p_midi_trans:	ds.l	1	//!< .l MIDI送信ルーチン(MIDI)

p_total:	ds.l	1	//!< .l トータルステップタイム
p_total_olp:	ds.l	1	//!< .l ﾙｰﾌﾟ外のﾄｰﾀﾙｽﾃｯﾌﾟｲﾑ

pst_split_len:	equ	6
p_split_tbl:			//!< .l 音色スプリットの管理ワーク
		ds.b	pst_split_len//!< n_of_split
pst_split_st:	equ	0	//!< .b 割り当てる開始ノートナンバー(0-127,128で残り全部)
pst_split_ed:	equ	1	//!< .b 割り当てる終端ノートナンバー(0-127,128で残り全部)
pst_split_bank:	equ	2	//!< .w 割り当てるBANK番号(MIDI:0-16383/FM,ADPCM:0-255)
pst_split_pgm:	equ	4	//!< .w 割り当てる音色番号(MIDI:0-127/FM,ADPCM:0-127 or 0-32767)

p_lfo_param:			//!< 以下２バイトペアワーク
p_pitch_param:	ds.w	1	//!< 音程関係の特殊処理フラグ
p_level_param:	ds.w	1	//!< 音量関係の特殊処理フラグ
p_key_on:	ds.l (16+1)//!< 2	//!< これから発音する音の note.b,velocity.b,
				//!< ch offset(.w),prog(.l)が格納される。
				//!< ただしch offsetはFM/ADPCMのみで有効、
				//!< MIDIでは常に0
pko_note:	equ	0
pko_velo:	equ	1
pko_offset:	equ	2
pko_prog:	equ	4
pko_size:	equ	8
		ds.b	64
p_user:		ds.b	1	//!< .b ユーザー汎用ワーク
#endif
};

// track_work_size:	equ	track_work_end-track_work+128	//!< 現在の実際使用量
// trwk_size:		equ	2048	//!< 各トラックの演奏時のワークサイズ(変更不可)
// trwk_size_:		equ	11	//!< ワークサイズが２の何乗か(変更不可)

// 	.offset	0
// k_note		ds.b	1	//!< .b ノートオンしたノートナンバー[-1]
// 				//!<    (実際にKey OFFされるとd7=1)
// k_velo:		ds.b	1	//!< .b 発音ベロシティ[-1]
// 				//!<    (ゲートタイムが0になるとd7=1)
// k_gate_time:	ds.w	1	//!< .w gate time[?]
// 				//!<    (tieは1回の割り込み内では0,
// 				//!<     割り込みを出ると-1,-2は無限ゲート)
// k_note_len:	ds.b	0
	