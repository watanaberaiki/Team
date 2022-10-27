#pragma once
#include <Windows.h>

class WinApp
{
public://定数
	//ウィンドウサイズ
	static const int window_width = 1280;//横幅
	static const int window_height = 720;//縦幅

public://静的メンバ関数
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public://メンバ関数
	//初期化
	void Initialize();
	//メッセージの処理
	bool ProcessMesseage();
	//終了
	void Finalize();

	//ゲッター
	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }

private://メンバ変数
	//ウィンドウハンドル
	HWND hwnd = nullptr;
	//ウィンドウクラスの設定
	WNDCLASSEX w{};
};
