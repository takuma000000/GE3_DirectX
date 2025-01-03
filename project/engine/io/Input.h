#pragma once
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
#include "WindowsAPI.h"

//入力
class Input
{
public:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public://メンバ関数

	// シングルトンインスタンスの取得
	static Input* GetInstance();

	Input() = default;
	~Input() = default;
	Input(Input&) = delete;
	Input& operator=(Input&) = delete;

	//初期化
	void Initialize(WindowsAPI* winApp);
	//終了
	void Finalize();
	//更新
	void Update();
	//キーの押下をチェック( 押されているか )
	bool PushKey(BYTE keyNumber);

	//キーのトリガーをチェック
	bool TriggerKey(BYTE keyNumber);

private://メンバ変数

	static Input* instance;

	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;
	//全キーの状態
	BYTE key[256] = {};
	//前回の全キーの状態
	BYTE keyPre[256] = {};
	//DirectInputのインスタンス
	ComPtr<IDirectInput8> directInput;
	//WindowsAPI
	WindowsAPI* winApp = nullptr;

};