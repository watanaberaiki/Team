#include "Input.h"
#include <cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

void Input::Initialize(WinApp* winApp)
{
	//�؂�Ă���WinApp�̃C���X�^���X���L�^
	this->winApp = winApp;

	//DirectInput�̏�����
	/*DirectInput�E�E�E�}�C�N���\�t�g�ɂ���ĊJ�����ꂽ�\�t�g�E�F�A�R���|�[�l���g�uMicrosoft DirectX�v�̂����̂ЂƂ�
	�}�E�X�A�L�[�{�[�h�A�W���C�X�e�B�b�N�A�Q�[���R���g���[��������ă��[�U�[����̓��͏������W���邽�߂�API*/

	HRESULT result;

	result = DirectInput8Create(
		winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//�L�[�{�[�h�f�o�C�X�̐���

	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	//���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);//�W���`��
	assert(SUCCEEDED(result));

	//�r�����䃌�x���̃Z�b�g
	/*�r������E�E�E�����̎�̂����������𓯎��ɗ��p����Ƌ�����Ԃ�������ꍇ�ɁA�����̂������𗘗p���Ă���ԁA�ʂ̎�̂ɂ�鎑���̗��p�𐧌��������͋֎~����d�g��*/
	result = keyboard->SetCooperativeLevel(
		winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update()
{
	HRESULT result;

	//�O��̃L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	//�L�[�{�[�h���̎擾�J�n
	result = keyboard->Acquire();
	//�S�L�[�̓��͏����擾����
	result = keyboard->GetDeviceState(sizeof(key), key);
}

bool Input::PushKey(BYTE keyNumber)
{
	//�w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber] && keyPre[keyNumber] == FALSE) {
		return true;
	}
	return false;
}