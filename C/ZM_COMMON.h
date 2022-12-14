#pragma once

#include <stdint.h>

struct buffer_information
{
	int32_t trk_buffer_top;			//!< トラックバッファ先頭アドレス
	int32_t trk_buffer_size;		//!< トラックバッファサイズ
	int32_t trk_buffer_end;			//!< トラックバッファ最終アドレス

	//!< #TODO
#if 0
adpcm_buffer_top:	ds.l	1	//!< (AD)PCMバッファ先頭アドレス
adpcm_buffer_size:	ds.l	1	//!< (AD)PCMバッファサイズ
adpcm_buffer_end:	ds.l	1	//!< (AD)PCMバッファ最終アドレス
wave_memory_top:	ds.l	1	//!< 波形メモリバッファ先頭アドレス
wave_memory_size:	ds.l	1	//!< 波形メモリバッファサイズ
wave_memory_end:	ds.l	1	//!< 波形メモリバッファ最終アドレス
seq_wk_tbl:		ds.l	1	//!< 音楽演奏トラックワーク先頭アドレス
seq_wk_tbl_se:		ds.l	1	//!< 効果音演奏トラックワーク先頭アドレス
play_trk_tbl:		ds.l	1	//!< どのトラックを演奏するのかを表すテーブル
play_trk_tbl_se:	ds.l	1	//!< どのトラックを演奏するのかを表すテーブル(効果音)
adpcm_tbl:		ds.l	1	//!< (AD)PCMトーンのアドレステーブル[0]	!!
adpcm_n_max:		ds.w	1	//!< 定義できる最大トーン数[0]		!!
adpcm_tbl2:		ds.l	1	//!< (AD)PCM音色のアドレステーブル[0]	#
adpcm_n_max2:		ds.w	1	//!< 定義できる最大音色数[0]		#
wave_tbl:		ds.l	1	//!< 波形メモリデータのテーブルアドレス
wave_n_max:		ds.w	1	//!< 波形メモリの定義最大個数
fmsnd_buffer:		ds.l	1	//!< FM音色バッファ
fmsnd_n_max:		ds.w	1	//!< FM音色バッファの定義最大個数
lyric_address:		ds.l	1	//!< 歌詞文字列データアドレス
lyric_size:		ds.l	1	//!< 歌詞文字列データサイズ
					//!< (文字列は0で終わらない場合有り)
trk_po_tbl:		ds.l	1	//!< 各トラックの先頭アドレス格納テーブルアドレス
trk_po_tbl_se:		ds.l	1	//!< 各トラックの先頭アドレス格納テーブルアドレス
trk_n_max:		ds.w	1	//!< トラックの個数
pattern_trk:		ds.l	1	//!< パターントラックアドレス[0]
pattern_trk_se:		ds.l	1	//!< パターントラックアドレス効果音[0]
m_buffer_0:		ds.l	1	//!< CZ6BM1-0用の送信バッファ
m_buffer_1:		ds.l	1	//!< CZ6BM1-1用の送信バッファ
m_buffer_r:		ds.l	1	//!< RS232C-MIDI用の送信バッファ
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
rec_buffer_0:		ds.l	1	//!< CZ6BM1-0用の受信バッファ
rec_buffer_1:		ds.l	1	//!< CZ6BM1-1用の受信バッファ
rec_buffer_r:		ds.l	1	//!< RS232C-MIDI用の受信バッファ
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
mm0_adr:		ds.l	1	//!< CZ6BM1-0用のチャンネルワーク
mm1_adr:		ds.l	1	//!< CZ6BM1-1用のチャンネルワーク
mmr0_adr:		ds.l	1	//!< RS232C-MIDI A用のチャンネルワーク
mmr1_adr:		ds.l	1	//!< RS232C-MIDI B用のチャンネルワーク
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
n_of_err:		ds.l	1	//!< 発生しているエラーの数
err_stock_next:		ds.l	1	//!< 次のエラー格納アドレス
err_stock_addr:		ds.l	1	//!< エラーストックバッファ先頭アドレス
err_stock_size:		ds.l	1	//!< エラーストックバッファサイズ
#endif
};