#ifndef _MAIN_H_
#define _MAIN_H_
//=============================================================================
//
// ���C������ [main.h]
// Author : 
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//�x���Ώ�
#include "dinput.h"//d�����邱�Ƃ�input.cpp�̃O���o�[���ϐ����`���ł���
#include <xaudio2.h>

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")//�V�X�e�������擾�p�ɕK�v
#pragma comment(lib, "dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"ws2_32.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//���_�t�H�[�}�b�g(���_���W[2D]/���_�J���[/�e�N�X�`�����W)
#define CLASS_NAME		"AppClass"			// �E�C���h�E�̃N���X��
#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)
#define	WINDOW_POS_X	(0)
#define	WINDOW_POS_Y	(0)
#define NUM_VERTEX (4)//���_��
#define NUM_POLYGON (2)//�|���S����
#define POLYGON_SIZE 70.0f
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;


#endif