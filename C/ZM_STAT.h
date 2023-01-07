#pragma once
#include <stdint.h>

enum {
	b_tma_flg = 0,		        //!< (d7��FUNC INTERCEPT_PLAY���L������m_play�����s������
    b_tmb_flg = 1,		        //!< 1�ɏ㏑�������B�O���A�v��������p���[�N�r�b�g)
    b_tmm_flg = 2,	
};

struct zmusic_stat
{
    int8_t midi_board;          //!< MIDI I/F�L���t���O
					            //!< d0�`d3�����ꂼ��CZ6BM1 #1,#2,RS232C-MIDI A,B�ɑΉ�
    int8_t available_device;    //!< ���ۂɎg�p����f�o�C�X�t���O(midi_board�Ɠ�������)
    int8_t timer_flg;	        //!< TIMER ON/OFF(d0TIMER A,d1TIMER B,d2YM3802 TIMER)
	int8_t dummy0;	            //!< dummy
    int16_t wk_size;  			//!< 1�g���b�N���[�N�̃T�C�Y
    int32_t play_start_time;	//!< ���t�J�n���� (10��23��52�b�Ȃ��$00102352,�����l=-1)!
    int32_t play_stop_time;    	//!< ���t��~���� (10��23��52�b�Ȃ��$00102352,�����l=-1)!
    int32_t play_cont_time;    	//!< ���t�ĊJ���� (10��23��52�b�Ȃ��$00102352,�����l=-1)!
    int32_t dev_end_adr;        //!< ZMSC3.X�ŏI�A�h���X
    int16_t t_min;             	//!< ���y���t�p�e���|�̍ŏ��l	(�f�t�H���g�l��MIDI  !!
    int16_t t_max;          	//!< ���y���t�p�e���|�̍ő�l	14bit�^�C�}��        !!
    int16_t t_min_se;          	//!< ���ʉ����t�p�e���|�̍ŏ��l	�̑����ꂽ���̏ꍇ)  !!
    int16_t t_max_se;        	//!< ���ʉ����t�p�e���|�̍ő�l			     !!
    int16_t _t_max;       		//!< ���y���t�p�^�C�}�l�̍ő�l
    int16_t _t_max_se;      	//!< ���ʉ����t�p�^�C�}�l�̍ő�l
    int16_t mask_opm_ch;        //!< FM�����̃}�X�N�`�����l���Ή��r�b�g
					        	//!< d0�`d7���`�����l��1�`8�ɑΉ��B�Ή��r�b�g=1Masked
    int16_t se_tr_max;          //!< ���ʉ��̍ő�g���b�N��[0]

