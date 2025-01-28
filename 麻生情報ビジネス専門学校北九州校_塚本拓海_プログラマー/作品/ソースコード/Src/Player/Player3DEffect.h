#pragma once

#include <vector>

#include <Vector/Vector3D.h>

#include <EffekseerParameter.h>

namespace BOUDAMA
{
	//�G�t�F�N�g�n���h���z��̓Y����
	enum EFFECT_HANDLE
	{
		CHARGE_INDEX,
		DAMAGE_INDEX,
		DEATH_INDEX,
		HEAL_INDEX
	};

	//�G�t�F�N�g���̂�ۑ����Ă���z��̓Y�������Ăяo�����Ɏg���ԍ�
	constexpr int EFFECT_CALL[] =
	{
		EFFECT::CHARGE,
		EFFECT::HIT_EFFECT,
		EFFECT::RED_DISSOLVE,
		EFFECT::PLAYER_HEAL
	};


	//�v���C���[�Ɋւ���3D�G�t�F�N�g��`�悷��N���X
	class Player3DEffect final
	{
	private:
		//�Ăяo�����G�t�F�N�g�̃n���h����ۑ�����ϐ�
		std::vector<int> effectHandle_;

	public:
		//�R���X�g���N�^
		constexpr Player3DEffect() {};

		//�f�X�g���N�^
		~Player3DEffect() {};

		//�����������֐�
		void Init(void);

		//�ǂݍ��ݏ����֐�
		void Load(void);

		//�s�������֐�
		void Step(void);

		//�`�揈���֐�
		void Draw(void);

		//�j�������֐�
		void Fin(void);

		//�G�t�F�N�g�\��
		void EffectRequest(EFFECT_HANDLE effectNum, const Vector3D& appearPos, float rotY);
	};
}
