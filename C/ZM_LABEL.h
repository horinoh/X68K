#pragma once

#include <stdint.h>

//			.nlist
enum {
	n_of_split = 8	//!< ���F�X�v���b�g�̍ő�u���b�N��
};

//	.offset	0
//!< ---------------ARCC(AMOD)/ENHANCED VELOCITY SEQUENCE�֘A----------------------
struct arcc_param
{
	int16_t p_arcc_wf;		//!< .w ARCC�g�`�^�C�v					##
							//!< �@ �v���Z�b�g�g�`:0�`7
							//!<    ���[�U�[�g�`:$8000+(0-32767))[2]
//!< #TODO
#if 0 
p_arcc_dpndpt:	ds.b	1	//!< .b ARCC�U���������[�h�̉��Z��(-128�`[0]�`127)		##
p_arcc_dpt_tbl:	ds.b	8	//!< .b ARCC�U���lð���//!< 8 [0]				##
		ds.b	1
p_arcc_dpnspd:	ds.w	1	//!< .w ARECC�U���������[�h�̐U���l���Z����([0]-32767)	!!
p_arcc_spd_tbl:	ds.w	8	//!< .w ARCC��߰�ޒl�e�[�u�� [mod_dflt]			!!
p_arcc_dpt_now:	ds.b	1	//!< .b ARCC���݂̎��s�U���l[0]
p_arcc_flg2:	ds.b	1	//!< .b ARCC����t���O���[�N 2
b_arcc_phase:	equ	0	//!< d0 ARCC�g�`�ʑ�([0]:Normal,[1]:Reverse)
b_arcc_syncok:	equ	7	//!< d7 ARCC�g�`�ڑ��\��([0]:No,1:Yes)
p_arcc_mode:	ds.b	1	//!< .b MIDI ARCC���[�h([-1]:�ʏ�,0�`127:�g��)
p_arcc_omt:	ds.b	1	//!< .b 1/8 MODE,OPTIONAL MODE�̏ȗ��r�b�g�p�^�[��[$01]
p_arcc_1st_dly:	ds.w	1	//!< .w ARCC�����f�B���C [0]
p_arcc_8st_tbl:	ds.w	8	//!< .w ARCC�̐U���ω��f�B���C
p_arcc_stp_tbl:	ds.w	8	//!< .w �e�|�C���g�ɒu����ARCC�X�e�b�v�ۑ����[�N//!< 8(Fixed)
p_arcc_step2:	ds.w	1	//!< .w ARCC���s�ï��
p_arcc_spd:	ds.w	1	//!< .w ARCC��߰��
p_arcc_spd2:	ds.w	1	//!< .w ARCC�߰��ܰ�
p_arcc_dly2:	ds.w	1	//!< .w ARCC�ިڲܰ�
p_arcc_level:	ds.w	1	//!< .w ARCC�߲��ܰ�
p_arcc_o:	ds.w	1	//!< .w ARCC�g�`�X�^�[�g�l(�m�R�M���g,�O�p�g��p)
p_arcc_sw:	ds.b	1	//!< .b ARCC�X�C�b�`					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_arcc_sw2:	ds.b	1	//!< .b ARCC�X�C�b�`�ۑ�					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_arcc_chain:	ds.b	1	//!< .b ARCC�̐ڑ��׸�
				//!<    (-1:�g�`�ڑ�����,0:���ڑ��\,1:�ڑ��ҋ@��,[2]:����)
p_arcc_flg:	ds.b	1	//!< .b ARCC����t���O���[�N
b_arcc_first:	equ	0	//!< d0 ARCC���߂Ă��Ⴄ��([0]:�͂��߂�,1:�Ⴄ)
b_arcc_dpn:	equ	1	//!< d1 ARCC�U���𑝉����������郂�[�h([0]:OFF,1:ON)
b_arcc_reset:	equ	2	//!< d2 ARCC�̃��Z�b�g�v��([0]:No [1]:Yes)
b_arcc_wvsqrst:	equ	3	//!< d3 ARCC�g�`�̒l���x���̎����X�V([0]:No,1:Yes)
b_arcc_wvsq:	equ	4	//!< d4 ARCC�g�`�̒l���L�[�I�����ɍX�V���郂�[�h([0]:OFF,1:ON)
b_arcc_rstsync:	equ	5	//!< d5 ARCC �x�����ɓ������邩(1:Yes,[0]:No)
b_vseq_gvnsync:	equ	6	//!< d6 VSEQ VELOCITY��^�����Ă鎞���i�s�����邩([0]:no,1:yes)
b_arcc_tiesync:	equ	6	//!< d6 ARCC �^�C���ɓ������邩(1:Yes,[0]:No)
b_arcc_sync:	equ	7	//!< d7 ARCC �L�[�I�����ɓ������邩([1]:Yes,0:No)
b_vseq_msrsync:	equ	7	//!< d7 VSEQ ���ߐ��������Ƀ��Z�b�g���邩(1:Yes,[0]:No)
p_arcc_last:	ds.b	1	//!< .b �O��o�͂���ARCC�l(MIDI)[-1]
p_arcc_reset:	ds.b	1	//!< .b ARCC�̃��Z�b�g�l([0])
p_arcc_origin:	ds.b	1	//!< .b ARCC��l([127])
p_arcc:		ds.b	1	//!< .b ARCC�̃R���g���[���i���o�[([11]=Expression)
p_arcc_o_next:	ds.w	1	//!< .w ���ɂ���\��̔g�`�J�n�_
p_arcc_step_next: ds.w	1	//!< .w ���ɂ���\��̃X�e�b�v
p_arcc_spd_next:  ds.w	1	//!< .w ���ɂ���\��̃X�s�[�h
p_wvam_start:	ds.l	1	//!< .l �g�`�������J�n�A�h���X
p_wvam_point:	ds.l	1	//!< .l �g�`���������݂̃|�C���^
p_wvam_end:	ds.l	1	//!< .l �g�`�������I���A�h���X
		ds.b	1
p_wvam_lpmd:	ds.b	1	//!< .b �g�`���������[�v���[�h
p_wvam_lpst:	ds.l	1	//!< .l �g�`���������[�v�J�n�A�h���X
p_wvam_lped:	ds.l	1	//!< .l �g�`���������[�v�I���A�h���X
p_wvam_lptm:	ds.l	1	//!< .l �g�`���������[�v��(0=��)
p_wvam_lptm2:	ds.l	1	//!< .l �g�`���������[�v�񐔎��s���[�N(0=��)
p_alta_flg:	ds.b	1	//!< .b �g�`�������������[�h�t���O
p_arcc_n:	ds.b	1	//!< .b ARCCð����߲��(-1,0�`7)
p_arcc_wf2:	ds.w	1	//!< .w ���ɂ���\��̔g�`�^�C�v[2]			!!
p_arcc_dpnrpt:	ds.w	1	//!< .w �U����������������s����			!!
				//!<    (0�`32767,[0]:��)
p_arcc_rndcnt:	ds.w	1	//!< .w �g�`������������(0-32767)		!!
p_arcc_dpntime:	ds.w	1	//!< .w ��������������s������(0-65535)	!!
p_arcc_syncnt:	ds.w	1	//!< .w �����J�E���g	([1]�`65535)	##
p_arcc_syncnt2:	ds.w	1	//!< .w �����J�E���g���s���[�N([1]�`65535)	##
		ds.l	16
		.even
#endif
};

