#include "SkyBox.h"
#include "SkyBoxParameter.h"
#include <DxLib.h>
#include <Math/MyMath.h>

namespace BOUDAMA
{
	//コンストラクタ
	SkyBox::SkyBox()
	{
		handle_ = -1;
	}

	//デストラクタ
	SkyBox::~SkyBox()
	{

	}

	//初期化処理関数
	void SkyBox::Init(void)
	{
		//初期化
		handle_ = -1;
		pos_ = MY_MATH::ZERO_VECTOR_3D;
		rot_ = MY_MATH::ZERO_VECTOR_3D;
	}

	//読み込み処理関数
	void SkyBox::Load(void)
	{
		//読み込み
		handle_ = MV1LoadModel(SKY_BOX::SKY_BOX_PATH);

		//大きさ調整
		MV1SetScale(handle_, SKY_BOX::SCALE_MULTIPLE);
	}

	//行動処理関数
	void SkyBox::Step(void)
	{
		//Y軸を回転させる
		rot_.y += SKY_BOX::SKY_BOX_ROT_SPEED;

		//回転を反映させる
		MV1SetRotationXYZ(handle_, rot_);
	}

	//描画処理関数
	void SkyBox::Draw(void)
	{
		//表示
		MV1DrawModel(handle_);
	}

	//破棄処理関数
	void SkyBox::Fin(void)
	{
		//ハンドルが存在したら削除
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}
	}
}
