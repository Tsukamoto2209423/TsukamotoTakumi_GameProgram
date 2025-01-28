#include "Bomb.h"
#include <Math/MyMath.h>
#include "Effekseer/Effekseer.h"
#include <EffekseerParameter.h>

namespace BOUDAMA
{
	//�����������֐�
	void Bomb::Init(void)
	{
		//������
		handle_ = -1;
		state_ = BOMB_STATE::NORMAL;
		isAlive_ = false;
		hp_ = 1;
		radius_ = BOMB::RADIUS;
		pos_ = MyMath::ZERO_VECTOR_3D;
		velocity_ = MyMath::ZERO_VECTOR_3D;
		rot_ = MyMath::ZERO_VECTOR_3D;

		countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

		playerOnlyEffect_ = false;
	}

	//�s�������֐�
	void Bomb::Step(void)
	{
		(this->*MoveFunctionPointer[state_])();
	}

	//�`�揈���֐�
	void Bomb::Draw(void)
	{
		if (!isAlive_ || state_ == BOMB_STATE::EXPLOSION)
		{
			return;
		}

		//�������Ă���ꍇ�͕`��
		MV1DrawModel(handle_);
	}


	//�o�������֐�
	void Bomb::AppearanceRequest(void)
	{
		isAlive_ = true;
		Ignite();
	}

	//�A�C�e���̌��ʎ��s
	void Bomb::EffectExecute(const std::shared_ptr<Object>& targetObject)
	{
		const Vector3D& myPosToTargetVector = targetObject->GetPos() - pos_;

		//�����ɉ����ė^���鑬�x�x�N�g���̒�����ς���
		const Vector3D& addExplosionVelocity = (BOMB::EXPLOSION_BOOST / myPosToTargetVector.L2Norm()) * myPosToTargetVector;

		targetObject->AddVelocity(addExplosionVelocity);

		targetObject->HitCalculation(BOMB::ATTACK_POWER);

		CEffekseerCtrl::Request(EFFECT::HIT_EFFECT, targetObject->GetPos(), false);
	}

	//���������Ƃ��̏���
	void Bomb::HitCalculation(void)
	{
		if (state_ != BOMB_STATE::EXPLOSION)
		{
			MoveTrigger();
		}
	}

	//���e�ɉ΂�����
	void Bomb::Ignite(void)
	{
		state_ = BOMB_STATE::IGNITION;
	}

	void Bomb::MoveNormal(void)
	{
		//�������Ă��Ȃ���Ύ��s���Ȃ�
		if (!isAlive_)
		{
			return;
		}

		//Y���̂��邮���]���鏈��
		rot_.y = rot_.y >= MyMath::TWO_PI - MyMath::PI_OVER_TWENTY ? 0.0f : rot_.y + MyMath::PI_OVER_TWENTY;

		//���W�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//���΂��ē�����ꂽ�Ƃ��̏���
	void Bomb::MoveIgnition(void)
	{
		//��������܂ł̎��Ԍv��
		--countExplodeTimeLimit_;

		if (countExplodeTimeLimit_ == BOMB::WARNING_BLINK_TIME)
		{
			//�����x���_��
			int handle = CEffekseerCtrl::Request(EFFECT::RED_DISSOLVE, pos_, false);
			CEffekseerCtrl::SetScale(handle, VECTOR(1.55f, 1.55f, 1.55f));
		}

		//�����܂ł̃J�E���g�_�E����0�ɂȂ�����
		if (countExplodeTimeLimit_ <= 0)
		{
			//���̏�Ŕ�����ԂɑJ��
			state_ = BOMB_STATE::TRIGGER;

			countExplodeTimeLimit_ = BOMB::MAX_EXPLODE_TIME_LIMIT;

			radius_ = BOMB::EXPLODE_RADIUS;

			return;
		}

		pos_ += velocity_;

		velocity_.y -= BOMB::GRAVITY;

		//�d�͏���
		if (pos_.y <= BOMB::GROUND_POS)
		{
			pos_.y = BOMB::GROUND_POS;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//��ʊO�ɏo���ꍇ�A���S����
		if (MyMath::Abs(pos_.x) > BOMB::MAX_POS_X_Z || MyMath::Abs(pos_.z) > BOMB::MAX_POS_X_Z)
		{
			isAlive_ = false;
			velocity_ = MyMath::ZERO_VECTOR_3D;
		}

		//�ʒu�E�p�x�ݒ�
		MV1SetPosition(handle_, pos_);
		MV1SetRotationXYZ(handle_, rot_);
	}

	//�������N�������u�Ԃ̏��
	void Bomb::MoveTrigger(void)
	{
		state_ = BOMB_STATE::EXPLOSION;
		CEffekseerCtrl::Request(EFFECT::EXPLOSION, pos_, false);
		radius_ = BOMB::EXPLODE_RADIUS;
	}

	//�������Ă���Ƃ��̏���
	void Bomb::MoveExplosion(void)
	{
		//�������̎��Ԍv��
		++explosionTime_;

		//�������Ԃ��ő�܂ōs������
		if (BOMB::MAX_EXPLOSION_TIME <= explosionTime_)
		{
			isAlive_ = false;
			state_ = BOMB_STATE::NORMAL;
			explosionTime_ = 0;
			radius_ = BOMB::RADIUS;
		}
	}
}