// __arcc_len:	equ	arcc_param_end-arcc_param	//!< ARCC�֘A�̃��[�N��
// //!< ---------------���t�g���b�N���[�N�G���A--------------------------------------
// 	.offset	-128
// p_note:		ds.b	4//!< 16	//!< �m�[�g�I���e�[�u��
// 	.offset	0

struct track_work
{
//!< ---------------��{�p�����[�^------------------------------------------------
	int16_t p_step_time;			//!< .w �X�e�b�v�^�C��
	int8_t 	p_track_stat;			//!< .b �g���b�N�X�e�[�^�X					$
									//!< ($00:���t�� $80:���S $01:�I��
									//!<  $02:��~�� $40:�����҂�)
#if 0
p_track_mode:	ds.b	1	//!< .b �g���b�N���[�h($80:Keyoff���� $00:�ʏ�)		$
p_trkfrq:	ds.b	1	//!< .b ���荞�ݕp�x(�}�X�^���[�N)				$
p_trkfrq_wk:	ds.b	1	//!< .b ���荞�ݕp�x(���s���[�N)				$
p_type:		ds.w	1	//!< .w �������					!!
				//!< (FM:0 ADPCM:1 MIDI1�`4:$8000�`$8003
				//!<  PATTERN:$7fff)
p_ch:		ds.w	1	//!< .w �`�����l���ԍ�(0�`32767)			!!
p_data_pointer:	ds.l	1	//!< .l ���݂̃R�}���h�|�C���^�A�h���X	#
p_now_pointer:	ds.l	1	//!< .l ���ݎ��s����CMD�̃A�h���X		#
//!< ---------------�A�t�^�[�^�b�`�V�[�P���X�֘A----------------------------------
p_trk_seq_flg:	ds.b	1	//!< .b [0]
b_vseq_done:	equ	7	//!< d7 vseq����x�̊��荞�ݏ����ŉ��x�����Ȃ����߂̃t���O[0]
b_loop_done:	equ	6	//!< d6 [do]-[loop]�𖳌��ɌJ��Ԃ��̂�h�~����t���O[0]
p_aftc_n:	ds.b	1	//!< .b ����������ݽ�̃|�C���^(-1,0�`7)
p_aftc_omt:	ds.b	1	//!< .b ����������ݽ�ȗ��t���O[0]		##
p_aftc_rltv:	ds.b	1	//!< .b ����������ݽ���Βl�t���O[0]		##
p_aftc_flg:	ds.b	1	//!< .b ����������ݽ����t���O[0]		##
b_aftc_first:	equ	0	//!< d0 ����������ݽ ���߂Ă��Ⴄ��([0]:�͂��߂� 1:�Ⴄ)
b_aftc_rstsync:	equ	5	//!< d5 ����������ݽ �x�����ɓ������邩(1:Yes,[0]:No)
b_aftc_tiesync:	equ	6	//!< d6 ����������ݽ �^�C���ɓ������邩(1:Yes,[0]:No)
b_aftc_sync:	equ	7	//!< d7 ����������ݽ �L�[�I�����ɓ������邩([1]:Yes,0:No)
p_aftc_level:	ds.b	1	//!< .b ���ݎ��s���̃A�t�^�[�^�b�`�l[-1]	##
p_aftc_tbl:	ds.b	8	//!< .b ����������ݽ�l�e�[�u��//!< 8
p_aftc_sw:	ds.b	1	//!< .b ����������ݽ�̽���
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)	!!
p_aftc_sw2:	ds.b	1	//!< .b ����������ݽ�̽����ۑ����[�N
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONALMODE ON)	!!
p_aftc_1st_dly:	ds.w	1	//!< .w ����������ݽ�����f�B���C[0]				!!
p_aftc_8st_tbl:	ds.w	8	//!< .w ����������ݽ�ިڲ�l//!< 8
p_aftc_dly2:	ds.w	1	//!< .w ����������ݽ�ިڲܰ�
p_aftc_syncnt:	ds.w	1	//!< .w �����J�E���g	([1]�`65535)	##
p_aftc_syncnt2:	ds.w	1	//!< .w �����J�E���g���s���[�N([1]�`65535)	##
		ds.l	1
