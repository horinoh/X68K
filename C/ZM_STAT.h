#pragma once
#include <stdint.h>

enum {
	b_tma_flg = 0,		        //!< (d7はFUNC INTERCEPT_PLAYが有効時にm_playが実行されると
    b_tmb_flg = 1,		        //!< 1に上書きされる。外部アプリ向け専用ワークビット)
    b_tmm_flg = 2,	
};

enum {
	fd_wkl = 8,		//!< ワーク長
	fd_wkl_ = 3,	//!< 2の何乗か
	fd_spd2	= 0,	//!< スピード実行ワーク(.w)
	fd_spd = 2,		//!< スピード値(.w)
	fd_lvlw	= 4,	//!< フェーダーレベル(.w)
	fd_lvlb	= 5,	//!< フェーダーレベル(.b)
	fd_dest	= 6,	//!< 目的値(.b)
	fd_mode	= 7,	//!< フェーダーモード(.b)	(-1,+1,nn)
};

enum {
	fcf_ch = 0,
	fcf_master = 1,
};

struct zmusic_stat
{
    int8_t midi_board;          //!< MIDI I/F有効フラグ
					            //!< d0〜d3がそれぞれCZ6BM1 #1,#2,RS232C-MIDI A,Bに対応
    int8_t available_device;    //!< 実際に使用するデバイスフラグ(midi_boardと同じ書式)
    int8_t timer_flg;	        //!< TIMER ON/OFF(d0TIMER A,d1TIMER B,d2YM3802 TIMER)
	int8_t dummy0;	            //!< dummy
    int16_t wk_size;  			//!< 1トラックワークのサイズ
    int32_t play_start_time;	//!< 演奏開始時刻 (10時23分52秒ならば$00102352,初期値=-1)!
    int32_t play_stop_time;    	//!< 演奏停止時刻 (10時23分52秒ならば$00102352,初期値=-1)!
    int32_t play_cont_time;    	//!< 演奏再開時刻 (10時23分52秒ならば$00102352,初期値=-1)!
    int32_t dev_end_adr;        //!< ZMSC3.X最終アドレス
    int16_t t_min;             	//!< 音楽演奏用テンポの最小値	(デフォルト値はMIDI  !!
    int16_t t_max;          	//!< 音楽演奏用テンポの最大値	14bitタイマが        !!
    int16_t t_min_se;          	//!< 効果音演奏用テンポの最小値	採択された時の場合)  !!
    int16_t t_max_se;        	//!< 効果音演奏用テンポの最大値			     !!
    int16_t _t_max;       		//!< 音楽演奏用タイマ値の最大値
    int16_t _t_max_se;      	//!< 効果音演奏用タイマ値の最大値
    int16_t mask_opm_ch;        //!< FM音源のマスクチャンネル対応ビット
					        	//!< d0〜d7がチャンネル1〜8に対応。対応ビット=1Masked
    int16_t se_tr_max;          //!< 効果音の最大トラック数[0]

