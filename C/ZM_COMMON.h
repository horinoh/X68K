#pragma once

#include <stdint.h>

struct buffer_information
{
	int32_t trk_buffer_top;			//!< �g���b�N�o�b�t�@�擪�A�h���X
	int32_t trk_buffer_size;		//!< �g���b�N�o�b�t�@�T�C�Y
	int32_t trk_buffer_end;			//!< �g���b�N�o�b�t�@�ŏI�A�h���X

	//!< #TODO
#if 0
adpcm_buffer_top:	ds.l	1	//!< (AD)PCM�o�b�t�@�擪�A�h���X
adpcm_buffer_size:	ds.l	1	//!< (AD)PCM�o�b�t�@�T�C�Y
adpcm_buffer_end:	ds.l	1	//!< (AD)PCM�o�b�t�@�ŏI�A�h���X
wave_memory_top:	ds.l	1	//!< �g�`�������o�b�t�@�擪�A�h���X
wave_memory_size:	ds.l	1	//!< �g�`�������o�b�t�@�T�C�Y
wave_memory_end:	ds.l	1	//!< �g�`�������o�b�t�@�ŏI�A�h���X
seq_wk_tbl:		ds.l	1	//!< ���y���t�g���b�N���[�N�擪�A�h���X
seq_wk_tbl_se:		ds.l	1	//!< ���ʉ����t�g���b�N���[�N�擪�A�h���X
play_trk_tbl:		ds.l	1	//!< �ǂ̃g���b�N�����t����̂���\���e�[�u��
play_trk_tbl_se:	ds.l	1	//!< �ǂ̃g���b�N�����t����̂���\���e�[�u��(���ʉ�)
adpcm_tbl:		ds.l	1	//!< (AD)PCM�g�[���̃A�h���X�e�[�u��[0]	!!
adpcm_n_max:		ds.w	1	//!< ��`�ł���ő�g�[����[0]		!!
adpcm_tbl2:		ds.l	1	//!< (AD)PCM���F�̃A�h���X�e�[�u��[0]	#
adpcm_n_max2:		ds.w	1	//!< ��`�ł���ő剹�F��[0]		#
wave_tbl:		ds.l	1	//!< �g�`�������f�[�^�̃e�[�u���A�h���X
wave_n_max:		ds.w	1	//!< �g�`�������̒�`�ő��
fmsnd_buffer:		ds.l	1	//!< FM���F�o�b�t�@
fmsnd_n_max:		ds.w	1	//!< FM���F�o�b�t�@�̒�`�ő��
lyric_address:		ds.l	1	//!< �̎�������f�[�^�A�h���X
lyric_size:		ds.l	1	//!< �̎�������f�[�^�T�C�Y
					//!< (�������0�ŏI���Ȃ��ꍇ�L��)
trk_po_tbl:		ds.l	1	//!< �e�g���b�N�̐擪�A�h���X�i�[�e�[�u���A�h���X
trk_po_tbl_se:		ds.l	1	//!< �e�g���b�N�̐擪�A�h���X�i�[�e�[�u���A�h���X
trk_n_max:		ds.w	1	//!< �g���b�N�̌�
pattern_trk:		ds.l	1	//!< �p�^�[���g���b�N�A�h���X[0]
pattern_trk_se:		ds.l	1	//!< �p�^�[���g���b�N�A�h���X���ʉ�[0]
m_buffer_0:		ds.l	1	//!< CZ6BM1-0�p�̑��M�o�b�t�@
m_buffer_1:		ds.l	1	//!< CZ6BM1-1�p�̑��M�o�b�t�@
m_buffer_r:		ds.l	1	//!< RS232C-MIDI�p�̑��M�o�b�t�@
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
rec_buffer_0:		ds.l	1	//!< CZ6BM1-0�p�̎�M�o�b�t�@
rec_buffer_1:		ds.l	1	//!< CZ6BM1-1�p�̎�M�o�b�t�@
rec_buffer_r:		ds.l	1	//!< RS232C-MIDI�p�̎�M�o�b�t�@
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
mm0_adr:		ds.l	1	//!< CZ6BM1-0�p�̃`�����l�����[�N
mm1_adr:		ds.l	1	//!< CZ6BM1-1�p�̃`�����l�����[�N
mmr0_adr:		ds.l	1	//!< RS232C-MIDI A�p�̃`�����l�����[�N
mmr1_adr:		ds.l	1	//!< RS232C-MIDI B�p�̃`�����l�����[�N
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
			ds.l	1	//!< RESERVED
n_of_err:		ds.l	1	//!< �������Ă���G���[�̐�
err_stock_next:		ds.l	1	//!< ���̃G���[�i�[�A�h���X
err_stock_addr:		ds.l	1	//!< �G���[�X�g�b�N�o�b�t�@�擪�A�h���X
err_stock_size:		ds.l	1	//!< �G���[�X�g�b�N�o�b�t�@�T�C�Y
#endif
};