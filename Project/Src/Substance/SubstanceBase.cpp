#include "SubstanceBase.h"
#include "Math/MyMath.h"
#include "SubstanceParameter.h"
#include <Player/Player.h>
#include <Matrix/Matrix3D.h>
#include <Collision/Collision.h>
#include "Sound/Sound.h"
#include <Common.h>
#include <Input/Input.h>
#include <Input/InputParameter.h>

//コンストラクタ
SubstanceBase::SubstanceBase()
{
	addScoreNum = -1;
}

//デストラクタ
SubstanceBase::~SubstanceBase()
{
	owner_.reset();
}

//初期化処理関数
void SubstanceBase::Init(void)
{

}

//読み込み処理関数
void SubstanceBase::Load(int originalHandle)
{
	//複製モデルデータ読み込み処理
	handle_ = MV1DuplicateModel(originalHandle);
}

//行動処理関数
void SubstanceBase::Step(void)
{
	//くっついていたら行う
	if (!owner_.expired())
	{
		const std::shared_ptr<Object>& owner = GetOwner();

		//くっついたものに追従
		Matrix3D retCalcMat = Matrix3D::GetTranslateMatrix(owner->GetPos())
			* Matrix3D::GetYawMatrix(owner->GetRotY())
			* Matrix3D::GetPitchMatrix(owner->GetRotX())
			* Matrix3D::GetRollMatrix(owner->GetRotZ())
			* Matrix3D::GetTranslateMatrix(-owner->GetPos() + dir_);

		pos_ = retCalcMat * owner->GetPos();

		//位置設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);

		return;
	}

	//ステージの端から出ないようにする
	if (MyMath::Abs(pos_.x) > ALL_SUBSTANCE::MAX_POS_X_Z)
	{
		pos_.x = 0.0f < pos_.x ? ALL_SUBSTANCE::MAX_POS_X_Z : -ALL_SUBSTANCE::MAX_POS_X_Z;
	}
	if (MyMath::Abs(pos_.z) > ALL_SUBSTANCE::MAX_POS_X_Z)
	{
		pos_.z = 0.0f < pos_.z ? ALL_SUBSTANCE::MAX_POS_X_Z : -ALL_SUBSTANCE::MAX_POS_X_Z;
	}

	//重力処理をする。地面より下なら上にあげる
	pos_.y - ALL_SUBSTANCE::GRAVITY > ALL_SUBSTANCE::GROUND_POS ? pos_.y -= ALL_SUBSTANCE::GRAVITY : pos_.y = ALL_SUBSTANCE::GROUND_POS;

	//速度がほぼ0なら
	if (velocity_.SquareL2Norm() < Common::KINDA_SMALL_NUMBER)
	{
		velocity_ = 0.0f;
	}

	//減速処理をする
	velocity_ *= ALL_SUBSTANCE::RESISTANCE_POWER;

	//物体を動かす
	pos_ += velocity_ + dir_;

	//位置設定
	MV1SetPosition(handle_, pos_);
	MV1SetRotationXYZ(handle_, rot_);
}

//破棄処理関数
void SubstanceBase::Fin(void)
{
	MV1DeleteModel(handle_);
	owner_.reset();
}

//くっつく関数
void SubstanceBase::AttachToObject(const std::shared_ptr<Object>& attachObject)
{
	//当たった物体の情報を取得 
	owner_ = attachObject;

	//物質から自分自身までのベクトルを計算
	dir_ = pos_ - attachObject->GetPos();

	dir_ = Matrix3D::GetYawMatrix(attachObject->GetRotY())
		* Matrix3D::GetPitchMatrix(attachObject->GetRotX())
		* Matrix3D::GetRollMatrix(attachObject->GetRotZ())
		* dir_;

	SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ATTACHED, DX_PLAYTYPE_BACK);
}

//当たり判定処理
void SubstanceBase::HitCalculation(void)
{
	dir_ = 0.0f;
	velocity_ = 0.0f;

}

//引数の場所に出現する処理
void SubstanceBase::appearCalculation(const Vector3D& appearPos)
{
	//既に出現していたら実行しない
	if (isAlive_)
	{
		return;
	}

	//死者蘇生
	isAlive_ = true;

	//出現位置代入
	pos_ = appearPos;
}

//引数の場所から飛び散りながら出現する処理
void SubstanceBase::FlyAppearCalculation(const Vector3D& appearPos)
{
	//既に出現していたら実行しない
	if (isAlive_)
	{
		return;
	}

	//死者蘇生
	isAlive_ = true;

	//出現位置代入
	pos_ = appearPos;

	//ランダムな角度で上向きに飛び散るベクトルを代入
	velocity_ = { static_cast<float>(GetRand(80)), 45.0f, static_cast<float>(GetRand(80)) };
}

//プレイヤーに吸い込まれるように追いかける処理
void SubstanceBase::ChasePosCalculation(const Vector3D& chasePos)
{
	dir_ = 0.5f * (chasePos - pos_);
}

//所有者は無敵ではない状態か
bool SubstanceBase::IsOwnerNotInvincible(void) const
{
	return Input::IsKeyKeep(GAME_INPUT::TURBO) || GetOwner()->GetVelocity().SquareL2Norm() < PLAYER::KILL_SPEED;
		
}
