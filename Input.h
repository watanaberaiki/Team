#pragma once
#include "winApp.h"
#include <windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION 0x0800 //directInputのバージョン指定
#include <dinput.h>

//入力
class Input
{
public:
	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://メンバ関数
	//初期化
	void Initialize(WinApp* winApp);
	//更新
	void Update();
	//キーの押下をチェック
	bool PushKey(BYTE keyNumber);
	//キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);

private://メンバ変数
	//WindowsAPI
	WinApp* winApp = nullptr;

	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput = nullptr;

	ComPtr<IDirectInputDevice8> keyboard;

	//全キーの入力状態を取得する
	BYTE key[256] = {};
	//前回の全キーの状態
	BYTE keyPre[256] = {};
};