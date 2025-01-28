#include "ScenePlay.h"
#include <DxLib.h>
#include <Effekseer/Effekseer.h>
#include "Common/Common.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Camera/CameraManager.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Input/GamePad/GamePad.h"
#include "Input/InputParameter.h"
#include "Player/PlayerParameter.h"
#include "NumberGraph/Number.h"

namespace BOUDAMA
{
	//�R���X�g���N�^
	ScenePlay::ScenePlay(void)
	{
		shadowHandle_ = -1;
		playDifficulty_ = SCENE::NORMAL_PLAY;
	}

	//�f�X�g���N�^
	ScenePlay::~ScenePlay(void)
	{

	}

	//�`�揈���֐�
	void ScenePlay::Draw(void)
	{
		if (!player_)
		{
			return;
		}

		//�e�̕`��J�n-------------------

		ShadowMap_DrawSetup(shadowHandle_);

		player_->Draw();

		field_.Draw();

		sky_.Draw();

		substanceManager_.Draw();

		enemyManager_.Draw();

		itemManager_.Draw();

		ShadowMap_DrawEnd();

		//�e�̕`��I��-------------------


		//�ʏ�̕`��J�n-------------------

		SetUseShadowMap(0, shadowHandle_);

		field_.Draw();

		sky_.Draw();

		itemManager_.Draw();

		substanceManager_.Draw();

		enemyManager_.Draw();

		player_->Draw();

		SetUseShadowMap(0, -1);

		// �ʏ�̕`��I��-------------------

		//UI
		timeLimit_.Draw();
		Score::DrawScore(SCORE::PLAY::INIT_POS_X, SCORE::PLAY::INIT_POS_Y);

		//�Q�[���v���C�p�̃J�������擾
		const auto& camera = CameraManager::GetInstance()->GetCamera()[CameraManager::GetInstance()->GetState()];

		//�G�t�F�N�g�`��v�Z����
		CEffekseerCtrl::SetCameraMtx(camera->GetPos(), camera->GetTarget(), camera->GetUp());
		CEffekseerCtrl::SetCameraRotMtx(camera->GetPos(), camera->GetRot(), camera->GetUp());
		CEffekseerCtrl::Update();
		CEffekseerCtrl::Draw();

	}

	//�����������֐�
	void ScenePlay::Init(void)
	{
		//�������E�ǂݍ��ݏ���
		player_ = std::make_shared<Player>();
		player_->Init();

		itemManager_.Init();

		enemyManager_.Init(playDifficulty_, itemManager_);

		field_.Init();

		substanceManager_.Init();

		sky_.Init();

		//�X�R�A�Ɛ������Ԃ�\������Ƃ��Ɏg���摜���������Ɠǂݍ���
		NumberGraph::Init();

		//�X�R�A��������
		Score::Init();

		//�J����������
		CameraManager::GetInstance()->Init();

		//�������ԏ�����
		timeLimit_.Init();
		timeLimit_.IsEndless(SCENE::ENDLESS_PLAY == playDifficulty_);

		//�ǂݍ��ݏ���
		Load();

		//�V���h�E�}�b�v�쐬
		shadowHandle_ = MakeShadowMap(4096, 4096);

		//�ˉe��������
		SetShadowMapLightDirection(shadowHandle_, VGet(0.0f, -1.0f, 0.1f));

		SetShadowMapDrawArea(shadowHandle_, VGet(-5100.0f, -1.0f, -5100.0f), VGet(5100.0f, 100.0f, 5100.0f));

	}

	//�ǂݍ��ݏ����֐�
	void ScenePlay::Load(void)
	{
		player_->Load();

		itemManager_.Load();

		enemyManager_.Load(playDifficulty_);

		field_.Load();

		substanceManager_.Load();

		sky_.Load();

		NumberGraph::Load();

		Score::Load();

		timeLimit_.Load();

		//BGM�Đ�
		SoundManager::GetInstance()->PlaySoundData(SOUND::BGM::PLAY, DX_PLAYTYPE_LOOP);
	}

	//�s�������֐�
	void ScenePlay::Step(void)
	{
		if (!player_->GetIsActive())
		{
			return;
		}

#ifdef _DEBUG
		//�f�o�b�O�t���O�������Ă���Ȃ�
		if (CameraManager::GetInstance()->GetState() == CAMERA_STATE::DEBUG)
		{
			//�J�����̏���
			CameraManager::GetInstance()->Step(player_->GetPos());
			CameraManager::GetInstance()->UpDate();

			return;
		}
#endif // _DEBUG


		//�v���C���[�̏���
		player_->Step();

		//�J�����̏���
		CameraManager::GetInstance()->Step(player_->GetPos());
		CameraManager::GetInstance()->UpDate();

		field_.Step();

		enemyManager_.Step(player_->GetPos());

		substanceManager_.Step();

		itemManager_.Step();

		sky_.Step();

		timeLimit_.Step();

		//�����蔻��ꊇ����
		CollisionManager::CheckHitAll(player_, enemyManager_, itemManager_, substanceManager_);

	}

	//�j�������֐�
	void ScenePlay::Fin(void)
	{
		player_->Fin();

		enemyManager_.Fin();

		field_.Fin();

		substanceManager_.Fin();

		itemManager_.Fin();

		sky_.Fin();

		timeLimit_.Fin();

		//�x�X�g�X�R�A�X�V����
		if (SCENE::ENDLESS_PLAY != playDifficulty_)
		{
			Score::UpdateBestScore();
		}
		else
		{
			Score::UpdateEndlessBestScore();
		}

		//�Đ����̉���S�Ď~�߂�
		SoundManager::GetInstance()->StopSoundData(SOUND::BGM::PLAY);

	}

	//����ʔ��f�p�֐�
	bool ScenePlay::CanGoToNextScene(const SCENE_STATE state) const
	{
		//���������������j���������Ȃ瑁�����^�[�����A���̏�ԂɈڍs
		if (state != SCENE_STATE::STEP)
		{
			return true;
		}

		if (!player_->GetIsActive())
		{
			return player_->IsEndDeathEvent();
		}

		//���Ԑ؂�ɂȂ�����I��
		if (timeLimit_.GetTimeLimitCount() <= 0)
		{
			return true;
		}

		return false;
	}

	//����ʑ���p�֐�
	SCENE ScenePlay::GetNextSceneNum(void) const noexcept
	{
		//�G���h���X���[�h�Ȃ猋�ʕ\����ʂɑJ��
		if (SCENE::ENDLESS_PLAY == playDifficulty_)
		{
			return SCENE::RESULT;
		}

		//�v���C���[���������Ă�����N���A�A���Ă��Ȃ�������Q�[���I�[�o�[
		if (player_->GetIsActive())
		{
			return SCENE::CLEAR;
		}

		return SCENE::GAMEOVER;
	}
}
