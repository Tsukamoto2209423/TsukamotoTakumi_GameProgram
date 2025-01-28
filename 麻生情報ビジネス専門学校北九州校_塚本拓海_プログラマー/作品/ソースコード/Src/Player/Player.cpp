#include "Player.h"
#include <math.h>
#include "Math/MyMath.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Input/GamePad/GamePad.h"
#include "Input/Mouse/Mouse.h"
#include "Common.h"
#include "Player/PlayerParameter.h"
#include <Matrix/Matrix3D.h>
#include <Camera/Camera.h>
#include <Camera/CameraManager.h>
#include "Sound/Sound.h"
#include <Input/Input.h>
#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerParameter.h>

namespace BOUDAMA
{
	//コンストラクタ
	Player::Player(void)
	{
		//初期化
		handle_ = -1;
		hp_ = 0;
		isAlive_ = true;
		pos_ = PLAYER::INIT_POS;
		deathTimeCount_ = 0;
	}

	//デストラクタ
	Player::~Player(void)
	{

	}

	//初期化処理関数
	void Player::Init(void)
	{
		//初期化
		handle_ = -1;
		isAlive_ = true;
		radius_ = PLAYER::RADIUS;
		hp_ = PLAYER::MAX_HP;
		pos_ = PLAYER::INIT_POS;
		dir_ = { 0.0f,0.0f,-1.0f };
		rot_ = { 0.0f,0.0f,0.0f };
		velocity_ = MyMath::ZERO_VECTOR_3D;
		deathTimeCount_ = 0;

		player2dEffect_.Init();
		player3dEffect_.Init();

		combo_.Init();
	}

	//読み込み処理関数
	void Player::Load(void)
	{
		//ハンドル未設定の場合、読み込む
		if (handle_ == -1)
		{
			handle_ = MV1LoadModel(PLAYER::PATH);
			player2dEffect_.Load();
			player3dEffect_.Load();
			combo_.Load();
		}
	}

	//行動処理関数
	void Player::Step(void)
	{
		//死亡していたら実行しない
		if (!isAlive_)
		{
			return;
		}

		if (Input::IsKeyPush(GAME_INPUT::TURBO))
		{
			dir_ = MyMath::ZERO_VECTOR_3D;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//ターボキーが押されているなら
		Input::IsKeyKeep(GAME_INPUT::TURBO) ?
			//ターボチャージ
			TurboCharge() :
			//移動計算処理
			MoveCalculation();


		player2dEffect_.Step();
		player3dEffect_.Step();
		combo_.Step();



		if (Input::IsKeyPush(GAME_INPUT::ENTER))
		{
			player2dEffect_.EffectRequest(PLAYER_EFFECT::HEAL);
			player3dEffect_.EffectRequest(EFFECT_HANDLE::HEAL_INDEX, pos_, rot_.y);
		}
	}

	//描画処理関数
	void Player::Draw(void)
	{
		//生存していない場合は描画しない
		if (!isAlive_)
		{
			return;
		}

		//生存している場合は描画
		MV1DrawModel(handle_);

		player2dEffect_.Draw(hp_, velocity_);
		player3dEffect_.Draw();

		//コンボ表示する
		combo_.Draw();
	}

	//破棄処理関数
	void Player::Fin(void)
	{
		//破棄処理
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}

		player2dEffect_.Fin();
		player3dEffect_.Fin();

		combo_.Fin();

		//空なら戻る
		if (attachedSubstances_.empty())
		{
			return;
		}


		for (auto&& attachSubstance = attachedSubstances_.cbegin(); attachSubstance != attachedSubstances_.cend();)
		{
			attachSubstance = attachedSubstances_.erase(attachSubstance);
		}

		//配列削除
		attachedSubstances_.clear();
		//領域を解放する
		attachedSubstances_.shrink_to_fit();

	}