//!< ---------------�s�b�`���W�����[�V�����֘A----------------------------------
pmod_param:
p_pmod_dpndpt:	ds.w	1	//!< .w PMOD�U���������[�h�̉��Z��(-32768�`[0]�`32767)	##
p_pmod_dpt_tbl:	ds.w	8	//!< 8w PMOD�U���lð��� [0]					##
p_pmod_dpnspd:	ds.w	1	//!< .w PMOD�U���������[�h�̐U���l���Z����([0]-32767)	!!
p_pmod_spd_tbl:	ds.w	8	//!< 8w PMOD��߰�ޒlð���[mod_dflt]				!!
p_pmod_dpt_now:	ds.w	1	//!< .w PMOD���݂̎��s�U���l[0]
p_pmod_wf:	ds.w	1	//!< .w PMOD�g�`�^�C�v[2]				%%
				//!<    �v���Z�b�g�g�`:0�`7
				//!<    ���[�U�[�g�`:$8000+(0-32767)
p_pmod_1st_dly:	ds.w	1	//!< .w PMOD�����f�B���C [0]			%%
p_pmod_8st_tbl:	ds.w	8	//!< 8w PMOD�̐U���ω��f�B���C			%%
p_pmod_stp_tbl:	ds.l	8	//!< 8l PMOD���Z�X�e�b�v�lð���
				//!<    (�g�`�^�C�v=��`�g,�m�C�Y,�g�`�������ł�
				//!<     �U���l���i�[�����)