	//!< #TODO ...
#if 0
int8_t ext_pcmdrv		dc.b	0	//!< 外部PCMドライバ([0]NO 1組み込まれている)
int8_t current_rs232c_part	dc.b	1	//!< RS232Cの現在の選択パート
					//!< 0PART A,$FFPART B,[1]未定義
int16_t current_midi_in_r	dc.w	-1	//!< カレント相対I/F番号(USERから見た0-3)
int8_t current_midi_in_w	dc.b	-1	//!< 通常は常時0
int8_t current_midi_in_b	dc.b	-1	//!< カレント絶対I/F番号(内部で使用する(0-3)//!< 2)
int16_t current_midi_out_r	dc.w	-1	//!< カレント相対I/F番号(USERから見た0-3)
int8_t current_midi_out_w	dc.b	-1	//!< 通常は常時0
int8_t current_midi_out_b	dc.b	-1	//!< カレント絶対I/F番号(内部で使用する(0-3)//!< 2)
int8_t midi_if_tbl		dcb.b	8+1,-1	//!< MIDIインターフェースの使用設定
					//!< (0CZ6BM1-1,2CZ6BM1-2,4RS232C-A,6RS232C-B,-1なし)
					//!< 未使用IFも$80+(0,2,4,6)として格納されている
int8_t ch_wk_mode		dc.b	-1	//!< チャンネルワークの使用状態
					//!< -1=全部(DEFAULT),0=FM無し(通常禁止)
					//!< 1=MIDI無し,2=全部無し(通常禁止)
int8_t gs_id		dc.b	$10,$10,$10,$10	//!< DEVICE IDデフォルト値
int8_t 		ds.b	4		//!< Reserved
int8_t sc88_id	dc.b	$10,$10,$10,$10
int8_t 		ds.b	4		//!< Reserved
int8_t mt32_id	dc.b	$10,$10,$10,$10	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t u220_id	dc.b	$10,$10,$10,$10	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t m1_id		dc.b	$30,$30,$30,$30	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t adpcm_frq	dc.b	0		//!< ADPCM周波数					!!
int8_t adpcm_pan	dc.b	0		//!< ADPCMパンポット				!!
int8_t adpb_clr	dc.b	0		//!< ADPCMバッファ初期化有無フラグ(0以外=要初期化)	!!
int8_t wvmm_clr	dc.b	0		//!< 波形メモリバッファ初期化有無フラグ(0以外=要初期化)!!

int16_t meter		dc.w	$0404		//!< 拍子					##
int8_t metronome	dc.b	0		//!< Reserve				##
int8_t 		dc.b	0		//!< Reserve				##
int16_t key		dc.w	0		//!< 調号					##
int16_t mst_clk	dc.w	192		//!< 全音符の絶対音長カウント		##
int16_t tempo_value	dc.w	120		//!< テンポ値(DEFAULT=120)			##順番変更禁止
int16_t timer_value	dc.w	0		//!< タイマの値				##

int16_t meter_se	dc.w	$0404		//!< 拍子(効果音サイド)			!!
int8_t metronome_se	dc.b	0		//!< Reserved				!!
int8_t 		dc.b	0		//!< Reserved				!!
int16_t key_se		dc.w	0		//!< 調号					!!
int16_t mst_clk_se	dc.w	192		//!< 全音符の絶対音長カウント(効果音サイド)	!!
int16_t tempo_value_se	dc.w	120		//!< テンポ値(DEFAULT=120)			!!順番変更禁止
int16_t timer_value_se	dc.w	0		//!< タイマの値				!!
int16_t eox_w		dcb.w	8,3		//!< EOXウェイト(DEFAULT=3)
int8_t se_mode	dc.b	0		//!< ADPCMの効果音モードか(0=NO,0以外=YES)
int8_t fader_flag	dc.b	0		//!< 現在実行中のフェーダー
					//!< (d7マスターフェーダー,d6チャンネルフェーダー)
					//!< 実行中のフェーダーに対応したビット=1で
					//!< そのフェーダーが可動中
int16_t fnc_no		dc.w	$7fff		//!< 最後に実行した(あるいは現在実行中の)ﾌｧﾝｸｼｮﾝ番号
int16_t sr_type	dc.w	$2500		//!< SRをマスクする際のデフォルト値(普通は書き変わる)
int32_t sp_buf		dc.l	0		//!< ファンクション実行時のスタック保存ワーク
int32_t fnc_quit_addr	dc.l	0		//!< 緊急帰還アドレス(エラーが発生した場合の脱出アドレス)
int32_t opmset_bsr_ms	dc.l	0		//!< FM音源ｱｸｾｽﾙｰﾁﾝｱﾄﾞﾚｽ(通常opmset,効果音MODEopmset_se)
int16_t timer_mode	dc.b	0		//!< どのタイマーを使うか
					//!< タイマA-1,タイマB0,YM3802タイマ1,$f8-In2
int16_t synchro_mode	dc.b	0		//!< 外部同期モードか(0=NO,$FF=YES)
int16_t polypress_mode	dc.b	-1		//!< ポリフォニックプレッシャーモード([-1]ON,0=NO)
int16_t no_init_mode	dc.b	0		//!< 初期化無しモードか([0]=NO,0以外=YES)
int32_t zmusic_int	dc.l	0		//!< ZMUSICが割り込むとインクリメントされる
int32_t last_zmusic_int	dc.l	0	//!< 前回MIDI_INP1を実行したときのzmusic_intの値
int8_t zpd_last_fn	ds.b	54		//!< 前回読み込んだファイルの名前
int8_t header_buffer	ds.b	8		//!< ファイルID用バッファ
int32_t fm_tune_tbl	dc.l	0		//!< FM音源周波数調整テーブル
int32_t pcm_tune_tbl	dc.l	0		//!< PCM音源周波数調整テーブル
int16_t occupy_flag	dc.b	0		//!< 占有状態(0=FREE,1=占有されている)
int16_t itpl_rate	dc.b	0		//!< 外部同期時の補間レート(1-15)	格納値はYM3802-R75書式
int16_t errmes_lang	dc.b	0		//!< メッセージ表示言語([0]English,1Japanese)
int16_t external_applications	dc.b	0	//!< 外部アプリの常駐状況
					//!< d7ZP -d,d6ZP -j
					//!< 対応ビット=1の時そのアプリケーションが
					//!< 組み込まれている
int16_t smf_end_flag	dc.b	0		//!< SMF 転送終了フラグ
int16_t rs232c_mode	dc.b	0		//!< RS232C-MIDIのモード
					//!< d7=(0通常,1デュアル)
					//!< d0-d3ボーレート時定数[3]
int16_t perform_flg	dc.b	0		//!< ZM_PLAY,ZM_CONT,ZM_STOPのファンクションが
					//!< 実行されるたびに対応ビットが1に上書きされる。
					//!< d0PLAY d1CONT d2STOP
					//!< d7loop mode(0normal 1no loop/FUNC $59参照)
int16_t zmsc_mode	dc.b	3		//!< ZMUSIC動作モード(2V2,[3]V3)

