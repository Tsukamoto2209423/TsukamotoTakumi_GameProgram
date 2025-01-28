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
	//�R���X�g���N�^
	Player::Player(void)
	{
		//������
		handle_ = -1;
		hp_ = 0;
		isAlive_ = true;
		pos_ = PLAYER::INIT_POS;
		deathTimeCount_ = 0;
	}

	//�f�X�g���N�^
	Player::~Player(void)
	{

	}

	//�����������֐�
	void Player::Init(void)
	{
		//������
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

	//�ǂݍ��ݏ����֐�
	void Player::Load(void)
	{
		//�n���h�����ݒ�̏ꍇ�A�ǂݍ���
		if (handle_ == -1)
		{
			handle_ = MV1LoadModel(PLAYER::PATH);
			player2dEffect_.Load();
			player3dEffect_.Load();
			combo_.Load();
		}
	}

	//�s�������֐�
	void Player::Step(void)
	{
		//���S���Ă�������s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		if (Input::IsKeyPush(GAME_INPUT::TURBO))
		{
			dir_ = MyMath::ZERO_VECTOR_3D;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//�^�[�{�L�[��������Ă���Ȃ�
		Input::IsKeyKeep(GAME_INPUT::TURBO) ?
			//�^�[�{�`���[�W
			TurboCharge() :
			//�ړ��v�Z����
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

	//�`�揈���֐�
	void Player::Draw(void)
	{
		//�������Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//�������Ă���ꍇ�͕`��
		MV1DrawModel(handle_);

		player2dEffect_.Draw(hp_, velocity_);
		player3dEffect_.Draw();

		//�R���{�\������
		combo_.Draw();
	}

	//�j�������֐�
	void Player::Fin(void)
	{
		//�j������
		if (handle_ != -1)
		{
			MV1DeleteModel(handle_);
			handle_ = -1;
		}

		player2dEffect_.Fin();
		player3dEffect_.Fin();

		combo_.Fin();

		//��Ȃ�߂�
		if (attachedSubstances_.empty())
		{
			return;
		}


		for (auto&& attachSubstance = attachedSubstances_.cbegin(); attachSubstance != attachedSubstances_.cend();)
		{
			attachSubstance = attachedSubstances_.erase(attachSubstance);
		}

		//�z��폜
		attachedSubstances_.clear();
		//�̈���������
		attachedSubstances_.shrink_to_fit();

	}

	//�����蔻�菈��
	void Player::HitCalculation(void)
	{
		SubHP();

		//���S����
		if (hp_ <= 0)
		{
			DeathEvent();

			return;
		}

		//�G�t�F�N�g�Ɖ�
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ + PLAYER::EFFECT_POS, false);
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ - PLAYER::EFFECT_POS, false);

		//�_���[�W���󂯂���
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DAMAGE, DX_PLAYTYPE_BACK);

	}
	
	//�����蔻�菈��
	void Player::HitCalculation(int damage)
	{
		SubHP(damage);

		//���S����
		if (hp_ <= 0)
		{
			DeathEvent();

			return;
		}

		//�G�t�F�N�g�Ɖ�
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ + PLAYER::EFFECT_POS, false);
		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, pos_ - PLAYER::EFFECT_POS, false);

		//�_���[�W���󂯂���
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::DAMAGE, DX_PLAYTYPE_BACK);

	}

	//�ړ��v�Z����
	void Player::MoveCalculation(void)
	{
		//������
		dir_ = MyMath::ZERO_VECTOR_3D;

		//��ړ�
		if (InputKeyBoard::IsKeyKeep(KEY::W))
		{
			dir_.z += 1.0f;
		}

		//���ړ�
		if (InputKeyBoard::IsKeyKeep(KEY::S))
		{
			dir_.z -= 1.0f;
		}

		//���ړ�
		if (InputKeyBoard::IsKeyKeep(KEY::A))
		{
			dir_.x -= 1.0f;
		}

		//�E�ړ�
		if (InputKeyBoard::IsKeyKeep(KEY::D))
		{
			dir_.x += 1.0f;
		}

		//�Q�[���p�b�h�ɓ��͂��ꂽ�l�����Z����
		dir_ += InputGamePad::GetLStickVector();

		//���͂��ꂽ�ꍇ���s����
		if (MyMath::Abs(dir_.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(dir_.z) > Common::KINDA_SMALL_NUMBER)
		{
			//���x�����ȉ��Ȃ���s����
			if (MyMath::Abs(velocity_.x) < PLAYER::MAX_SPEED && MyMath::Abs(velocity_.z) < PLAYER::MAX_SPEED)
			{
				//�J�����̊p�x�ɍ��킹�ĕ����x�N�g����Y������ɉ�]
				dir_ *= Matrix3D::GetYawMatrix(CameraManager::GetInstance()->GetPlayCamera()->GetRotY());

				//���͂����l��P�ʃx�N�g���ɂ��ăv���C���[�̑����ŃX�J���[�{�����Z
				velocity_ += dir_.Normalize() * PLAYER::SPEED;

			}

			//�v���C���[�̑��x�x�N�g���̊p�x���v�Z���A�v���C���[�������p�x�����߂�
			RotateYaw(velocity_);
		}

		//���C�͌v�Z
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

		//�ړ����Ă���Ȃ�
		if (MyMath::Abs(velocity_.x) > Common::KINDA_SMALL_NUMBER || MyMath::Abs(velocity_.z) > Common::KINDA_SMALL_NUMBER)
		{
			//�]�����Ă��鎞�̊p�x�v�Z
			RotateCalculation();
		}

		//�ʒu���Z
		pos_ += velocity_;

		//�d�͉��Z
		pos_.y -= PLAYER::GRAVITY;

		//�n�ʂ�艺�ɍs���Ȃ��悤�ɂ���
		if (pos_.y < PLAYER::GROUND_POS_Y)
		{
			pos_.y = PLAYER::GROUND_POS_Y;
			velocity_.y = 0.0f;
		}

		//�X�e�[�W�̒[����o�Ȃ��悤�ɂ���
		if (MyMath::Abs(pos_.x) > PLAYER::MAX_POS_X_Z)
		{
			pos_.x = 0.0f < pos_.x ? PLAYER::MAX_POS_X_Z : -PLAYER::MAX_POS_X_Z;
		}
		if (MyMath::Abs(pos_.z) > PLAYER::MAX_POS_X_Z)
		{
			pos_.z = 0.0f < pos_.z ? PLAYER::MAX_POS_X_Z : -PLAYER::MAX_POS_X_Z;
		}

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//��]�v�Z����
	void Player::RotateCalculation(void)
	{
		//�]�����Ă��鎞�̊p�x�v�Z
		MyMath::Abs(rot_.x) < MyMath::TWO_PI ?
			rot_.x -= PLAYER::ROTATION_COEFFICIENT * velocity_.L2Norm() * MyMath::INVERSE_TWO_PI :
			rot_.x = 0.0f;
	}

	//�^�[�{�𗭂߂�
	void Player::TurboCharge(void)
	{
		//�J�����̊p�x�ɍ��킹�ĕ����x�N�g�������߂�
		dir_.z += PLAYER::TURBO_CHARGE_POWER;
		velocity_ = Matrix3D::GetYawMatrix(CameraManager::GetInstance()->GetPlayCamera()->GetRotY()) * dir_;

		//�v���C���[�̑��x�x�N�g���̊p�x���v�Z���A�v���C���[�������p�x�����߂�
		RotateYaw(velocity_);
		

		//�]�����Ă��鎞�̊p�x�v�Z
		RotateCalculation();

		player3dEffect_.EffectRequest(EFFECT_HANDLE::CHARGE_INDEX, pos_, rot_.y);

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//���S�C�x���g
	void Player::DeathEvent(void)
	{
		isAlive_ = false;

		CEffekseerCtrl::StopAll();

		CEffekseerCtrl::Request(EFFECT_CALL[EFFECT_HANDLE::DEATH_INDEX], pos_, false);

		//���S��
		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::RED_DISSOLVE, DX_PLAYTYPE_BACK);
	}


	bool Player::IsEndDeathEvent(void)
	{
		++deathTimeCount_;

		return  PLAYER::DEATH_EFFECT_TIME < deathTimeCount_;
	}

	//���G���ǂ���
	bool Player::IsInvincible(void)
	{
		//�^�[�{��ԂȂ疳�G�ł͂Ȃ��̂�false
		if (Input::IsKeyKeep(GAME_INPUT::TURBO))
		{
			return false;
		}

		//�����v���C���[���J�\�N��ԂȂ疳�G����
		if (velocity_.SquareL2Norm() > PLAYER::KILL_SPEED)
		{
			return true;
		}

		//�����łȂ��Ȃ疳�G�ł͂Ȃ�
		return false;

	}
}
