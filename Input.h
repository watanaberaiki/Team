#pragma once
#include "winApp.h"
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 //directInput�̃o�[�W�����w��
#include <dinput.h>

//����
class Input
{
public:
	//namespace�ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://�����o�֐�
	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();
	//�L�[�̉������`�F�b�N
	bool PushKey(BYTE keyNumber);
	//�L�[�̃g���K�[���`�F�b�N
	bool TriggerKey(BYTE keyNumber);

private://�����o�ϐ�
	//WindowsAPI
	WinApp* winApp = nullptr;

	//DirectInput�̃C���X�^���X
	ComPtr<IDirectInput8> directInput = nullptr;

	ComPtr<IDirectInputDevice8> keyboard;

	//�S�L�[�̓��͏�Ԃ��擾����
	BYTE key[256] = {};
	//�O��̑S�L�[�̏��
	BYTE keyPre[256] = {};
};