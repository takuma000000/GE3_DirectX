#pragma once
#include <memory>

//前方宣言
class WindowsAPI;
class DirectXCommon;
class SrvManager;

class Framework
{
public:
	// 仮想関数（派生クラスで必ず実装する必要がある）
	virtual void Initialize();   // 初期化
	virtual void Finalize();     // 終了
	virtual void Update();       // 毎フレーム更新

	// 純粋仮想関数（必ずオーバーライドしないとエラーになる）
	virtual void Draw() = 0;     // 描画

	// ゲーム終了のチェック
	virtual bool IsEndRequest() { return endRequest_; }

	virtual ~Framework() = default;

	//実行
	void Run();

	// 初期化した共通機能を派生クラスで使えるようにするためのアクセサ
	WindowsAPI* GetWindowsAPI() const { return windowsAPI.get(); }
	DirectXCommon* GetDirectXCommon() const { return dxCommon.get(); }
	SrvManager* GetSrvManager() const { return srvManager.get(); }

protected:
	bool endRequest_ = false;    // 終了フラグ

	// 汎用メンバ変数
	std::unique_ptr<WindowsAPI> windowsAPI;
	std::unique_ptr<DirectXCommon> dxCommon;
	std::unique_ptr<SrvManager> srvManager;
};

