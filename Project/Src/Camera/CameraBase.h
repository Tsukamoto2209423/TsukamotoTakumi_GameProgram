#pragma once
#include <Vector/Vector3D.h>

//カメラ基底クラス
class CameraBase
{
protected:
	//位置
	Vector3D pos_;

	//注視点
	Vector3D target_;

	//上方向
	Vector3D up_;

	//回転
	Vector3D rot_;

	//カメラの正面方向ベクトル
	Vector3D dir_;

public:
	//コンストラクタ
	CameraBase() {}

	//デストラクタ
	virtual ~CameraBase() {}

	//初期化処理関数
	virtual void Init(void) = 0;

	//移動処理関数
	virtual void Step(const Vector3D& playerPos) = 0;

	//更新関数
	virtual void UpDate(void) = 0;

	//XYZ座標取得
	inline Vector3D GetPos(void) const { return pos_; }

	//XYZ座標設定
	inline void SetPos(float x, float y, float z) { pos_.x = x; pos_.y = y; pos_.z = z; }

	//XYZ座標設定
	inline void SetPos(const Vector3D& pos) { pos_ = pos; }

	//X軸取得
	inline float GetPosX(void) const { return pos_.x; }

	//X軸設定
	inline void SetPosX(float x) { pos_.x = x; }

	//Y軸取得
	inline float GetPosY(void) const { return pos_.y; }

	//Y軸設定
	inline void SetPosY(float y) { pos_.y = y; }

	//Z軸取得
	inline float GetPosZ(void) const { return pos_.z; }

	//Z軸設定
	inline void SetPosZ(float z) { pos_.z = z; }


	//注視点取得
	inline Vector3D GetTarget(void) const { return target_; }

	//注視点取得
	inline void SetTarget(const Vector3D& target) { target_ = target; }


	//上方向取得
	inline Vector3D GetUp(void) const { return up_; }

	//上方向設定
	inline void SetUp(const Vector3D& up) { up_ = up; }


	//回転軸取得
	inline Vector3D GetRot(void) const { return rot_; }

	//回転軸設定
	inline void SetRot(const Vector3D& rot) { rot_ = rot; }

	//X軸取得
	inline float GetRotX(void) const { return rot_.x; }

	//X軸設定
	inline void SetRotX(float x) { rot_.x = x; }

	//Y軸取得
	inline float GetRotY(void) const { return rot_.y; }

	//Y軸設定
	inline void SetRotY(float y) { rot_.y = y; }

	//Z軸取得
	inline float GetRotZ(void) const { return rot_.z; }

	//Z軸設定
	inline void SetRotZ(float z) { rot_.z = z; }


	//方向ベクトル取得
	inline Vector3D GetDir(void) const { return dir_; }

	//方向ベクトル設定
	inline void SetDir(const Vector3D& dir) { dir_ = dir; }

};