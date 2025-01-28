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

namespace BOUDAMA
{
	//�R���X�g���N�^
	SubstanceBase::SubstanceBase()
	{
		addScoreNum = -1;
	}

	//�f�X�g���N�^
	SubstanceBase::~SubstanceBase()
	{
		owner_.reset();
	}

	//�����������֐�
	void SubstanceBase::Init(void)
	{

	}

	//�ǂݍ��ݏ����֐�
	void SubstanceBase::Load(int originalHandle)
	{
		//�������f���f�[�^�ǂݍ��ݏ���
		handle_ = MV1DuplicateModel(originalHandle);
	}

	//�s�������֐�
	void SubstanceBase::Step(void)
	{
		//�������Ă�����s��
		if (const auto& owner = GetOwner())
		{
			//�����������̂ɒǏ]
			Matrix3D retCalcMat = Matrix3D::GetTranslateMatrix(owner->GetPos())
				* Matrix3D::GetYawMatrix(owner->GetRotY())
				* Matrix3D::GetPitchMatrix(owner->GetRotX())
				* Matrix3D::GetRollMatrix(owner->GetRotZ())
				* Matrix3D::GetTranslateMatrix(-owner->GetPos() + dir_);

			pos_ = retCalcMat * owner->GetPos();

			//�ʒu�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}

		//�X�e�[�W�̒[����o�Ȃ��悤�ɂ���
		if (MyMath::Abs(pos_.x) > ALL_SUBSTANCE::MAX_POS_X_Z)
		{
			pos_.x = 0.0f < pos_.x ? ALL_SUBSTANCE::MAX_POS_X_Z : -ALL_SUBSTANCE::MAX_POS_X_Z;
		}
		if (MyMath::Abs(pos_.z) > ALL_SUBSTANCE::MAX_POS_X_Z)
		{
			pos_.z = 0.0f < pos_.z ? ALL_SUBSTANCE::MAX_POS_X_Z : -ALL_SUBSTANCE::MAX_POS_X_Z;
		}

		//�d�͏���������B�n�ʂ�艺�Ȃ��ɂ�����
		pos_.y - ALL_SUBSTANCE::GRAVITY > ALL_SUBSTANCE::GROUND_POS ? pos_.y -= ALL_SUBSTANCE::GRAVITY : pos_.y = ALL_SUBSTANCE::GROUND_POS;

		//���x���ق�0�Ȃ�
		if (velocity_.SquareL2Norm() < Common::KINDA_SMALL_NUMBER)
		{
			velocity_ = 0.0f;

			//�ʒu�ݒ�
			MV1SetPosition(handle_, pos_);
			MV1SetRotationXYZ(handle_, rot_);

			return;
		}

		//��������������
		velocity_ *= ALL_SUBSTANCE::RESISTANCE_POWER;

		//���̂𓮂���
		pos_ += velocity_ + dir_;

		//�ʒu�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�j�������֐�
	void SubstanceBase::Fin(void)
	{
		MV1DeleteModel(handle_);
		owner_.reset();
	}

	//�������֐�
	void SubstanceBase::AttachToObject(const std::shared_ptr<Object>& attachObject)
	{
		//�����������̂̏����擾 
		owner_ = attachObject;

		//�������玩�����g�܂ł̃x�N�g�����v�Z
		dir_ = pos_ - attachObject->GetPos();

		dir_ = Matrix3D::GetYawMatrix(attachObject->GetRotY())
			* Matrix3D::GetPitchMatrix(attachObject->GetRotX())
			* Matrix3D::GetRollMatrix(attachObject->GetRotZ())
			* dir_;

		SoundManager::GetInstance()->PlaySoundData(SOUND::SE::ATTACHED, DX_PLAYTYPE_BACK);
	}

	//�����蔻�菈��
	void SubstanceBase::HitCalculation(void)
	{
		dir_ = 0.0f;
		velocity_ = 0.0f;

	}

	//�����̏ꏊ�ɏo�����鏈��
	void SubstanceBase::appearCalculation(const Vector3D& appearPos)
	{
		//���ɏo�����Ă�������s���Ȃ�
		if (isAlive_)
		{
			return;
		}

		//���ґh��
		isAlive_ = true;

		//�o���ʒu���
		pos_ = appearPos;
	}

	//�����̏ꏊ�����юU��Ȃ���o�����鏈��
	void SubstanceBase::FlyAppearCalculation(const Vector3D& appearPos)
	{
		//���ɏo�����Ă�������s���Ȃ�
		if (isAlive_)
		{
			return;
		}

		//���ґh��
		isAlive_ = true;

		//�o���ʒu���
		pos_ = appearPos;

		//�����_���Ȋp�x�ŏ�����ɔ�юU��x�N�g������
		velocity_ = { static_cast<float>(GetRand(80)), 45.0f, static_cast<float>(GetRand(80)) };
	}

	//�v���C���[�ɋz�����܂��悤�ɒǂ������鏈��
	void SubstanceBase::ChasePosCalculation(const Vector3D& chasePos)
	{
		dir_ = 0.5f * (chasePos - pos_);
	}

	//���L�҂͖��G�ł͂Ȃ���Ԃ�
	bool SubstanceBase::IsOwnerNotInvincible(void) const
	{
		return Input::IsKeyKeep(GAME_INPUT::TURBO) || GetOwner()->GetVelocity().SquareL2Norm() < PLAYER::KILL_SPEED;

	}
}
