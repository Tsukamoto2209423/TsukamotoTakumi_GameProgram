#pragma once

namespace BOUDAMA
{
	namespace SOUND
	{
		//���ԍ����
		enum class BGM
		{
			//�^�C�g�����
			TITLE,
			//�Q�[���v���C��
			PLAY,

			//����
			NUM
		};

		//���ʉ�
		enum class SE
		{
			//���������̌��ʉ�
			ATTACHED = BGM::NUM,

			//�_���[�W���󂯂��Ƃ��̌��ʉ�
			DAMAGE,

			//�v���C���[�����񂾂Ƃ��̌��ʉ�
			RED_DISSOLVE,

			//�G�����񂾂Ƃ��̌��ʉ�
			ENEMY_DEATH,

			//�G���v���C���[�𔭌������Ƃ��̌��ʉ�
			FIND_OUT,

			//����{�^�����������Ƃ��̌��ʉ�
			DESIDE,

			//�Q�[�����I��������̌��ʉ�
			GAME_FINISH,

			//�L�����Z����
			CANCEL,

			//�t�F�[�h�C���E�t�F�[�h�A�E�g���ɖ���ʉ�
			SCENE_CHANGE,

			//����
			NUM
		};

		//���ʉ��̍��v
		constexpr int ALL_SOUND_NUM = static_cast<int>(SE::NUM);

		//�����p�X
		constexpr char PATH[] = "Data/Sound/SoundList.csv";

	}
}