p_pmod_sw:	ds.b	1	//!< .b PMOD�����						!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_pmod_sw2:	ds.b	1	//!< .b PMOD������ۑ�					!!
				//!<    ([0]=OFF,$ff=1/8 MODE ON,$01=OPTIONAL MODE ON)
p_pmod_chain:	ds.b	1	//!< .b PMOD�̐ڑ��׸�
				//!<    (-1:�g�`�ڑ�����,0:���ڑ��\,1:�ڑ��ҋ@��,[2]:����)
p_pmod_flg:	ds.b	1	//!< .b PMOD�̓���t���O[0]
b_pmod_first:	equ	0	//!< d0 PMOD ���߂Ă��Ⴄ��([0]:�͂��߂�,1:�Ⴄ)
b_pmod_dpn:	equ	1	//!< d1 PMOD �U���𑝉����������郂�[�h([0]:OFF,1:ON)
b_pmod_syncok:	equ	2	//!< d2 PMOD �g�`�ڑ��\��([0]:No,1:Yes)
b_pmod_wvsqrst:	equ	3	//!< d3 PMOD �g�`�̒l���x���̎����X�V([0]:NO,1:YES)
b_pmod_wvsq:	equ	4	//!< d4 PMOD �g�`�̒l���L�[�I�����ɍX�V���郂�[�h([0]:OFF,1:ON)
b_pmod_rstsync:	equ	5	//!< d5 PMOD �x�����ɓ������邩(1:Yes,[0]:No)
b_pmod_tiesync:	equ	6	//!< d6 PMOD �^�C���ɓ������邩(1:Yes,[0]:No)
b_pmod_sync:	equ	7	//!< d7 PMOD �L�[�I�����ɓ������邩([1]:Yes,0:No)
p_pmod_mode:	ds.b	1	//!< .b MIDI PMOD���[�h
				//!<    ([-1]:�ʏ�,0:FM�݊��g��,1:MIDI�݊��g��)
p_pmod_omt:	ds.b	1	//!< .b 1/8 MODE,OPTIONAL MODE�̏ȗ��r�b�g�p�^�[��
				//!<    (�U����̎���[$01])
p_pitch_last:	ds.w	1	//!< .w �O��o�͂����x���_�[�l [-1]
p_pmod_step2:	ds.l	1	//!< .l PMOD���s�ï��(Fixed)
p_pmod_dly2:	ds.w	1	//!< .w PMOD��ިڲ���sܰ�
p_pmod_spd:	ds.w	1	//!< .w PMOD���߰��
p_pmod_spd2:	ds.w	1	//!< .w PMOD���߰��ܰ�
p_pmod_pitch:	ds.l	1	//!< .l PMOD��߯�ܰ�(Fixed)
p_pmod_step_next: ds.l	1	//!< .l ���ɂ���\��̃X�e�b�v
p_pmod_spd_next:  ds.w	1	//!< .w ���ɂ���\��̃X�s�[�h
p_wvpm_start:	ds.l	1	//!< .l �g�`�������J�n�A�h���X
p_wvpm_point:	ds.l	1	//!< .l �g�`���������݂̃|�C���^
p_wvpm_end:	ds.l	1	//!< .l �g�`�������I���A�h���X
		ds.b	1
