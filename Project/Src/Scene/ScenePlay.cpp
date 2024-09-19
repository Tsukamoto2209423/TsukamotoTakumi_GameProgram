#include "ScenePlay.h"
#include <DxLib.h>
#include <Effekseer/Effekseer.h>
#include "Game/System.h"
#include "Common/Common.h"
#include "Math/MyMath.h"
#include "Collision/CollisionManager.h"
#include "Camera/CameraManager.h"
#include "Input/KeyBoard/InputKeyBoard.h"
#include "Input/GamePad/GamePad.h"
#include "Input/InputParameter.h"
#include "Player/PlayerParameter.h"
#include "NumberGraph/Number.h"

//コンストラクタ
ScenePlay::ScenePlay(void)
{
	shadowHandle_ = -1;
	playDifficulty_ = SCENE::NORMAL_PLAY;
}

//デストラクタ
ScenePlay::~ScenePlay(void)
{

}

//描画処理関数
void ScenePlay::Draw(void)
{
	if (!player_)
	{
		return;
	}

	//影の描画開始-------------------

	ShadowMap_DrawSetup(shadowHandle_);

	field_.Draw();

	sky_.Draw();

	substanceManager_.Draw();

	enemyManager_.Draw();

	player_->Draw();

	ShadowMap_DrawEnd();

	//影の描画終了-------------------


	//通常の描画開始-------------------

	SetUseShadowMap(0, shadowHandle_);

	field_.Draw();

	sky_.Draw();

	substanceManager_.Draw();

	enemyManager_.Draw();

	player_->Draw();

	SetUseShadowMap(0, -1);

	// 通常の描画終了-------------------

	//UI
	timeLimit_.Draw();
	Score::DrawScore(SCORE::PLAY::INIT_POS_X, SCORE::PLAY::INIT_POS_Y);

	//ゲームプレイ用のカメラ情報取得
	const std::shared_ptr<CameraBase>& camera = CameraManager::GetInstance()->GetCamera()[CameraManager::GetInstance()->GetState()];

	//エフェクト描画計算処理
	CEffekseerCtrl::SetCameraMtx(camera->GetPos(), camera->GetTarget(), camera->GetUp());
	CEffekseerCtrl::SetCameraRotMtx(camera->GetPos(), camera->GetRot(), camera->GetUp());
	CEffekseerCtrl::Update();
	CEffekseerCtrl::Draw();

}

//初期化処理関数
void ScenePlay::Init(void)
{
	//初期化・読み込み処理
	player_ = std::make_shared<Player>();

	player_->Init();

	enemyManager_.Init(playDifficulty_);

	field_.Init();

	substanceManager_.Init();

	sky_.Init();
	
	//スコアと制限時間を表示するときに使う画像を初期化と読み込み
	NumberGraph::Init();

	//スコアを初期化
	Score::Init();

	//カメラ初期化
	CameraManager::GetInstance()->Init();

	//制限時間初期化
	timeLimit_.Init();
	timeLimit_.IsEndless(SCENE::ENDLESS_PLAY == playDifficulty_);

	//読み込み処理
	Load();

	//シャドウマップ作成
	shadowHandle_ = MakeShadowMap(4096, 4096);

	//射影方向決定
	SetShadowMapLightDirection(shadowHandle_, VGet(0.0f, -1.0f, 0.1f));

	SetShadowMapDrawArea(shadowHandle_, VGet(-5100.0f, -1.0f, -5100.0f), VGet(5100.0f, 100.0f, 5100.0f));

}

//読み込み処理関数
void ScenePlay::Load(void)
{
	player_->Load();

	enemyManager_.Load(playDifficulty_);

	field_.Load();

	substanceManager_.Load();

	sky_.Load();

	NumberGraph::Load();

	Score::Load();

	timeLimit_.Load();

	//BGM再生
	SoundManager::GetInstance()->PlaySoundData(SOUND::BGM::PLAY, DX_PLAYTYPE_LOOP);
}

//行動処理関数
void ScenePlay::Step(void)
{
	if (!player_->GetIsActive())
	{
		return;
	}

	//デバッグフラグが立っているなら
	if (CameraManager::GetInstance()->GetState() == CAMERA_STATE::DEBUG)
	{
		CameraManager::GetDebugCamera()->Step(player_->GetPos());
		CameraManager::GetDebugCamera()->UpDate();

		return;
	}

	//プレイヤーの処理
	player_->Step();

	//カメラの処理
	CameraManager::GetInstance()->Step(player_->GetPos());
	CameraManager::GetInstance()->UpDate();

	field_.Step();

	enemyManager_.Step(player_->GetPos());

	substanceManager_.Step();

	sky_.Step();
	
	timeLimit_.Step();

	//当たり判定一括処理
	CollisionManager::CheckHitAll(player_, enemyManager_, itemManager_, substanceManager_);

}

//破棄処理関数
void ScenePlay::Fin(void)
{
	player_->Fin();

	enemyManager_.Fin();

	field_.Fin();

	substanceManager_.Fin();

	sky_.Fin();

	timeLimit_.Fin();

	//ベストスコア更新処理
	if (SCENE::ENDLESS_PLAY != playDifficulty_)
	{
		Score::UpdateBestScore();
	}
	else
	{
		Score::UpdateEndlessBestScore();
	}

	//再生中の音を全て止める
	SoundManager::GetInstance()->StopSoundData(SOUND::BGM::PLAY);

}

//次場面判断用関数
bool ScenePlay::CanGoToNextScene(const SCENE_STATE state) const
{
	//初期化処理中か破棄処理中なら早期リターンし、次の状態に移行
	if (state != SCENE_STATE::STEP)
	{
		return true;
	}

	if (!player_->GetIsActive())
	{
		return player_->IsEndDeathEvent();
	}

	//時間切れになったら終了
	if (timeLimit_.GetTimeLimitCount() <= 0)
	{
		return true;
	}

	return false;
}

//次場面代入用関数
SCENE ScenePlay::GetNextSceneNum(void) const noexcept
{
	//エンドレスモードなら結果表示画面に遷移
	if (SCENE::ENDLESS_PLAY == playDifficulty_)
	{
		return SCENE::RESULT;
	}

	//プレイヤーが生存していたらクリア、していなかったらゲームオーバー
	if (player_->GetIsActive())
	{
		return SCENE::CLEAR;
	}

	return SCENE::GAMEOVER;
}
