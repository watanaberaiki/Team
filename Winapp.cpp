#include "WinApp.h"

//ウィンドウプロシージャ
/*ウィンドウ・・・コンピュータの操作画面上で個々のソフトウェアに割り当てられた矩形の表示領域*/
/*ウィンドウプロシージャ・・・ウィンドウメッセージを処理する関数
メッセージループで取得したメッセージをウィンドウプロシージャに送信し、受け取ったメッセージをウィンドウプロシージャで処理する*/
LRESULT WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		//ウィンドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		/*OS・・・コンピューターを動かすためのソフトウェアのこと
		Operating System オペレーティング システムの略
		コンピューター全体を管理、制御し、人が使えるようにする役割がある*/
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}


void WinApp::Initialize()
{
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;	//ウィンドウプロシージャを設定
	w.lpszClassName = L"DirectXGame";		//ウィンドウクラス名
	/*ウィンドウクラス・・・「どのようなウィンドウを作るかの定義」のこと
	アイコン、メニュー、カーソルなどと、ウィンドウプロシージャが定義されている*/
	w.hInstance = GetModuleHandle(nullptr);	//ウィンドウハンドル
	/*ウィンドウハンドル・・・コンピュータが各ウィンドウに割り振る管理番号
	これを指定することで、コンピュータに該当のウィンドウを認識させる*/
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル指名

	//ウィンドウクラスをOSに登録する
	RegisterClassEx(&w);
	//ウィンドウサイズ{X座標 Y座標 横幅 縦幅}
	RECT wrc = { 0, 0, window_width, window_height };
	//自動でサイズを補修する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(w.lpszClassName,//クラス名
		L"DirectXGame",			//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//標準的なウィンドウスタイル
		CW_USEDEFAULT,			//表示X座標(OSに任せる)
		CW_USEDEFAULT,			//表示Y座標(OSに任せる)
		wrc.right - wrc.left,	//ウィンドウ横幅
		wrc.bottom - wrc.top,	//ウィンドウ縦幅
		nullptr,				//親ウィンドウハンドル
		nullptr,				//メニューハンドル
		w.hInstance,			//呼び出しアプリケーションハンドル
		nullptr);				//オプション

	//ウィンドウを表示状態にする
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::ProcessMesseage()
{
	MSG msg{};

	//メッセージがある？
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);//キー入力メッセージの処理
		DispatchMessage(&msg);//プロシージャにメッセージを送る
	}

	//×ボタンで終了メッセージが来たらゲームループを抜ける
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}

void WinApp::Finalize()
{
	//ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}