p_wvpm_lpmd:	ds.b	1	//!< .b �g�`���������[�v���[�h
p_wvpm_lpst:	ds.l	1	//!< .l �g�`���������[�v�J�n�A�h���X
p_wvpm_lped:	ds.l	1	//!< .l �g�`���������[�v�I���A�h���X
p_wvpm_lptm:	ds.l	1	//!< .l �g�`���������[�v��(0=��)
p_wvpm_lptm2:	ds.l	1	//!< .l �g�`���������[�v�񐔎��s���[�N(0=��)
p_altp_flg:	ds.b	1	//!< .b �g�`�������������[�h�t���O
p_pmod_n:	ds.b	1	//!< .b 8�߲�ĥPMOD�ð����߲��(-1,0�`7)
p_pmod_wf2:	ds.w	1	//!< .w PMOD���s�g�`�^�C�v					!!
				//!< �v���Z�b�g�g�`:0�`7
				//!< ���[�U�[�g�`:$8000+(0-32767))[2]
p_pmod_dpnrpt:	ds.w	1	//!< .w �U����������������s����(0�`32767,[0]:��)		!!
p_pmod_rndcnt:	ds.w	1	//!< .w �g�`������������(0-32767)		!!
p_pmod_dpntime:	ds.w	1	//!< .w ��������������s������(0-65535)	!!
p_pmod_syncnt:	ds.w	1	//!< .w �����J�E���g	([1]�`65535)	##
p_pmod_syncnt2:	ds.w	1	//!< .w �����J�E���g���s���[�N([1]�`65535)	##
		ds.l	16
	.even
pmod_param_end:	ds.b	0
__pmod_len:	equ	pmod_param_end-pmod_param

p_arcc_param:	ds.b	__arcc_len//!< 4
p_vseq_param:	ds.b	__arcc_len
//!< ---------------�|���^�����g&�f�B�`���[���֌W----------------------------------
p_detune:	ds.w	1	//!< .w �f�`���[��(�I�[�g�x���h�̊J�n�l�ɂ��Ȃ�)[0]	!!
p_special_tie:	ds.w	1	//!< .w MIDI��p�̃X�y�V�����E�^�C�p�s�b�`���[�N[0]	!!
p_port_dly:	ds.w	1	//!< .w �|���^�����g�f�B���C[0]		!!
p_port_cnt:	ds.w	1	//!< .w �|���^�����g�p������[0]		!!
p_bend_dly:	ds.w	1	//!< .w �x���h�f�B���C�l[0]				!!
p_bend_cnt:	ds.w	1	//!< .w �x���h�e�C��/�x���h�^�C��[0]		!!
p_port2_dly:	ds.w	1	//!< .w ���������ăf�B���C[0]		!!
p_port2_cnt:	ds.w	1	//!< .w ���������ăe�C��/���������ă^�C��[0]!!
p_port_pitch:	ds.l	1	//!< .l �������/�������ޗp
				//!<    ���݂̃x���h�l//!< 65536(Fixed)[0]
p_port_flg:	ds.b	1	//!< .b ������ĵ݂��̂�
				//!<    ([0]=OFF,1=Normal Delay,-1=Minus Delay)
p_port2_flg:	ds.b	1	//!< .b ���������Ľ���([0]=OFF,1=ON)
p_bend_sw:	ds.b	1	//!< .b �������ނ��݂��̂�([0]=OFF,1=ON)
				//!<    d7:���߂Ă�(bit=0:���߂�)
