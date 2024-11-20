#include "GameSystem.h"
#include "DxLib.h"
#include "Common.h"
#include "FrameRate/FrameRate.h"
#include "Camera/CameraManager.h"
#include <Effekseer/Effekseer.h>
#include <Math/MyMath.h>
#include <Sound/Sound.h>
#include <Input/Input.h>
#include "Input/InputParameter.h"

namespace BOUDAMA
{
	//初期化関数
	void GameSystem::Init()
	{
		//スクリーンモードで起動
		ChangeWindowMode(true);

		//ウィンドウの大きさ設定
		SetGraphMode(Common::WINDOW_WIDTH, Common::WINDOW_HEIGHT, 32);

		//最大化付きのスクリーンモード
		SetWindowStyleMode(7);

		//大きさ変更可能に設定
		SetWindowSizeChangeEnableFlag(true);

		//ウィンドウ名設定
		SetWindowText("ボウダマ！");
	}

	//ゲーム起動関数
	void GameSystem::Start()
	{
		//DxLibを起動する前に行う処理
		Init();

		//DXライブラリ初期化
		if (DxLib_Init() == -1)
		{
			//異常値が返ってきたらゲームを終了
			SetGameEnd();
			return;
		}

		//描画するスクリーンを設定
		SetDrawScreen(DX_SCREEN_BACK);

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);

		//入力初期化
		Input::Init();

		//シーン初期化
		sceneManager_.Init();

		//エフェクト初期化
		CEffekseerCtrl::Init(10, 6000);
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/HitEffect.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/EnemySpawn.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/PlayerDeath.efk"));
		CEffekseerCtrl::SetEffectLoadID(CEffekseerCtrl::LoadData("Data/Effect/Accelerator.efk"));
		CEffekseerCtrl::SetProjectionMtx(MyMath::PI_OVER_THREE, 16.0f / 9.0f, 1.0f, 27000.0f);

		//音情報初期化
		SoundManager::GetInstance()->Init();
		SoundManager::GetInstance()->Load();

	}

	//ゲーム本編統括処理関数
	void GameSystem::MainLoop()
	{
		//ゲーム本編処理
		while (ProcessMessage() != -1)
		{
			//ESCキーかゲーム終了フラグが立っていれば終了
			if (Input::IsKeyDown(GAME_INPUT::ESCAPE) || GetGameEnd())
			{
				break;
			}

			//本編処理
			Step();
		}
	}

	//ゲーム本編処理関数
	void GameSystem::Step()
	{
		//システムに処理を返す
		Sleep(1);

		//=====================

		//フレームレート通常処理
		FrameRate::Step();

		//実行可能ならメインの処理に通る
		if (FrameRate::IsPassedFrameRateTime())
		{
			//画面に表示されたものを初期化（１ループの１度だけ行う）
			ClearDrawScreen();

			//入力処理
			Input::Step();

			//フレームレート更新処理
			FrameRate::Update();

			//================================

			//ゲーム処理
			sceneManager_.Loop();
			sceneManager_.Draw();

			//===============

			//FPS計算
			FrameRate::CalcFPS();
#ifdef _DEBUG

			//FPS表示
			FrameRate::DrawFPS();

#endif // _DEBUG

			//フリップ関数（ループの終わりに１度だけ行う）
			ScreenFlip();
		}
	}

	//情報破棄関数
	void GameSystem::Fin()
	{
		//エフェクト全停止
		CEffekseerCtrl::StopAll();
		//エフェクト情報破棄
		CEffekseerCtrl::Exit();

		//カメラ情報破棄
		CameraManager::GetInstance()->Fin();

		//場面情報破棄
		sceneManager_.Fin();

		//音情報破棄
		SoundManager::GetInstance()->Fin();
		SoundManager::GetInstance()->DeleteInstance();

		InitGraph();

		//DXライブラリの終了処理
		//最後に１回だけやる処理をここに書く
		DxLib_End();
	}
}