	//!< #TODO ...
#if 0
int8_t ext_pcmdrv		dc.b	0	//!< �O��PCM�h���C�o([0]NO 1�g�ݍ��܂�Ă���)
int8_t current_rs232c_part	dc.b	1	//!< RS232C�̌��݂̑I���p�[�g
					//!< 0PART A,$FFPART B,[1]����`
current_midi_in_r	dc.w	-1	//!< �J�����g����I/F�ԍ�(USER���猩��0-3)
int8_t current_midi_in_w	dc.b	-1	//!< �ʏ�͏펞0
int8_t current_midi_in_b	dc.b	-1	//!< �J�����g���I/F�ԍ�(�����Ŏg�p����(0-3)//!< 2)
current_midi_out_r	dc.w	-1	//!< �J�����g����I/F�ԍ�(USER���猩��0-3)
int8_t current_midi_out_w	dc.b	-1	//!< �ʏ�͏펞0
int8_t current_midi_out_b	dc.b	-1	//!< �J�����g���I/F�ԍ�(�����Ŏg�p����(0-3)//!< 2)
int8_t midi_if_tbl		dcb.b	8+1,-1	//!< MIDI�C���^�[�t�F�[�X�̎g�p�ݒ�
					//!< (0CZ6BM1-1,2CZ6BM1-2,4RS232C-A,6RS232C-B,-1�Ȃ�)
					//!< ���g�pIF��$80+(0,2,4,6)�Ƃ��Ċi�[����Ă���
int8_t ch_wk_mode		dc.b	-1	//!< �`�����l�����[�N�̎g�p���
					//!< -1=�S��(DEFAULT),0=FM����(�ʏ�֎~)
					//!< 1=MIDI����,2=�S������(�ʏ�֎~)
int8_t gs_id		dc.b	$10,$10,$10,$10	//!< DEVICE ID�f�t�H���g�l
int8_t 		ds.b	4		//!< Reserved
int8_t sc88_id	dc.b	$10,$10,$10,$10
int8_t 		ds.b	4		//!< Reserved
int8_t mt32_id	dc.b	$10,$10,$10,$10	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t u220_id	dc.b	$10,$10,$10,$10	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t m1_id		dc.b	$30,$30,$30,$30	//!< 
int8_t 		ds.b	4		//!< Reserved
int8_t adpcm_frq	dc.b	0		//!< ADPCM���g��					!!
int8_t adpcm_pan	dc.b	0		//!< ADPCM�p���|�b�g				!!
int8_t adpb_clr	dc.b	0		//!< ADPCM�o�b�t�@�������L���t���O(0�ȊO=�v������)	!!
int8_t wvmm_clr	dc.b	0		//!< �g�`�������o�b�t�@�������L���t���O(0�ȊO=�v������)!!

meter		dc.w	$0404		//!< ���q					##
int8_t metronome	dc.b	0		//!< Reserve				##
int8_t 		dc.b	0		//!< Reserve				##
key		dc.w	0		//!< ����					##
mst_clk	dc.w	192		//!< �S�����̐�Ή����J�E���g		##
tempo_value	dc.w	120		//!< �e���|�l(DEFAULT=120)			##���ԕύX�֎~
timer_value	dc.w	0		//!< �^�C�}�̒l				##

meter_se	dc.w	$0404		//!< ���q(���ʉ��T�C�h)			!!
int8_t metronome_se	dc.b	0		//!< Reserved				!!
int8_t 		dc.b	0		//!< Reserved				!!
key_se		dc.w	0		//!< ����					!!
mst_clk_se	dc.w	192		//!< �S�����̐�Ή����J�E���g(���ʉ��T�C�h)	!!
tempo_value_se	dc.w	120		//!< �e���|�l(DEFAULT=120)			!!���ԕύX�֎~
timer_value_se	dc.w	0		//!< �^�C�}�̒l				!!
eox_w		dcb.w	8,3		//!< EOX�E�F�C�g(DEFAULT=3)
int8_t se_mode	dc.b	0		//!< ADPCM�̌��ʉ����[�h��(0=NO,0�ȊO=YES)
int8_t fader_flag	dc.b	0		//!< ���ݎ��s���̃t�F�[�_�[
					//!< (d7�}�X�^�[�t�F�[�_�[,d6�`�����l���t�F�[�_�[)
					//!< ���s���̃t�F�[�_�[�ɑΉ������r�b�g=1��
					//!< ���̃t�F�[�_�[������
fnc_no		dc.w	$7fff		//!< �Ō�Ɏ��s����(���邢�͌��ݎ��s����)̧ݸ��ݔԍ�
sr_type	dc.w	$2500		//!< SR���}�X�N����ۂ̃f�t�H���g�l(���ʂ͏����ς��)
sp_buf		dc.l	0		//!< �t�@���N�V�������s���̃X�^�b�N�ۑ����[�N
fnc_quit_addr	dc.l	0		//!< �ً}�A�҃A�h���X(�G���[�����������ꍇ�̒E�o�A�h���X)
opmset_bsr_ms	dc.l	0		//!< FM��������ٰ�ݱ��ڽ(�ʏ�opmset,���ʉ�MODEopmset_se)
timer_mode	dc.b	0		//!< �ǂ̃^�C�}�[���g����
					//!< �^�C�}A-1,�^�C�}B0,YM3802�^�C�}1,$f8-In2
synchro_mode	dc.b	0		//!< �O���������[�h��(0=NO,$FF=YES)
polypress_mode	dc.b	-1		//!< �|���t�H�j�b�N�v���b�V���[���[�h([-1]ON,0=NO)
no_init_mode	dc.b	0		//!< �������������[�h��([0]=NO,0�ȊO=YES)
zmusic_int	dc.l	0		//!< ZMUSIC�����荞�ނƃC���N�������g�����
last_zmusic_int	dc.l	0	//!< �O��MIDI_INP1�����s�����Ƃ���zmusic_int�̒l
zpd_last_fn	ds.b	54		//!< �O��ǂݍ��񂾃t�@�C���̖��O
header_buffer	ds.b	8		//!< �t�@�C��ID�p�o�b�t�@
fm_tune_tbl	dc.l	0		//!< FM�������g�������e�[�u��
pcm_tune_tbl	dc.l	0		//!< PCM�������g�������e�[�u��
occupy_flag	dc.b	0		//!< ��L���(0=FREE,1=��L����Ă���)
itpl_rate	dc.b	0		//!< �O���������̕�ԃ��[�g(1-15)	�i�[�l��YM3802-R75����
errmes_lang	dc.b	0		//!< ���b�Z�[�W�\������([0]English,1Japanese)
external_applications	dc.b	0	//!< �O���A�v���̏풓��
					//!< d7ZP -d,d6ZP -j
					//!< �Ή��r�b�g=1�̎����̃A�v���P�[�V������
					//!< �g�ݍ��܂�Ă���
smf_end_flag	dc.b	0		//!< SMF �]���I���t���O
rs232c_mode	dc.b	0		//!< RS232C-MIDI�̃��[�h
					//!< d7=(0�ʏ�,1�f���A��)
					//!< d0-d3�{�[���[�g���萔[3]
perform_flg	dc.b	0		//!< ZM_PLAY,ZM_CONT,ZM_STOP�̃t�@���N�V������
					//!< ���s����邽�тɑΉ��r�b�g��1�ɏ㏑�������B
					//!< d0PLAY d1CONT d2STOP
					//!< d7loop mode(0normal 1no loop/FUNC $59�Q��)
zmsc_mode	dc.b	3		//!< ZMUSIC���샂�[�h(2V2,[3]V3)