p_agogik_flg:	ds.b	1	//!< .b �A�S�[�M�N�r�b�g���[�N[0]
b_agogik_trmk:	equ	0	//!< d0 Agogik�哱���t���O([0]=No/1=Yes)
b_agogik_msrsync: equ	2	//!< d2 Agogik ���ߐ��������Ƀ��Z�b�g���邩(1:Yes,[0]:No)
b_agogik_wvsqrst: equ	3	//!< d3 Agogik �g�`�̒l���x���̎����X�V
				//!<    ([0]:No,1:Yes)
b_agogik_wvsq:	  equ	4	//!< d4 Agogik �g�`�̒l���L�[�I�����ɍX�V���郂�[�h
				//!<    ([0]:OFF,1:ON)
b_agogik_rstsync: equ	5	//!< d5 Agogik �x�����ɓ������邩(1:Yes,[0]:No)
b_agogik_tiesync: equ	6	//!< d6 Agogik �^�C���ɓ������邩(1:Yes,[0]:No)
b_agogik_sync:	equ	7	//!< d7 Agogik �L�[�I�����ɓ������邩(1:Yes,[0]:No)
p_bend_dst:	ds.w	1	//!< .w �I�[�g�x���h�̃����W(�I�[�g�x���h�̖ړI�l�ƂȂ�)[0]
		ds.w	1	//!< .w 
p_port_step:	ds.l	1	//!< .l �|���^�����g�p���s�X�e�b�v//!< 65536
		ds.l	16
//!< ----------------��ʃp�����[�^-------------------------------------------------
p_measure:	ds.l	1	//!< .l ���݂̏��ߔԍ�[0]

p_voice_rsv:	ds.w	1	//!< .w FM/ADPCM�����g���b�N�̃{�C�X���U�[�u��
				//!<    ([0]�`7)
p_next_on:	ds.b	1	//!< .b FM/ADPCM�����g���b�N�̎���̔����`�����l��
				//!<    [0]
p_timbre_set:
pts_bank:	equ	7	//!< d7:Bank Select�̐ݒ肪�s��ꂽ��(MIDI)
pts_program:	equ	6	//!< d6:Program�`�F���W���s��ꂽ��(MIDI)
pts_volume:	equ	5	//!< d5:Volume�ݒ肪�s��ꂽ��(MIDI)
pts_panpot:	equ	4	//!< d4:Panpot�ݒ肪�s��ꂽ��(MIDI)
pts_damper:	equ	3	//!< d3:Damper�ݒ肪�s��ꂽ��(MIDI)
p_tone_set:	ds.b	1	//!< .b ��n�ޯĂ��`�����l��n�Ƃ���
				//!<    ���F��ݒ肵�����ǂ����̃t���O(FM)[0]

p_return:	ds.l	1	//!< .l gosub�̎��̃A�h���X[0]

p_transpose:	ds.b	1	//!< .b �L�[�g�����X�|�[�Y[0]
p_mask_mode:	ds.b	1	//!< .b Mask Mode���ǂ���([0]=Normal,1=Masked)			!!
p_damper:	ds.b	1	//!< .b damper on or off ([0]�`63:OFF/64�`127:ON)
p_seq_flag:	ds.b	1	//!< .b []�R�}���h�n�̏����t���O�r�b�g�p�^�[��[0]
				//!< d0:[D.C.]�������������Ƃ����邩([0]=no/1=yes)
				//!< d1:[FINE]���������ׂ����ǂ���([0]=no/1=yes)
				//!< d2:[!]�t���O([0]=OFF/1=���s��)
p_bank_msb:	ds.b	1	//!< .b MIDI Bank MSB [-1]	!!
p_bank_lsb:	ds.b	1	//!< .b MIDI Bank LSB [-1]	!!
p_pgm:		ds.w	1	//!< .w Program Number([0]-32767)	!!

