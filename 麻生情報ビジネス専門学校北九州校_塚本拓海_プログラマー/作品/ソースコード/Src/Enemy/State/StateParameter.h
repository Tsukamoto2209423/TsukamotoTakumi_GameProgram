#pragma once

namespace BOUDAMA
{
	enum class ENEMY_STATE
	{
		//�ҋ@
		IDLE,

		//�����_���E�H�[�N
		RANDOM_WALK,

		//�v���C���[�T��
		SEARCH,

		//�v���C���[����
		FIND_OUT,

		//�v���C���[�ǐ�
		CHASE,

		//������
		RUN_AWAY,

		//�U������
		CHARGE,

		//�U����
		ATTACK,

		//�m�b�N�o�b�N
		KNOCK_BACK,

		//���̏��
		CORPSE
	};

}
