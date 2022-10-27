#include "WinApp.h"

//�E�B���h�E�v���V�[�W��
/*�E�B���h�E�E�E�E�R���s���[�^�̑����ʏ�ŌX�̃\�t�g�E�F�A�Ɋ��蓖�Ă�ꂽ��`�̕\���̈�*/
/*�E�B���h�E�v���V�[�W���E�E�E�E�B���h�E���b�Z�[�W����������֐�
���b�Z�[�W���[�v�Ŏ擾�������b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��M���A�󂯎�������b�Z�[�W���E�B���h�E�v���V�[�W���ŏ�������*/
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ɉ����ăQ�[���ŗL�̏������s��
	switch (msg) {
		//�E�B���h�E���j�����ꂽ
	case WM_DESTROY:
		//OS�ɑ΂��āA�A�v���̏I����`����
		/*OS�E�E�E�R���s���[�^�[�𓮂������߂̃\�t�g�E�F�A�̂���
		Operating System �I�y���[�e�B���O �V�X�e���̗�
		�R���s���[�^�[�S�̂��Ǘ��A���䂵�A�l���g����悤�ɂ������������*/
		PostQuitMessage(0);
		return 0;
	}

	//�W���̃��b�Z�[�W�������s��
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


void WinApp::Initialize()
{
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;	//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = L"DirectXGame";		//�E�B���h�E�N���X��
	/*�E�B���h�E�N���X�E�E�E�u�ǂ̂悤�ȃE�B���h�E����邩�̒�`�v�̂���
	�A�C�R���A���j���[�A�J�[�\���ȂǂƁA�E�B���h�E�v���V�[�W������`����Ă���*/
	w.hInstance = GetModuleHandle(nullptr);	//�E�B���h�E�n���h��
	/*�E�B���h�E�n���h���E�E�E�R���s���[�^���e�E�B���h�E�Ɋ���U��Ǘ��ԍ�
	������w�肷�邱�ƂŁA�R���s���[�^�ɊY���̃E�B���h�E��F��������*/
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���w��

	//�E�B���h�E�N���X��OS�ɓo�^����
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y{X���W Y���W ���� �c��}
	RECT wrc = { 0, 0, window_width, window_height };
	//�����ŃT�C�Y���C����
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(w.lpszClassName,//�N���X��
		L"DirectXGame",			//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,	//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,			//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,			//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,	//�E�B���h�E����
		wrc.bottom - wrc.top,	//�E�B���h�E�c��
		nullptr,				//�e�E�B���h�E�n���h��
		nullptr,				//���j���[�n���h��
		w.hInstance,			//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);				//�I�v�V����

	//�E�B���h�E��\����Ԃɂ���
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::ProcessMesseage()
{
	MSG msg{};

	//���b�Z�[�W������H
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);//�L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg);//�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	//�E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}