p_sync_wk:	ds.b	1	//!< .b ���������R�}���h�p���[�N[1]
p_@b_range:	ds.b	1	//!< .b �x���h�����W[12]
p_vol16:	ds.b	1	//!< .b 16�i�K����(0-16),[-1]=����(127�i�K���ʃ��[�h)
p_velo16:	ds.b	1	//!< .b 16�i�K�x���V�e�B(0-16),[-1]=����
				//!<    (127�i�K�x���V�e�B���[�h)
p_do_loop_flag:	ds.b	1	//!< .b [DO]���ȑO�ɐݒ肳��Ă��邩
				//!<    [0]=NO/���[�v��(1�`255)
p_md_flg:	ds.b	1	//!< .b �e��r�b�g���[�N[0]
b_bend_reset:	equ	0	//!< d0 @B:����ޒl��ؾ�Ă��ׂ����ǂ���
				//!<    (MIDI��p [0]=No/1=Yes)
b_pmod_reset:	equ	1	//!< d1 @M:Ӽޭڰ��ݒl��ؾ�Ă��邩���Ȃ���
				//!<    (MIDI��p [0]=No/1=Yes)
				//!<    ��(���ꂼ��֌WCTRL��0�ȊO�̒l��
				//!<       �o�͂������Ƀr�b�g��1�ɂȂ�)
b_vtune_mode:	equ	2	//!< d2 ADPCM Variable Tuning Mode ([0]:NOT)
b_slot_mask:	equ	3	//!< d3 OPM�X���b�g�}�X�N�̐؂芷��
b_tie_mode:	equ	4	//!< d4 MIDI Tie Mode([0]:Normal,1:Special)
b_voice_rsv:	equ	5	//!< d5 FM/ADPCM��Voice Reserve���s������([0]:No/1:Yes)
b_split_mode:	equ	7	//!< d7 ���F�X�v���b�g���[�h([0]:OFF,1:ON
p_how_many:	ds.b	1	//!< .b �������L�[�I�����Ă��邩
				//!<    ([-1]:None/0�`7:1�`8)
p_last_note:	ds.b	1	//!< .b �O�񔭉������m�[�g�ԍ�([-1])
//!< ---------------MIDI��p�֌W----------------
p_maker:	ds.b	1	//!< .b Ұ��ID(MIDI)[-1]
p_device:	ds.b	1	//!< .b ���޲�ID(MIDI)[-1]
p_module:	ds.b	1	//!< .b Ӽޭ��ID(MIDI)[-1]
p_effect1:	ds.b	1	//!< .b Effect Parameter 1(GS:RVB)	[-1]
p_effect3:	ds.b	1	//!< .b Effect Parameter 3(GS:CHO)	[-1]
p_effect4:	ds.b	1	//!< .b Effect Parameter 4(GS:DLY)	[-1]
p_effect2:	ds.b	1	//!< .b Effect Parameter 2	[-1]
p_effect5:	ds.b	1	//!< .b Effect Parameter 5	[-1]
//!< ----------------��ʃp�����[�^-------------
p_timbre_src:	ds.b	1	//!< .b ���F�̃R�s�[���`�����l���I�t�Z�b�g(FM:0-7)
p_sync:		ds.b	1	//!< .b OPM-LFO�̃V���N�X�C�b�`(0=off,1=on)		!!
p_om:		ds.b	1	//!< .b �I�y���[�^�}�X�N(&b0000-&b1111)		!!
		ds.b	1

p_vol:		ds.b	1	//!< .b 127�i�K����(0-127)	[??]		!
p_velo:		ds.b	1	//!< .b �x���V�e�B(0-[127])			!
p_frq:		ds.b	1	//!< .b ADPCM�̎��g��(0-6)	[4]		!
p_pan:		ds.b	1	//!< .b Last PANPOT(0�`127,-1=MUTE)[64]	!

