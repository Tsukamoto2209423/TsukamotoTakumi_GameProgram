#pragma once

#include <vector>
#include "CameraBase.h"

#include <memory>

#ifdef _DEBUG
#define New new(_NORMAL_BLOCK,__FILE__,__LINE__)

#else
#define New new

#endif // DEBUG

enum CAMERA_STATE
{
	PLAY,
	DEBUG,
};

class CameraManager
{
private:
	static inline std::shared_ptr<CameraManager> instance_;

	std::vector<std::shared_ptr<CameraBase>> cameras_;

	CAMERA_STATE state_;

public:
	//コンストラクタ
	CameraManager() { state_ = CAMERA_STATE::PLAY; }

	//デストラクタ
	~CameraManager() {}

	//コピーコンストラクタ
	CameraManager(const CameraManager& other) = delete;
	CameraManager& operator=(const CameraManager& other) = delete;

	//インスタンス生成・取得
	static inline std::shared_ptr<CameraManager> GetInstance(void)
	{ return instance_ ? instance_ : instance_ = std::make_shared<CameraManager>(); }

	//カメラ情報取得
	std::vector<std::shared_ptr<CameraBase>>& GetCamera(void) { return cameras_; }

	//通常のカメラ情報取得
	static std::shared_ptr<CameraBase> &GetPlayCamera(void) { return GetInstance()->GetCamera()[CAMERA_STATE::PLAY]; }

	//デバッグのカメラ情報取得
	static std::shared_ptr<CameraBase> &GetDebugCamera(void) { return GetInstance()->GetCamera()[CAMERA_STATE::DEBUG]; }

	//カメラの状態取得
	inline CAMERA_STATE GetState(void) const { return state_; }

	//初期化処理関数
	void Init(void);

	//移動処理関数
	void Step(const Vector3D& playerPos);

	//更新関数
	void UpDate(void);

	//破棄処理関数
	void Fin(void);

};
