#include "Player/Player3DEffect.h"
#include "Player.h"
#include "Effekseer/Effekseer.h"
#include "Effekseer/EffekseerParameter.h"

namespace BOUDAMA
{
	//�����������֐�
	void Player3DEffect::Init(void)
	{
		for (int effectCallNum : EFFECT_CALL)
		{
			effectHandle_.push_back(-1);
		}
	}

	//�ǂݍ��ݏ����֐�
	void Player3DEffect::Load(void)
	{

	}

	//�s�������֐�
	void Player3DEffect::Step(void)
	{

	}

	//�`�揈���֐�
	void Player3DEffect::Draw(void)
	{

	}

	//�j�������֐�
	void Player3DEffect::Fin(void)
	{

	}

	//�G�t�F�N�g�\��
	void Player3DEffect::EffectRequest(EFFECT_HANDLE effectNum, const Vector3D& appearPos, float rotY)
	{
		effectHandle_[effectNum] = CEffekseerCtrl::Request(EFFECT_CALL[effectNum], appearPos, false);
		CEffekseerCtrl::SetRot(effectHandle_[effectNum], VECTOR(0.0f, rotY, 0.0f));
		CEffekseerCtrl::SetPosition(effectHandle_[effectNum], appearPos);
	}
}