		.even
fm_vol_tbl	dcb.b	16,$ff		//!< フェードアウト/イン用の音量ワーク
ad_vol_tbl	dcb.b	16,$ff
m0_vol_tbl	dcb.b	16,$ff
m1_vol_tbl	dcb.b	16,$ff
mr0_vol_tbl	dcb.b	16,$ff
mr1_vol_tbl	dcb.b	16,$ff

// fd_wkl		equ	8		//!< ワーク長
// fd_wkl_	equ	3		//!< 2の何乗か
// fd_spd2	equ	0		//!< スピード実行ワーク(.w)
// fd_spd		equ	2		//!< スピード値(.w)
// fd_lvlw	equ	4		//!< フェーダーレベル(.w)
// fd_lvlb	equ	5		//!< フェーダーレベル(.b)
// fd_dest	equ	6		//!< 目的値(.b)
// fd_mode	equ	7		//!< フェーダーモード(.b)	(-1,+1,nn)

// fcf_ch			equ	0
// fcf_master		equ	1

//!< 以下spd,spd2,lvlw,lvlb系のワークの配置はzmsc2.hasの都合に合わせてある
					//!< マスターフェーダーパラメータ群
int16_t mstfd_fm_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_fm_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_fm_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_fm_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_fm_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_fm_mode	ds.b	1		//!< フェーダーモード(.b)

int16_t mstfd_ad_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_ad_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_ad_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_ad_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_ad_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_ad_mode	ds.b	1		//!< フェーダーモード(.b)

int16_t mstfd_m0_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_m0_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_m0_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_m0_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_m0_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_m0_mode	ds.b	1		//!< フェーダーモード(.b)

int16_t mstfd_m1_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_m1_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_m1_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_m1_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_m1_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_m1_mode	ds.b	1		//!< フェーダーモード(.b)

int16_t mstfd_mr0_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_mr0_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_mr0_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_mr0_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_mr0_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_mr0_mode	ds.b	1		//!< フェーダーモード(.b)

int16_t mstfd_mr1_spd2	ds.w	1		//!< スピード実行ワーク(.w)
int16_t mstfd_mr1_spd	ds.w	1		//!< スピード値(.w)
int8_t mstfd_mr1_lvlw	ds.b	1		//!< フェーダーレベル(.w)
int8_t mstfd_mr1_lvlb	ds.b	1		//!< フェーダーレベル(.b)
int8_t mstfd_mr1_dest	ds.b	1		//!< 目的値(.b)
int8_t mstfd_mr1_mode	ds.b	1		//!< フェーダーモード(.b)

int8_t ch_fm_fdp	ds.b	fd_wkl//!< 16	//!< チャンネルフェーダーパラメータ群
int8_t ch_ad_fdp	ds.b	fd_wkl//!< 16	//!< (1ch8byte構成//!< 16ch分)
int8_t ch_m0_fdp	ds.b	fd_wkl//!< 16
int8_t ch_m1_fdp	ds.b	fd_wkl//!< 16
int8_t ch_mr0_fdp	ds.b	fd_wkl//!< 16
int8_t ch_mr1_fdp	ds.b	fd_wkl//!< 16

int16_t ch_fader_tbl	ds.w	96	//!< チャンネルフェーダー
				//!< (フェード処理するチャンネル番号0-95が並ぶ)
int16_t		dc.w	-1	//!< End code
master_fader_tbl		//!< マスターフェーダー
				//!< (フェード処理するデバイス番号//!< fd_wklが並ぶ)
int16_t 		ds.w	6	//!< 0,8,16,24,32,40 
int16_t		dc.w	-1	//!< End code

int16_t ch_mask_fm	dc.w	0		//!< チャンネルフェーダービットワーク
int16_t ch_mask_ad	dc.w	0
int16_t ch_mask_m0	dc.w	0
int16_t ch_mask_m1	dc.w	0
int16_t ch_mask_mr0	dc.w	0
int16_t ch_mask_mr1	dc.w	0
		.even
int8_t agogik_work		ds.b	__pmod_len	//!< 音楽演奏用アゴーギクワーク
int8_t agogik_work_se		ds.b	__pmod_len	//!< 効果音演奏用アゴーギクワーク
		.even
mpcm_vol_tbl					//!< MPCM用音量テーブル64=原音レベル
	dc.w	   0,   3,   6,   9,  12,  15,  18,  21
	dc.w	  24,  25,  26,  27,  28,  29,  30,  31
	dc.w	  32,  33,  34,  35,  36,  37,  38,  39
	dc.w	  40,  41,  42,  43,  44,  45,  46,  47
	dc.w	  48,  50,  52,  54,  56,  58,  60,  62
	dc.w	  64,  66,  68,  70,  72,  74,  76,  78
	dc.w	  80,  82,  84,  86,  88,  90,  92,  94
	dc.w	  96, 100, 104, 108, 112, 116, 120, 124
	dc.w	 128, 132, 136, 140, 144, 148, 152, 156
	dc.w	 160, 164, 168, 172, 176, 180, 184, 188
	dc.w	 192, 200, 208, 216, 224, 232, 240, 248
	dc.w	 256, 264, 272, 280, 288, 296, 304, 312
	dc.w	 320, 328, 336, 344, 352, 360, 368, 376
	dc.w	 384, 400, 416, 432, 448, 464, 480, 496
	dc.w	 512, 528, 544, 560, 576, 592, 608, 624
	dc.w	 640, 656, 672, 688, 704, 720, 736, 752
nof_result		equ	5
_result_start				//!< 戻り値バッファ
int32_t mask_track_result	ds.l	1	//!< 4//!< (trk_n_max+1) bytes
int32_t mask_channel_result	ds.l	1	//!< 4//!< (trk_n_max+1) bytes
int32_t m_play_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes
int32_t m_stop_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes
int32_t m_cont_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes

					//!< SMF再生関連ワーク
int32_t smf_delta	ds.l	1		//!< SMF デルタタイム
int32_t smf_running	ds.l	1		//!< SMFランニングステータスカウンタ
int32_t smf_pointer	ds.l	1		//!< SMF データポインタ
int32_t smf_transfer	ds.l	1		//!< SMF MIDI送信エントリ
int32_t smf_mst_clk	ds.l	1		//!< SMFマスタークロック
int32_t smf_addr	ds.l	1		//!< SMFの格納アドレス

int8_t fo_ch_fm	ds.b	8		//!< フェードアウト/インのワーク
int8_t 		ds.b	8		//!< DUMMY
int8_t fo_ch_ad	ds.b	16		//!< d0ch fader active flag	01
int8_t fo_ch_m0	ds.b	16		//!< d1master fader active flag	02
int8_t fo_ch_m1	ds.b	16		//!< d5master fader move flag	20
int8_t fo_ch_mr0	ds.b	16		//!< d6ch fader move flag		40
int8_t fo_ch_mr1	ds.b	16		//!< d7処理したかどうか		80
work
int32_t pt_ptr		ds.l	1		//!< play_trk_tblの指標	必ずwork=pt_ptr
int32_t pt_ptr_se	ds.l	1		//!< play_trk_tbl_seの指標
int8_t cf	ds.b	8	//!< オペレータのコネクションテーブルビット	!
int8_t ol1	ds.b	8	//!< アウトプットレベル1			!
int8_t ol2	ds.b	8	//!< アウトプットレベル2			!
int8_t ol3	ds.b	8	//!< アウトプットレベル3			!
int8_t ol4	ds.b	8	//!< アウトプットレベル4			!
int8_t opm_kon	ds.b	8		//!< OPMレジスタ8番のワーク
int8_t opm_nom	ds.b	8		//!< オペレータマスク(OM)のNOT(&b11110000-&b11111111)
int8_t _opm		ds.b	256		//!< OPMのレジスタ・イメージ・ワーク
int16_t opm_pmd	dc.b	0
opmreg		equ	_opm-work
AF		equ	$20
#endif
};