		.even
fm_vol_tbl	dcb.b	16,$ff		//!< �t�F�[�h�A�E�g/�C���p�̉��ʃ��[�N
ad_vol_tbl	dcb.b	16,$ff
m0_vol_tbl	dcb.b	16,$ff
m1_vol_tbl	dcb.b	16,$ff
mr0_vol_tbl	dcb.b	16,$ff
mr1_vol_tbl	dcb.b	16,$ff

fd_wkl		equ	8		//!< ���[�N��
fd_wkl_	equ	3		//!< 2�̉��悩
fd_spd2	equ	0		//!< �X�s�[�h���s���[�N(.w)
fd_spd		equ	2		//!< �X�s�[�h�l(.w)
fd_lvlw	equ	4		//!< �t�F�[�_�[���x��(.w)
fd_lvlb	equ	5		//!< �t�F�[�_�[���x��(.b)
fd_dest	equ	6		//!< �ړI�l(.b)
fd_mode	equ	7		//!< �t�F�[�_�[���[�h(.b)	(-1,+1,nn)

fcf_ch			equ	0
fcf_master		equ	1

//!< �ȉ�spd,spd2,lvlw,lvlb�n�̃��[�N�̔z�u��zmsc2.has�̓s���ɍ��킹�Ă���
					//!< �}�X�^�[�t�F�[�_�[�p�����[�^�Q
mstfd_fm_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_fm_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_fm_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_fm_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_fm_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_fm_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

mstfd_ad_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_ad_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_ad_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_ad_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_ad_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_ad_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

mstfd_m0_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_m0_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_m0_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_m0_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_m0_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_m0_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

mstfd_m1_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_m1_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_m1_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_m1_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_m1_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_m1_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

mstfd_mr0_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_mr0_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_mr0_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_mr0_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_mr0_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_mr0_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

mstfd_mr1_spd2	ds.w	1		//!< �X�s�[�h���s���[�N(.w)
mstfd_mr1_spd	ds.w	1		//!< �X�s�[�h�l(.w)
mstfd_mr1_lvlw	ds.b	1		//!< �t�F�[�_�[���x��(.w)
mstfd_mr1_lvlb	ds.b	1		//!< �t�F�[�_�[���x��(.b)
mstfd_mr1_dest	ds.b	1		//!< �ړI�l(.b)
mstfd_mr1_mode	ds.b	1		//!< �t�F�[�_�[���[�h(.b)

ch_fm_fdp	ds.b	fd_wkl//!< 16	//!< �`�����l���t�F�[�_�[�p�����[�^�Q
ch_ad_fdp	ds.b	fd_wkl//!< 16	//!< (1ch8byte�\��//!< 16ch��)
ch_m0_fdp	ds.b	fd_wkl//!< 16
ch_m1_fdp	ds.b	fd_wkl//!< 16
ch_mr0_fdp	ds.b	fd_wkl//!< 16
ch_mr1_fdp	ds.b	fd_wkl//!< 16

ch_fader_tbl	ds.w	96	//!< �`�����l���t�F�[�_�[
				//!< (�t�F�[�h��������`�����l���ԍ�0-95������)
		dc.w	-1	//!< End code
master_fader_tbl		//!< �}�X�^�[�t�F�[�_�[
				//!< (�t�F�[�h��������f�o�C�X�ԍ�//!< fd_wkl������)
		ds.w	6	//!< 0,8,16,24,32,40 
		dc.w	-1	//!< End code

ch_mask_fm	dc.w	0		//!< �`�����l���t�F�[�_�[�r�b�g���[�N
ch_mask_ad	dc.w	0
ch_mask_m0	dc.w	0
ch_mask_m1	dc.w	0
ch_mask_mr0	dc.w	0
ch_mask_mr1	dc.w	0
		.even
agogik_work		ds.b	__pmod_len	//!< ���y���t�p�A�S�[�M�N���[�N
agogik_work_se		ds.b	__pmod_len	//!< ���ʉ����t�p�A�S�[�M�N���[�N
		.even
mpcm_vol_tbl					//!< MPCM�p���ʃe�[�u��64=�������x��
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
_result_start				//!< �߂�l�o�b�t�@
mask_track_result	ds.l	1	//!< 4//!< (trk_n_max+1) bytes
mask_channel_result	ds.l	1	//!< 4//!< (trk_n_max+1) bytes
m_play_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes
m_stop_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes
m_cont_result		ds.l	1	//!< 4//!< (trk_n_max+1) bytes