	//当たり判定処理
	void Player::HitCalculation(void)
	{
		SubHP();

		//死亡処理
		if (hp_ <= 0)
		{
			DeathEvent();

			return;
		}

		//エフェクトと音
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ + PLAYER::EFFECT_POS, false);
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ - PLAYER::EFFECT_POS, false);

		//ダメージを受けた音
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DAMAGE, DX_PLAYTYPE_BACK);

	}
	
	//当たり判定処理
	void Player::HitCalculation(int damage)
	{
		SubHP(damage);

		//死亡処理
		if (hp_ <= 0)
		{
			DeathEvent();

			return;
		}

		//エフェクトと音
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ + PLAYER::EFFECT_POS, false);
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ - PLAYER::EFFECT_POS, false);

		//ダメージを受けた音
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DAMAGE, DX_PLAYTYPE_BACK);

	}

	//移動計算処理
	void Player::MoveCalculation(void)
	{
		//初期化
		dir_ = MyMath::ZERO_VECTOR_3D;

		//上移動
		if (InputKeyBoard::IsKeyKeep(KEY::W))
		{
			dir_.z += 1.0f;
		}

		//下移動
		if (InputKeyBoard::IsKeyKeep(KEY::S))
		{
			dir_.z -= 1.0f;
		}

		//左移動
		if (InputKeyBoard::IsKeyKeep(KEY::A))
		{
			dir_.x -= 1.0f;
		}

		//右移動
		if (InputKeyBoard::IsKeyKeep(KEY::D))
		{
			dir_.x += 1.0f;
		}

		//ゲームパッドに入力された値も加算する
		dir_ += InputGamePad::GetLStickVector();

		//入力された場合実行する
		if (MyMath::Abs(dir_.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(dir_.z) > Common::KINDA_SMALL_NUMBER)
		{
			//速度が一定以下なら実行する
			if (MyMath::Abs(velocity_.x) < PLAYER::MAX_SPEED && MyMath::Abs(velocity_.z) < PLAYER::MAX_SPEED)
			{
				//カメラの角度に合わせて方向ベクトルをY軸周りに回転
				dir_ *= Matrix3D::GetYawMatrix(CameraManager::GetInstance()->GetPlayCamera()->GetRotY());

				//入力した値を単位ベクトルにしてプレイヤーの速さでスカラー倍し加算
				velocity_ += dir_.Normalize() * PLAYER::SPEED;

			}

			//プレイヤーの速度ベクトルの角度を計算し、プレイヤーが向く角度を決める
			RotateYaw(velocity_);
		}

		//摩擦力計算
		velocity_.x *= PLAYER::KINETIC_FRICTION_COEFFICIENT;
		velocity_.z *= PLAYER::KINETIC_FRICTION_COEFFICIENT;


		if (MyMath::Abs(velocity_.x) <= Common::KINDA_SMALL_NUMBER)
		{
			velocity_.x = 0.0f;
		}
		if (MyMath::Abs(velocity_.z) <= Common::KINDA_SMALL_NUMBER)
		{
			velocity_.z = 0.0f;
		}

		//移動しているなら
		if (MyMath::Abs(velocity_.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(velocity_.z) > Common::KINDA_SMALL_NUMBER)
		{
			//転がっている時の角度計算
			RotateCalculation();
		}

		//位置加算
		pos_ += velocity_;

		//重力加算
		pos_.y -= PLAYER::GRAVITY;

		//地面より下に行かないようにする
		if (pos_.y < PLAYER::GROUND_POS_Y)
		{
			pos_.y = PLAYER::GROUND_POS_Y;
			velocity_.y = 0.0f;
		}

		//ステージの端から出ないようにする
		if (MyMath::Abs(pos_.x) > PLAYER::MAX_POS_X_Z)
		{
			pos_.x = 0.0f < pos_.x ? PLAYER::MAX_POS_X_Z : -PLAYER::MAX_POS_X_Z;
		}
		if (MyMath::Abs(pos_.z) > PLAYER::MAX_POS_X_Z)
		{
			pos_.z = 0.0f < pos_.z ? PLAYER::MAX_POS_X_Z : -PLAYER::MAX_POS_X_Z;
		}

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//回転計算処理
	void Player::RotateCalculation(void)
	{
		//転がっている時の角度計算
		MyMath::Abs(rot_.x) < MyMath::TWO_PI ?
			rot_.x -= PLAYER::ROTATION_COEFFICIENT * velocity_.L2Norm() * MyMath::INVERSE_TWO_PI :
			rot_.x = 0.0f;
	}

	//ターボを溜める
	void Player::TurboCharge(void)
	{
		//カメラの角度に合わせて方向ベクトルを決める
		dir_.z += PLAYER::TURBO_CHARGE_POWER;
		velocity_ = Matrix3D::GetYawMatrix(CameraManager::GetInstance()->GetPlayCamera()->GetRotY()) * dir_;

		//プレイヤーの速度ベクトルの角度を計算し、プレイヤーが向く角度を決める
		RotateYaw(velocity_);
		

		//転がっている時の角度計算
		RotateCalculation();

		player3dEffect_.EffectRequest(EFFECT_HANDLE::CHARGE_INDEX, pos_, rot_.y);

		//位置・角度設定
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//死亡イベント
	void Player::DeathEvent(void)
	{
		isAlive_ = false;

		CEffekseerCtrl::StopAll();

		CEffekseerCtrl::Request(EFFECT_CALL[EFFECT_HANDLE::DEATH_INDEX], pos_, false);

		//死亡音
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::RED_DISSOLVE, DX_PLAYTYPE_BACK);
	}


	bool Player::IsEndDeathEvent(void)
	{
		++deathTimeCount_;

		return  PLAYER::DEATH_EFFECT_TIME < deathTimeCount_;
	}

	//無敵かどうか
	bool Player::IsInvincible(void)
	{
		//ターボ状態なら無敵ではないのでfalse
		if (Input::IsKeyKeep(GAME_INPUT::TURBO))
		{
			return false;
		}

		//もしプレイヤーがカソク状態なら無敵判定
		if (velocity_.SquareL2Norm() > PLAYER::KILL_SPEED)
		{
			return true;
		}

		//そうでないなら無敵ではない
		return false;

	}
}