p_onoff_bit:	ds.b	1	//!< �L�[�I���^�I�t�r�b�g���[�N
b_keyon:	equ	7	//!< d7:Key ON�̂Ƃ���bit=1���㏑�������
b_keyoff:	equ	6	//!< d6:Key OFF�̂Ƃ���bit=1���㏑�������
p_om_bak:	ds.b	1	//!< .b p_om�̃o�b�N�A�b�v
p_Q_gate:	ds.w	1	//!< .w Q�R�}���h�̒l(CONVERTER��p)
				//!<    (0-256:NORMAL Q,���l:@Q)
p_midi_if:	ds.w	1	//!< .w ���[�U����݂�MIDI�C���^�[�t�F�[�X�ԍ�(0-3)

p_do_loop_ptr:	ds.l	1	//!< .l [do]�̂���ʒu
p_int_play_ope:	ds.l	1	//!< .l ���t����ٰ�ݱ��ڽ
				//!<    �ʏ�̓\�[�XZMSC2.HAS����int_play_ope_fm,
				//!<    int_play_ope_ad,int_play_ope_midi
p_opmset:			//!< .l OPM�A�N�Z�X���[�`��(FM)
p_midi_trans:	ds.l	1	//!< .l MIDI���M���[�`��(MIDI)

p_total:	ds.l	1	//!< .l �g�[�^���X�e�b�v�^�C��
p_total_olp:	ds.l	1	//!< .l ٰ�ߊO��İ�ٽï�߲�

pst_split_len:	equ	6
p_split_tbl:			//!< .l ���F�X�v���b�g�̊Ǘ����[�N
		ds.b	pst_split_len//!< n_of_split
pst_split_st:	equ	0	//!< .b ���蓖�Ă�J�n�m�[�g�i���o�[(0-127,128�Ŏc��S��)
pst_split_ed:	equ	1	//!< .b ���蓖�Ă�I�[�m�[�g�i���o�[(0-127,128�Ŏc��S��)
pst_split_bank:	equ	2	//!< .w ���蓖�Ă�BANK�ԍ�(MIDI:0-16383/FM,ADPCM:0-255)
pst_split_pgm:	equ	4	//!< .w ���蓖�Ă鉹�F�ԍ�(MIDI:0-127/FM,ADPCM:0-127 or 0-32767)

p_lfo_param:			//!< �ȉ��Q�o�C�g�y�A���[�N
p_pitch_param:	ds.w	1	//!< �����֌W�̓��ꏈ���t���O
p_level_param:	ds.w	1	//!< ���ʊ֌W�̓��ꏈ���t���O
p_key_on:	ds.l (16+1)//!< 2	//!< ���ꂩ�甭�����鉹�� note.b,velocity.b,
				//!< ch offset(.w),prog(.l)���i�[�����B
				//!< ������ch offset��FM/ADPCM�݂̂ŗL���A
				//!< MIDI�ł͏��0
pko_note:	equ	0
pko_velo:	equ	1
pko_offset:	equ	2
pko_prog:	equ	4
pko_size:	equ	8
		ds.b	64
p_user:		ds.b	1	//!< .b ���[�U�[�ėp���[�N
#endif
};

// track_work_size:	equ	track_work_end-track_work+128	//!< ���݂̎��ێg�p��
// trwk_size:		equ	2048	//!< �e�g���b�N�̉��t���̃��[�N�T�C�Y(�ύX�s��)
// trwk_size_:		equ	11	//!< ���[�N�T�C�Y���Q�̉��悩(�ύX�s��)

// 	.offset	0
// k_note		ds.b	1	//!< .b �m�[�g�I�������m�[�g�i���o�[[-1]
// 				//!<    (���ۂ�Key OFF������d7=1)
// k_velo:		ds.b	1	//!< .b �����x���V�e�B[-1]
// 				//!<    (�Q�[�g�^�C����0�ɂȂ��d7=1)
// k_gate_time:	ds.w	1	//!< .w gate time[?]
// 				//!<    (tie��1��̊��荞�ݓ��ł�0,
// 				//!<     ���荞�݂��o���-1,-2�͖����Q�[�g)
// k_note_len:	ds.b	0
	