					//!< SMF�Đ��֘A���[�N
smf_delta	ds.l	1		//!< SMF �f���^�^�C��
smf_running	ds.l	1		//!< SMF�����j���O�X�e�[�^�X�J�E���^
smf_pointer	ds.l	1		//!< SMF �f�[�^�|�C���^
smf_transfer	ds.l	1		//!< SMF MIDI���M�G���g��
smf_mst_clk	ds.l	1		//!< SMF�}�X�^�[�N���b�N
smf_addr	ds.l	1		//!< SMF�̊i�[�A�h���X

fo_ch_fm	ds.b	8		//!< �t�F�[�h�A�E�g/�C���̃��[�N
		ds.b	8		//!< DUMMY
fo_ch_ad	ds.b	16		//!< d0ch fader active flag	01
fo_ch_m0	ds.b	16		//!< d1master fader active flag	02
fo_ch_m1	ds.b	16		//!< d5master fader move flag	20
fo_ch_mr0	ds.b	16		//!< d6ch fader move flag		40
fo_ch_mr1	ds.b	16		//!< d7�����������ǂ���		80
work
pt_ptr		ds.l	1		//!< play_trk_tbl�̎w�W	�K��work=pt_ptr
pt_ptr_se	ds.l	1		//!< play_trk_tbl_se�̎w�W
cf	ds.b	8	//!< �I�y���[�^�̃R�l�N�V�����e�[�u���r�b�g	!
ol1	ds.b	8	//!< �A�E�g�v�b�g���x��1			!
ol2	ds.b	8	//!< �A�E�g�v�b�g���x��2			!
ol3	ds.b	8	//!< �A�E�g�v�b�g���x��3			!
ol4	ds.b	8	//!< �A�E�g�v�b�g���x��4			!
opm_kon	ds.b	8		//!< OPM���W�X�^8�Ԃ̃��[�N
opm_nom	ds.b	8		//!< �I�y���[�^�}�X�N(OM)��NOT(&b11110000-&b11111111)
_opm		ds.b	256		//!< OPM�̃��W�X�^�E�C���[�W�E���[�N
opm_pmd	dc.b	0
opmreg		equ	_opm-work
AF		equ	$20
#endif
};
